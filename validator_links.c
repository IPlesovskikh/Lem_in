
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

int		ft_serach_links(const char *checker, const char *checked, int i)
{
	int 	temp;
	int 	y;

	temp = i;
	y = 0;
	while (checker[y] != '\0')
	{
		if (checker[y] != checked[i])
			return (temp);
		i++;
		y++;
	}
	return (i);
}

int		ft_search_room_b(t_link *temp_link, t_data *data, t_lines *lines, int i)
{
	t_room		*temp;
	int 		status;

	temp = data->rooms;
	status = i;
	while (status != -1 && temp)
	{
		status = i;
		if (((i = ft_serach_links(temp->name, lines->line, i))) == status)
			temp = temp->next;
		else
		{
			if (lines->line[i] == '\0')
			{
				temp_link->b = temp->num;
				return (0);
			}
			else
			{
				temp = temp->next;
				i = status;
			}
		}
	}
	return (-3);
}

int		ft_fill_link(t_link *temp_link, t_data *data, t_lines *lines, int i)
{
	t_room		*temp;
	int 		status;

	temp = data->rooms;
	status = 0;
	while (status != -1 && temp)
	{
		status = i;
		if (((i = ft_serach_links(temp->name, lines->line, i))) == status)
			temp = temp->next;
		else
		{
			if (lines->line[i] == '-')
			{
				temp_link->a = temp->num;
				status = -1;
			}
			else
			{
				temp = temp->next;
				i = 0;
			}
		}
	}
	return ((status == -1) ? ft_search_room_b(temp_link, data, lines, i + 1) : -3);
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
			i = ft_fill_link(temp_link, data, lines, 0);
			if (i == -3 || ((check_links(data->links, temp_link)) == -4))
			{
				free_temp_link(&temp_link, data);
				if (i == -3)
					return (-3);
			}
		}
		else if ((ft_strcmp(&(lines->line[0]), "##start") == 0) ||
				(ft_strcmp(&(lines->line[0]), "##end") == 0))
			return (-1);
		lines = lines->next;
	}
	return (0);
}
