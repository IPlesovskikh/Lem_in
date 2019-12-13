
#include "validator.h"

int		check_links(t_link *link, t_link *temp_link)
{
	t_link	*temp;

	temp = link;
	while (temp->next)
	{
		if (((temp->a == temp_link->a) && (temp->b == temp_link->b)) ||
			((temp->a == temp_link->b) && (temp->b == temp_link->a)))
			return (-4);
		temp = temp->next;
	}
	return (0);
}

int 	ft_create_link(t_link **temp_link, t_data *data)
{
	t_link	*temp;

	if (data->links)
	{
		if ((temp = (t_link*)malloc(sizeof(t_link))) == NULL)
			return (-1);
		(*temp_link)->next = temp;
		(*temp_link)->next->prev = (*temp_link);
		(*temp_link) = (*temp_link)->next;
	}
	else
	{
		if ((data->links = (t_link*)malloc(sizeof(t_link))) == NULL)
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
	if ((temp = ft_strsub(lines->line, 0, i)) == NULL)
		return (-1);
	if ((temp_link->a = check_rooms(data, temp)) == -1)
		return (ft_clean_buf(&temp));
	free(temp);
	i++;
	i2 = i;
	while (lines->line[i] != '\0')
		i++;
	if ((temp = ft_strsub(lines->line, i2, i - i2)) == NULL)
		return (-1);
	if ((temp_link->b = check_rooms(data, temp)) == -1)
		return (ft_clean_buf(&temp));
	free(temp);
	return (0);
}

int		get_links(t_data *data, t_lines *lines)
{
	t_link	*temp_link;
	int 	i;

	temp_link = NULL;
	i = 0;
	while (lines)
	{
		if (lines->line[0] != '#')
		{
			if ((ft_create_link(&temp_link, data)) == -1)
				return (-1);
			if ((i = ft_fill_link(temp_link, data, lines)) == -1)
				return (-1);
			if (i == -3 || ((check_links(data->links, temp_link)) == -4))
			{
				temp_link = temp_link->prev;
				free(temp_link->next);
				temp_link->next = NULL;
				if (i == -3)
					return (-3);
			}
		}
		lines = lines->next;
	}
	return (0);
}
