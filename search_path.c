//
// Created by Peggie Donnie on 2019-11-30.
//

#include "validator.h"

static void sort_childs(t_room **array, t_room *end, t_child *parent)
{
	while (parent) // чекнуть как код работает else / не проверял
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
					parent->next = parent->prev->next;
				parent->prev->next = parent;
			}
			else
			{
				end->child = end->child->next;
				parent->prev = end->child;
				parent->next = end->child->next;
				parent->next->prev = parent;
				end->child->next = parent;
			}
			parent = end->child;
		}
		else
			parent = parent->next;
	}
}

static void create_path(int **path, t_room **array, int max, t_child *parent)
{
	int 	i;
	t_room	*temp;

	(*path) = (int*)malloc(sizeof(int) * (max + 1));
	(*path)[max] = -1;
	i = 0;
	temp = array[parent->num];
	while (i < max)
	{
		(*path)[i] = temp->num;
		temp = array[array[temp->num]->parent->num];
		i++;
	}
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

void	get_path(t_data *data, t_room **array, int **paths)
{
	t_room	*end;
	t_child	*parent;
	t_child	*temp;
	int 	start;
	int 	status;
	int 	i;

	end = data->end;
	sort_childs(array, end, end->parent);
	i = 0;
	parent = end->parent;
	create_path(&paths[i], array, array[parent->num]->level, parent);
	parent = parent->next;
	start = data->start->num;
	while (parent)
	{
		temp = parent;
		status = 1;
		while (status == 1 && temp->num != start)
		{
			if (array[temp->num]->output > 1)
				status = -1;
			temp = array[temp->num]->parent;
		}
		if (status == 1 || check_forks(paths, temp->num, i + 1) == 1)
			create_path(&paths[++i], array, array[parent->num]->level, parent);
		parent = parent->next;
	}
}
