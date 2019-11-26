//
// Created by Peggie Donnie on 2019-11-24.
//

#include "validator.h"

int		get_ants(t_data	*data, int fd)
{
	char	*line;
	int 	i;

	get_next_line(fd, &line);
	if (line == NULL)
		return (-1);
	i = 0;
	if (line[i] == '+' || line[i] == '-')
		i++;
	while (line[i] != '\0')
	{
		if (ft_isdigit(line[i]) == 0)
			return(-1); // free + put_error+return
		i++;
	}
	data->ants = ft_atoi(line); // чекнуть на переполнение как в пушсвапе == валидность цифры иначе return - 1
	free(line);
	return (0);
}

int		get_lines(t_lines *lines, int fd)
{
	char 	*line;

	while (get_next_line(fd, &line) > 0) // -1 ошибка как обработать ?
	{
		if (lines->line)
        {
            if ((lines->next = malloc(sizeof(t_lines))) == NULL)
                return (-1); // free +  + put_error+return
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

int		check_coordinates(t_room *temp, t_room *check)
{
	while (temp->num != check->num)
	{
		if ((temp->x == check->x) && (temp->y == check->y))
			return (-1);
		check = check->next;
	}
	return (0);
}

t_room	*create_room( t_data *data, t_lines *lines, int i)
{
	t_room		*temp;
	t_room		*check;
	static int 	num;

	temp = data->rooms;
	while (temp && temp->next != NULL)
		temp = temp->next;
	if (temp)
	{
        if ((temp->next = malloc(sizeof(t_room))) == NULL)
            return (NULL);
        temp->next->prev = temp;
        temp = temp->next;
    }
	else
    {
        if ((data->rooms = malloc(sizeof(t_room))) == NULL)
            return (NULL);
        temp = data->rooms;
        temp->prev = NULL;
    }
	temp->num = num++;
	temp->next = NULL;
	temp->name = NULL;
	temp->x = 0;
	temp->y = 0;
	temp->name = ft_strsub(lines->line, 0, i);
	check = data->rooms;
	while (check->num != temp->num)
	{
		if (ft_strcmp(check->name, temp->name) == 0)
			return (NULL);
		check = check->next;
	}
	return (temp);
}

int 	get_rooms(int i, int i2, t_data *data, t_lines *lines)
{
	t_room		*temp;

	while (lines->line[i] != '\0' && lines->line[i] != ' ')
		i++;
	if (lines->line[i] == '\0')
		return (-1);
	if ((temp = create_room(data, lines, i)) == NULL)
		return (-1);
	i2 = i + 1;
	while (lines->line[++i] != '\0' && lines->line[i] != ' ')
	{
		if (ft_isdigit(lines->line[i]) == 0)
			return (-1);
	}
	temp->x = ft_atoi(&(lines->line[i2]));
	i2 = i;
	while (lines->line[++i] != '\0')
	{
		if (ft_isdigit(lines->line[i]) == 0)
			return (-1);
	}
	temp->y = ft_atoi(&(lines->line[i2]));
	if (check_coordinates(temp, data->rooms) == -1)
		return (-1);
	return (0);
}

int		ft_check_comment(t_lines **lines)
{
	int 	i;

	i = 0;
	while (i == 0)
	{
		if ((*lines)->line[0] == '#' && (*lines)->line[1] == '#')
			return (-1);
		else if ((*lines)->line[0] == '#')
		{
			(*lines) = (*lines)->next;
		}
		else
			i++;
	}
    return (0);
}

int 	get_commande(t_data *data, t_lines **lines)
{
	t_room		*temp;

	if (ft_strcmp(&((*lines)->line[2]), "start") == 0)
	{
	    if (data->start != NULL)
            return (-1);
		(*lines) = (*lines)->next;
		if (ft_check_comment(&(*lines)) == -1)
			return (-1);
		if (get_rooms(0, 0, data, *lines) == -1)
			return (-1);
		temp = data->rooms;
		while (temp->next != NULL)
			temp = temp->next;
		data->start = temp;
	}
	else if (ft_strcmp(&((*lines)->line[2]), "end") == 0)
	{
        if (data->end != NULL)
            return (-1);
		(*lines) = (*lines)->next;
		if (ft_check_comment(&(*lines)) == -1)
			return (-1);
		if (get_rooms(0, 0, data, (*lines)) == -1)
			return (-1);
		temp = data->rooms;
        while (temp->next != NULL)
            temp = temp->next;
		data->end = temp;
	}
	else
		return (-1);
	return (0);
}

int		check_rooms(t_data *data, t_lines *lines, char *temp)
{
	t_room 	*check;
	int 	i;

	check = data->rooms;
	i = 0;
	while (i == 0 && check)
	{
		if (ft_strcmp(check->name, temp) == 0)
			i = 1;
		else
		    check = check->next;
	}
	if (i == 0)
		return (-1);
	return (check->num);
}

int		check_links(t_link *link, t_link *temp_link)
{
	t_link	*temp;

	temp = link;
	while (temp->next)
	{
		if (((temp->a && temp_link->a) && (temp->b && temp_link->b)) ||
				((temp->a && temp_link->b) && (temp->b && temp_link->a)))
			return (-1);
		temp = temp->next;
	}
	return (0);
}

t_link 	*ft_create_link(t_link *temp_link, t_data *data)
{
	if (data->links)
	{
		if ((temp_link->next = malloc(sizeof(t_link))) == NULL)
			return (NULL);
		temp_link->next->prev = temp_link;
		temp_link = data->links->next;
	}
	else
	{
		if ((data->links = malloc(sizeof(t_link))) == NULL)
			return (NULL);
		temp_link = data->links;
	}
	temp_link->next = NULL;
	return (temp_link);
}

int		ft_fill_link(t_link *temp_link, t_data *data, t_lines *lines)
{
	char 	*temp;
	int 	i;
	int 	i2;

	i = 0;
	while (lines->line[i] != '\0' && lines->line[i] != '-')
		i++;
	if (lines->line[i] == '\0')
		return (-1);
	temp = ft_strsub(lines->line, 0, i);
	if ((temp_link->a = check_rooms(data, lines, temp)) == -1)
		return (-1);
	free(temp);
	i++;
	i2 = i;
	while (lines->line[i] != '\0')
		i++;
	temp = ft_strsub(lines->line, i2, i - i2);
	if ((temp_link->b = check_rooms(data, lines, temp)) == -1)
		return (-1);
	free(temp);
}

int		get_links(t_data *data, t_lines *lines)
{
	t_link	*temp_link;

	temp_link = NULL;
	while (lines)
	{
		if ((temp_link = ft_create_link(temp_link, data)) == NULL)
			return (-1);
		if ((ft_fill_link(temp_link, data, lines)) == -1)
			return (-1);
		if ((check_links(data->links, temp_link)) == -1)
			return (-1);
		lines = lines->next;
	}
	return (0);
}

int		parse(t_data *data, t_lines *lines)
{
	int 	i;

	i = 0;
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
	if (i == -2 || data->rooms == NULL || data->start == NULL || data->end == NULL)
		return (-1);
	if (get_links(data, lines) == -1) // тут -1 не значит конец, если ряд условий будет соблюден то можно продолжать(как определить что начало и конец хотя бы один путь имеют ?)?
		return (-1);
	if (data->links == NULL)
		return (-1);
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
		return (-1);
	if (parse(data, &lines) == -1) // lines почистил а строки line  ?
		return (-1);
	//сохранить линии которые распечатать->только валидные линии || координаты отрицательные не принимает
	return (0);
}