//
// Created by Peggie Donnie on 2019-11-28.
//

#include "validator.h"

int				bfs(t_data *data, t_room **array)
{
	t_room		*temp_room;
	t_child		*temp_child;
	int 		i;

	temp_room = array[data->start->num];
	temp_room->level = 0;
	data->end->level = 2147483647;
	i = 1;
	while (temp_room->level != 2147483647)
	{
		temp_child = temp_room->child;
		while (temp_child)
		{
			array[temp_child->num]->level = i;
			temp_child = temp_child->next;
		}
		i++;
		temp_room = 
	}
	return (0);
}