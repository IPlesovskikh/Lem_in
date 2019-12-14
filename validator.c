//
// Created by Peggie Donnie on 2019-11-24.
//

#include "validator.h"

int		get_ants(t_data	*data, int fd, t_lines **lines, int i)
{
	int 	status;

	status = 0;
	if ((skip_comments(2, data, &(*lines), fd)) == -1)
		return (-1);
	while ((*lines)->line[i] == '\t' || (*lines)->line[i] == ' ')
		i++;
	if ((*lines)->line[i] == '+' || (*lines)->line[i] == '-')
		i++;
	while (status == 0 && (*lines)->line[i] != '\0')
	{
		if (ft_isdigit((*lines)->line[i]) == 0)
			status = -1;
		else
			i++;
	}
	while (((*lines)->line[i] == '\t' || (*lines)->line[i] == ' '))
		i++;
	if ((*lines)->line[i] != '\0')
		return (-1);
	if ((data->ants = ft_atoi((*lines)->line)) == 0)
		if ((*lines)->line[0] == '\0' || ((*lines)->line[0] != '0' && (*lines)->line[1] != '\0'))
			return (-1);
	return (0);
}

static t_lines	*get_lines(t_lines *lines, int fd)
{
	char 	*line;
	int 	status;
	t_lines	*line_start_rooms;

	while (lines->next)
		lines = lines->next;
	line_start_rooms = lines;
	while ((status = get_next_line(fd, &line)) > 0)
	{
        if ((lines->next = (t_lines*)malloc(sizeof(t_lines))) == NULL)
			return (NULL);
        lines->next->line = line;
        lines = lines->next;
        line = NULL;
	}
	if (status < 0)
		return (NULL);
	lines->next = NULL;
	line_start_rooms = line_start_rooms->next;
	return (line_start_rooms);
}

static int		parse(t_data *data, t_lines *lines, int i)
{
	while (lines && i == 0)
	{
		if (lines->line[0] == '#' && lines->line[1] == '#')
		{
		    if (get_commande(data, &lines) == -1)
				i = -2;
		    else
                lines = lines->next;
		}
		else if (lines->line[0] != '#')
		{
			if (get_rooms(0, 0, data, lines) == -1)
				i = -1;
			else
                lines = lines->next;
		}
		else
            lines = lines->next;
	}
	if (i == -2 || data->rooms == NULL || data->start == NULL ||
	data->end == NULL || get_links(data, lines) == -1 || data->links == NULL)
		return (-1);
	if (data->ants > 261000)
		data->ants = 261000;
	return (0);
}

int				validator(t_data *data, int fd)
{
	t_lines		*lines;

	lines = NULL;
	if (get_ants(data, fd, &lines, 0) == -1 || data->ants < 1)
		return (print_error());
	if ((lines = get_lines(lines, fd)) == NULL)
		return (print_error());
	if (parse(data, lines, 0) == -1)
		return (print_error());
	return (0);
}