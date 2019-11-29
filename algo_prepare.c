
#include "validator.h"

static void	del_child_or_parent(t_child	**child, t_room **array, int i)
{
	t_child		*temp;

	if ((*child)->prev)
	{
		(*child)->prev->next = (*child)->next;
		if ((*child)->next)
			(*child)->next->prev = (*child)->prev->next;
	}
	else
	{
		array[i]->child = (*child)->next;
		if (array[i]->child)
			array[i]->child->prev = NULL;
	}
	temp = (*child)->next;
	free(*child);
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

static void	del_same_lvl_and_get_directions(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;

	i = 0;
	max = data->total_rooms;
	while (i < max)
	{
		child = array[i]->child;
		while (child && array[child->num]->level != -1)
		{
			if (array[i]->level == array[child->num]->level)
				del_child_or_parent(&child, array, i);
			else if (array[i]->level > array[child->num]->level)
			{
				get_direction(child, array, i);
				del_child_or_parent(&child, array, i);
			}
			else
				child = child->next;
		}
		i++;
	}
}

static void	del_no_lvl(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;

	i = 0;
	max = data->total_rooms;
	while (i < max)
	{
		if (array[i]->level == -1)
		{
			child = array[i]->child;
			while (child)
			{
				del_child_or_parent(&(array[child->num]->parent), array, child->num);
				array[child->num]->input--;
				del_child_or_parent(&child, array, i);
				array[i]->output--;
			}
		}
		i++;
	}
}

static void	calculate_input_and_output(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;

	i = 0;
	max = data->total_rooms;
	while (i < max)
	{
		child = array[i]->child;
		while (child)
		{
			array[i]->output++;
			array[child->num]->input++;
			child = child->next;
		}
		i++;
	}
}

static void		delete_no_one_link(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;

	i = -1;
	max = data->total_rooms;
	while (++i < max)
	{
		child = array[i]->child;
		while (child && array[child->num]->num != data->end->num &&
						  array[child->num]->num != data->start->num)
		{
			if (array[child->num]->output == 0)
			{
				del_child_or_parent(&(array[child->num]->parent), array, child->num);
				array[child->num]->input--;
				del_child_or_parent(&child, array, i);
				array[i]->output--;
			}
			else
				child = child->next;
		}
	}
}

void		del_input_forks(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*parent;
	t_child *temp;
	t_child *temp_more_then_one;
	int 	y;

	i = 0;
	max = data->total_rooms;
	while (++i < max)
	{
		if (array[i]->input > 1)
		{
			parent = array[i]->parent;
			while (parent)
			{
				if (array[parent->num]->output == 1)
				{
					temp = array[i]->parent;
					while (temp)
					{
						if (temp->num == parent->num)
						{
							del_child_or_parent(&(array[parent->num]->parent), array, parent->num);
							array[parent->num]->output--;
							del_child_or_parent(&parent, array, i);
							array[i]->input--;
						}
						else
							temp = temp->next;
					}
				}
				else if ()
				parent = parent->next;
			}
		}
	}
}

void		algo_prepare_graph(t_data *data, t_room **array)
{
	del_same_lvl_and_get_directions(data, array);
	del_no_lvl(data, array);
	calculate_input_and_output(data, array);
	delete_no_one_link(data, array);
	//rooms 6 7 8 2 inputs ; room 9 3 outputs 2 inputs и instead room 4 we have room 10 as child
	// считать инпуты старта надо ? может заранее удалить все?
	del_input_forks(data, array);
}


