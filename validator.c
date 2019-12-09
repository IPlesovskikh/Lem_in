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

int		get_ants(t_data	*data, int fd)
{
	char	*line;
	int 	i;
	int 	status;

	status = 2;
	while (status == 2 && (status = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == '#' && line[1] != '#')
		{
			status = 2;
			free(line);
		}
	}// если меньше 0 то выйти ?
	if (status == -1 || line == NULL)
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
	free(line);
	return (0);
}

int		get_lines(t_lines *lines, int fd)
{
	char 	*line;

	while (get_next_line(fd, &line) > 0) // -1 ошибка как обработать ? отшрифить line не забыть
	{
		if (lines->line)
        {
            if ((lines->next = (t_lines*)malloc(sizeof(t_lines))) == NULL)
                return (-1); // line не забыть отфришить
            lines->next->line = line;
            lines = lines->next;
        }
		else
            lines->line = line;
        line = NULL;
	}
	lines->next = NULL;
	return (0);
}

int		parse(t_data *data, t_lines *lines, int i)
{
	t_link	*temp;
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

int		validator(t_data *data, int fd)
{
	t_lines		lines;

	if (get_ants(data, fd) == -1 || data->ants < 1)
		return (-1);
	lines.line = NULL;
	lines.line = NULL;
	if (get_lines(&lines, fd) == -1)
		return (-1); // lines  удалить
	if (parse(data, &lines, 0) == -1) // lines почистил а строки line  ?
		return (-1); // lines удалить
	//сохранить линии которые распечатать->только валидные линии(? если реализую) и без коментов. записать все в одну строку и вывести потом ?
	// start and end 0 and max int
	return (0);
}