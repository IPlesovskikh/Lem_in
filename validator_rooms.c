//
// Created by Peggie Donnie on 26/11/2019.
//
#include "validator.h"

static int		check_coordinates(t_room *temp, t_room *check)
{
	while (temp->num != check->num)
	{
		if ((temp->x == check->x) && (temp->y == check->y))
		{
			printf("Error: two rooms have the same coordinates : x = %d y = %d\n", temp->x, temp->y);
			return (-1);
		}
		check = check->next;
	}
	return (0);
}

static int		allocate_memory_for_room(t_room	**temp, t_data *data)
{
	if (*temp)
	{
		if (((*temp)->next = malloc(sizeof(t_room))) == NULL)
			return (-1);
		(*temp)->next->child = NULL;
		(*temp) = (*temp)->next;
	}
	else
	{
		if ((data->rooms = malloc(sizeof(t_room))) == NULL)
			return (-1);
		(*temp) = data->rooms;
		(*temp)->child = NULL;
	}
	return (0);
}

static t_room	*create_room(t_data *data, t_lines *lines, int i)
{
	t_room		*temp;
	t_room		*check;

	temp = data->rooms;
	while (temp && temp->next != NULL)
		temp = temp->next;
	if (allocate_memory_for_room(&temp, data) == -1)
		return (NULL);
	temp->num = data->order;
	data->order++;
	data->total_rooms = data->order;
	temp->next = NULL;
	temp->name = NULL;
	temp->x = 0;
	temp->y = 0;
	temp->level = -1;
	temp->input = 0;
	temp->output = 0;
	temp->child = NULL;
	temp->parent = NULL;
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
		if (ft_isdigit(lines->line[i]) == 0)
			return (-1);
	temp->x = ft_atoi(&(lines->line[i2]));
	i2 = i;
	if (lines->line[++i] == '+' || lines->line[i--] == '-')
		i++;
	while (lines->line[++i] != '\0')
		if (ft_isdigit(lines->line[i]) == 0)
			return (-1);
	temp->y = ft_atoi(&(lines->line[i2]));
	return (check_coordinates(temp, data->rooms) == -1 ? -1 : 0);
}

int		get_commande(t_data *data, t_lines **lines)
{
	t_room		*temp;
	int			i;

	if (ft_strcmp(&((*lines)->line[2]), "start") == 0)
		i = 1;
	else if (ft_strcmp(&((*lines)->line[2]), "end") == 0)
		i = 2;
	else
		return (-1);
	if ((i == 1 && data->start != NULL) || (i == 2 && data->end != NULL))
		return (-1);
	(*lines) = (*lines)->next;
	if (ft_check_comment(&(*lines)) == -1)
		return (-1);
	if (get_rooms(0, 0, data, *lines) == -1)
		return (-1);
	temp = data->rooms;
	while (temp->next != NULL)
		temp = temp->next;
	if (i == 1)
		data->start = temp;
	else
		data->end = temp;
	return (0);
}
