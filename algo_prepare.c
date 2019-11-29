
#include "validator.h"

static void	del_same_lvl(t_child	**child, t_child **temp, t_room **array, int i)
{
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
	(*temp) = (*child)->next;
	free(*child);
	(*child) = (*temp);
}

static void	get_direction(t_child **child, t_child **temp, t_room **array, int i)
{
	t_child	*parent;

	parent = array[i]->parent;
	if (parent)
	{
		while (parent->next)
			parent = parent->next;
		parent->next = (t_child *) malloc(sizeof(t_child));
		parent->next->prev = parent;
		parent->next->num = (*child)->num;
		parent->next->next = NULL;
	}
	else
	{
		array[i]->parent = (t_child*)malloc(sizeof(t_child));
		array[i]->parent->prev = NULL;
		array[i]->parent->next = NULL;
		array[i]->parent->num = (*child)->num;
	}
}

static void	del_same_lvl_and_get_directions(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;
	t_child	*temp;

	i = 0;
	max = data->total_rooms;
	while (i < max)
	{
		child = array[i]->child;
		while (child)
		{
			if (array[i]->level == array[child->num]->level)
				del_same_lvl(&child, &temp, array, i);
			else if (array[i]->level > array[child->num]->level)
			{
				get_direction(&child, &temp, array, i);
				del_same_lvl(&child, &temp, array, i);
			}
			else
				child = child->next;
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
		if (array[i]->level != -1)
		{
			child = array[i]->child;
			while (child)
			{
				array[i]->output++;
				array[child->num]->input++;
				child = child->next;
			}
		}
		i++;
	}
}

void		delete_no_one_link(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;
	t_child	*temp;

	i = -1;
	max = data->total_rooms;
	while (++i < max)
	{
		child = array[i]->child;
		while (child && array[child->num]->num != data->end->num &&
						  array[child->num]->num != data->start->num)
		{
			if (array[child->num]->input == 0 ||
				array[child->num]->output == 0)
			{
				temp = (child->next) ? child->next : NULL;
				if (child->prev)
					child->prev->next = temp;
				else if (!(child->prev))
					array[child->num]->child = temp;
				array[child->num]->input--;
				array[i]->output--;
				free(child);
				child = (temp) ? child : NULL;
			}
			else
				child = child->next;
		}
	}
}

void		algo_prepare_graph(t_data *data, t_room **array)
{
	del_same_lvl_and_get_directions(data, array);
	calculate_input_and_output(data, array);
	delete_no_one_link(data, array);
}


