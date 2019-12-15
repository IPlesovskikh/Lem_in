
#include "validator.h"

static void	get_direction(t_child *child, t_room **array, int i)
{
	t_child	*parent;

	parent = array[i]->parent;
	if (parent)
	{
		while (parent->next)
			parent = parent->next;
		parent->next = (t_child *) malloc(sizeof(t_child));
		parent->next->prev = parent;
		parent->next->num = child->num;
		parent->next->next = NULL;
	}
	else
	{
		array[i]->parent = (t_child*)malloc(sizeof(t_child));
		array[i]->parent->prev = NULL;
		array[i]->parent->next = NULL;
		array[i]->parent->num = child->num;
	}
}

static void	del_same_lvl_and_get_directions(t_data *data, t_room **array, int **queue, int i)
{
	int 	y;
	t_child	*child;

	while (queue[++i][0] != -1)
	{;
		y = -1;
		while (queue[i][++y] != -1)
		{
			child = array[queue[i][y]]->child;
			while (child)
			{
				if (array[child->num]->level == array[queue[i][y]]->level)
					del_child_or_parent(&child, child->num, array, queue[i][y]);
				else if (array[child->num]->level < array[queue[i][y]]->level)
				{
					get_direction(child, array, queue[i][y]);
					del_child_or_parent(&child, child->num, array, queue[i][y]);
				}
				else
					child = child->next;
			}
		}
	}
	data->end->parent = data->end->child;
	data->end->child = NULL;
}

static void	del_no_lvl(t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*parent;

	i = -1;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			parent = array[queue[i][y]]->parent;
			while (parent)
			{
				if (array[parent->num]->level == -1)
					del_child_or_parent(&parent, parent->num, array, queue[i][y]);
				else
					parent = parent->next;
			}
		}
	}
}

void		delete_no_one_link(t_data *data, t_room **array, int **queue, int i)
{
	int 	y;
	t_child	*child;
	t_child	*temp_parent;

	y = -1;
	while (queue[i][++y] != -1)
	{
		child = array[queue[i][y]]->child;
		while (child)
		{
			if (array[child->num]->num != data->end->num &&
				array[child->num]->output == 0)
			{
				temp_parent = array[child->num]->parent;
				del_child_or_parent(&temp_parent, queue[i][y], array, child->num);
				array[child->num]->input--;
				del_child_or_parent(&child, child->num, array, queue[i][y]);
				array[queue[i][y]]->output--;
			}
			else
				child = child->next;
		}
	}
}

int			algo_prepare_graph(t_data *data,t_room **array,int ***queue)
{
	del_same_lvl_and_get_directions(data, array, (*queue), -1);
	if (data->total_rooms == 2)
	{
		data->end->input++;
		return (ft_free_queue(&(*queue)));
	}
    if (data->end->parent == NULL)
		return (print_error());
	del_no_lvl(array, (*queue));
	calculate_input_and_output(array, (*queue));
	delete_no_one_link_a(data, array, (*queue), -1);
	del_input_forks(data, array, 1, (*queue));
	delete_no_one_link_a(data, array, (*queue), -1);
	return (ft_free_queue(&(*queue)));
}
