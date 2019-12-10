//
// Created by Peggie Donnie on 2019-11-24.
//

#include "validator.h"

int		ft_check_comment(t_lines **lines)
{
	int		i;

	i = 0;
	while (i == 0)
	{
		if ((*lines)->line[0] == '#' && (*lines)->line[1] == '#')
			return (-1);
		else if ((*lines)->line[0] == '#')
			(*lines) = (*lines)->next;
		else
			i++;
	}
	return (0);
}

int		get_ants(t_data	*data, int fd, t_lines **lines)
{
	char	*line;
	int 	i;
	int 	status;

	status = 2;
	while (status == 2 && (status = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == '#' && line[1] != '#')
			status = 2;
		if (*lines)
		{
			(*lines)->next = (t_lines*)malloc(sizeof(t_lines));
			(*lines)->line = line;
			(*lines) = (*lines)->next;
			(*lines)->next = NULL;
		}
		else
		{
			(*lines) = (t_lines*)malloc(sizeof(t_lines));
			(*lines)->line = line;
			(*lines)->next = NULL;
			data->first_line_print = (*lines);
		}
	}
	if (status <= 0)
		return (-1);
	i = 0;
	if (line[i] == '+' || line[i] == '-')
		i++;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
			return(-1); // line отфришить
		i++;
	}
	if ((data->ants = ft_atoi(line)) == 0 && line[0] != '0' && line[1] != '\0')
		return (-1);
	return (0);
}

t_lines		*get_lines(t_lines *lines, int fd)
{
	char 	*line;
	int 	status;
	t_lines	*line_start_rooms;

	while (lines->next)
		lines = lines->next;
	line_start_rooms = lines;
	while ((status = get_next_line(fd, &line)) > 0) // -1 ошибка как обработать ? отшрифить line не забыть
	{
        if ((lines->next = (t_lines*)malloc(sizeof(t_lines))) == NULL)
			return (NULL); // line не забыть отфришить
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

int		parse(t_data *data, t_lines *lines, int i)
{
	while (lines && i == 0)
	{
		if (lines->line[0] == '#' && lines->line[1] == '#') // а если три подряд то что ?
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
		return (-1); // тут -1 не значит конец, если ряд условий будет соблюден то можно продолжать(как определить что начало и конец хотя бы один путь имеют ?)?
	return (0);
}

t_lines		*validator(t_data *data, int fd)
{
	t_lines		*lines;

	lines = NULL;
	if (get_ants(data, fd, &lines) == -1 || data->ants < 1)
		return (NULL);
	if ((lines = get_lines(lines, fd)) == NULL)
		return (NULL); // lines  удалить
	if (parse(data, lines, 0) == -1) // lines почистил а строки line  ?
		return (NULL); // lines удалить
	return (lines);
}