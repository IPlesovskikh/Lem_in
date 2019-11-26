//
// Created by Peggie Donnie on 26/11/2019.
//
#include "validator.h"

static int		check_coordinates(t_room *temp, t_room *check)
{
	while (temp->num != check->num)
	{
		if ((temp->x == check->x) && (temp->y == check->y))
			return (-1);
		check = check->next;
	}
	return (0);
}

static t_room	*create_room( t_data *data, t_lines *lines, int i)
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

int 		get_rooms(int i, int i2, t_data *data, t_lines *lines)
{
	t_room		*temp;

	while (lines->line[i] != '\0' && lines->line[i] != ' ')
		i++;
	if (lines->line[i] == '\0')
		return (-1);
	if ((temp = create_room(data, lines, i)) == NULL)
		return (-1);
	i2 = i + 1;
	if (lines->line[++i] == '+' || lines->line[i--] == '-')
		i++;
	while (lines->line[++i] != '\0' && lines->line[i] != ' ')
	{
		if (ft_isdigit(lines->line[i]) == 0)
			return (-1);
	}
	temp->x = ft_atoi(&(lines->line[i2]));
	i2 = i;
	if (lines->line[++i] == '+' || lines->line[i--] == '-')
		i++;
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

static int		ft_check_comment(t_lines **lines)
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

