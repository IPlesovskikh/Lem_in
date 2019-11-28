
#include "validator.h"

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
			if (array[i]->level >= array[child->num]->level)
			{
				if (child->prev)
				{
					child->prev->next = child->next;
					if (child->next)
						child->next->prev = child->prev->next;
				}
				else
				{
					array[i]->child = child->next;
					if (array[i]->child)
						array[i]->child->prev = NULL;
				}
				temp = child->next;
				free(child);
				child = temp;
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

void		algo_prepare_graph(t_data *data, t_room **array)
{
	del_same_lvl_and_get_directions(data, array);
	calculate_input_and_output(data, array);
}


