
#include "validator.h"

void	del_child_or_parent(t_child	**child, int y, t_room **array, int i)
{
	t_child		*temp;
	t_child		*del;

	temp = (*child);
	while (temp->num != y)
		temp = temp->next;
	del = temp;
	if (temp->prev)
	{
		temp->prev->next = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
		temp = temp->next;
	}
	else
	{
		if (array[i]->child && array[i]->child->num == y)
		{
			array[i]->child = temp->next;
			if (array[i]->child)
				array[i]->child->prev = NULL;
			temp = array[i]->child;
		}
		else
		{
			array[i]->parent = temp->next;
			if (array[i]->parent)
				array[i]->parent->prev = NULL;
			temp = array[i]->parent;
		}
	}
	free(del);
	(*child) = temp;
}

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

static void	del_same_lvl_and_get_directions(t_data *data, t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*child;

	i = -1;
	while (queue[++i][0] != -1)
	{
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

static void	calculate_input_and_output(t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*child;

	i = -1;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			child = array[queue[i][y]]->child;
			while (child)
			{
				array[queue[i][y]]->output++;
				array[child->num]->input++;
				child = child->next;
			}
		}
	}
}

static void		delete_no_one_link(t_data *data, t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*child;
	t_child	*temp_parent;

	i = -1;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			child = array[queue[i][y]]->child;
			while (child)
			{
				if (array[child->num]->num != data->end->num && array[child->num]->output == 0)
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
}

int			search_no_input_forks(t_data *data, t_room **array, t_child *parent)
{
	if (data->start->num != array[parent->num]->num && array[parent->num]->output == 1)
	{
		parent = array[parent->num]->parent;
		if (search_no_input_forks(data, array, parent) == 0)
			return (0);
		else
			return (1);
	}
	else if (data->start->num == array[parent->num]->num)
		return (1);
	return (0);
}

void		delete_fork(t_room **array, int i, t_child *parent)
{
	t_child		*temp;
	t_child		*temp_parent;

	temp = array[i]->parent;
	while (temp)
	{
		if (temp->num == parent->num)
		{
			temp = temp->next;
			array[i]->parent = parent;
			array[i]->parent->next = NULL;
			array[i]->parent->prev = NULL;
		}
		else
		{
			temp_parent = array[temp->num]->child;
			del_child_or_parent(&temp_parent, i, array, temp->num);
			array[temp->num]->output--;
			del_child_or_parent(&temp, temp->num, array, i);
			array[i]->input--;
		}
	}
}

void		del_input_forks(t_data *data, t_room **array, int i, int **queue)
{
	int 	y;
	t_child	*parent;
	int 	status;

	i = 1;
	status = 0;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			if (array[queue[i][y]]->num != data->end->num && array[queue[i][y]]->input > 1)
			{
				parent = array[queue[i][y]]->parent;
				while (status == 0 && parent)
				{
					if (search_no_input_forks(data, array, parent) == 0)
						parent = parent->next;
					else
						status = 1;
				}
				if (status == 1)
					delete_fork(array, queue[i][y], parent);
				else
					delete_fork(array, queue[i][y], array[queue[i][y]]->parent);
			}
		}
	}
}

int			algo_prepare_graph(t_data *data,t_room **array,int **queue)
{
	int 	i;

	del_same_lvl_and_get_directions(data, array, queue);
	if (data->total_rooms == 2)
		return (0);
    if (data->end->parent == NULL)
	{
		printf("Error : no paths from start to end");
		return (-1);
	}
	del_no_lvl(array, queue);
	calculate_input_and_output(array, queue);
	delete_no_one_link(data, array, queue);
	del_input_forks(data, array, 0, queue);
	delete_no_one_link(data, array, queue);
	i = 0;
	if (queue)
	{
		while ((queue)[i])
		{
			free((queue)[i]);
			(queue)[i] = NULL;
			i++;
		}
		free(queue);
		queue = NULL;
	}
	return (0);
}


