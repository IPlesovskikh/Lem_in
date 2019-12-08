//
// Created by Peggie Donnie on 26/11/2019.
//

#include "validator.h"

int		check_links(t_link *link, t_link *temp_link)
{
	t_link	*temp;

	temp = link;
	while (temp->next)
	{
		if (((temp->a == temp_link->a) && (temp->b == temp_link->b)) ||
			((temp->a == temp_link->b) && (temp->b == temp_link->a)))
			return (-1);
		temp = temp->next;
	}
	return (0);
}

int 	ft_create_link(t_link **temp_link, t_data *data)
{
	if (data->links)
	{
		if (((*temp_link)->next = malloc(sizeof(t_link))) == NULL)
			return (-1);
		(*temp_link)->next->prev = (*temp_link);
		(*temp_link) = (*temp_link)->next;
	}
	else
	{
		if ((data->links = malloc(sizeof(t_link))) == NULL)
			return (-1);
		(*temp_link) = data->links;
		(*temp_link)->prev = NULL;
	}
	(*temp_link)->next = NULL;
	(*temp_link)->a = -1;
	(*temp_link)->b = -1;
	return (0);
}

static int		check_rooms(t_data *data, char *temp)
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
	if ((temp_link->a = check_rooms(data, temp)) == -1)
		return (-1);
	free(temp);
	i++;
	i2 = i;
	while (lines->line[i] != '\0')
		i++;
	temp = ft_strsub(lines->line, i2, i - i2);
	if ((temp_link->b = check_rooms(data, temp)) == -1)
		return (-1);
	free(temp);
	return (0);
}

int		get_links(t_data *data, t_lines *lines)
{
	t_link	*temp_link;

	temp_link = NULL;
	while (lines)
	{
		if (lines->line[0] != '#')
		{
			if ((ft_create_link(&temp_link, data)) == -1)
				return (-1);
			if ((ft_fill_link(temp_link, data, lines)) == -1)
				return (-1);
			if ((check_links(data->links, temp_link)) == -1)
			{
				printf("Error : duplicate of link : %s ", lines->line);
				return (-1);
			}
		}
		lines = lines->next;
	}
	return (0);
}

