//
// Created by Peggie Donnie on 2019-11-30.
//

#include "validator.h"

static void sort_childs(t_room **array, t_room *end, t_child *parent)
{
	while (parent->next)
	{
		if (array[parent->num]->level > array[parent->next->num]->level)
		{
			if (parent->prev)
			{
				parent->prev->next = parent->next;
				parent->next->prev = parent->prev;
				parent->prev = parent->next;
				parent->next = parent->next->next;
				if (parent->next)
					parent->next->prev = parent;
				parent->prev->next = parent;
			}
			else
			{
				end->parent = end->parent->next;
				parent->prev = end->parent;
				parent->next = end->parent->next;
				if (parent->next)
					parent->next->prev = parent;
				end->parent->next = parent;
				end->parent->prev = NULL;
			}
			parent = end->parent;
		}
		else
			parent = parent->next;
	}
}

static int create_path(t_data *data, int **path, t_room **array, int max, t_child *parent)
{
	int 	i;
	t_room	*temp;
	int 	y;

	if (((*path) = (int*)malloc(sizeof(int) * (max + 4))) == NULL)
		return (-1);
	(*path)[max + 3] = -1;
	(*path)[0] = max + 2;
	(*path)[1] = data->start->num;
	(*path)[max + 2] = data->end->num;
	i = max + 2;
	temp = array[parent->num];
	while (--i > 1)
	{
		(*path)[i] = temp->num;

		if (array[temp->num]->parent)
			temp = array[array[temp->num]->parent->num];
		else
			return (0);
	}
	data->total_paths++;
	 return (1);
}

int		check_forks(int **paths, int checked, int max)
{
	int 	i;
	int 	y;
	int 	status;

	status = 1;
	y = 0;
	while (status == 1 && y < max)
	{
		i = 0;
		while(status == 1 && paths[y][i] != -1)
		{
			if (paths[y][i] == checked)
				status = -1;
			i++;
		}
		y++;
	}
	return (status);
}

void	check_path(t_room **array, int start, t_child *parent, int end)
{
	t_child		*child;
	int			status;

	while (parent)
	{
		child = array[parent->num]->parent;
		status = 0;
		while (status == 0 && child)
		{
			if (child->num == start)
				status = 1;
			else
				child = array[child->num]->parent;
		}
		if (status == 0 && parent->num != start)
			del_child_or_parent(&parent, parent->num, array, end);
		else
			parent = parent->next;
	}
}

int		get_path(t_data *data, t_room **array, int **paths)
{
	t_room	*end;
	t_child	*parent;
	t_child	*temp;
	int 	start;
	int 	status;
	int 	i;

	end = data->end;
	check_path(array, data->start->num, end->parent, end->num);
	if (end->parent->next)
		sort_childs(array, end, end->parent);
	i = 0;
	parent = end->parent;
	if ((create_path(data, &(paths[i]), array,
			array[parent->num]->level, parent)) == -1)
		return (print_error());
	parent = parent->next;
	start = data->start->num;
	while (parent)
	{
		temp = parent;
		status = 1;
		while (status == 1 && temp->num != start)
		{
			if (array[temp->num]->output > 1)
				if (check_forks(paths, temp->num, i + 1) == -1)
					status = -1;
			temp = array[temp->num]->parent;
		}
		if (status == 1)
			if ((status = create_path(data, &(paths[++i]),
					array, array[parent->num]->level, parent)) == -1)
				return (print_error());
		parent = parent->next;
	}
	while (++i < end->input)
		paths[i] = NULL;
	return (0);
}