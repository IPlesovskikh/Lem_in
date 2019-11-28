
#include "validator.h"

static void	del_useless_links(t_data *data, t_room **array)
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
			{
				child->prev->next = child->next;
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

void	algo_prepare_graph(t_data *data, t_room **array)
{
	del_useless_links(data, array);
	
}


