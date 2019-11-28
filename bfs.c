//
// Created by Peggie Donnie on 2019-11-28.
//

#include "validator.h"

int				bfs(t_data *data, t_room **array)
{
	t_room		*temp;

	temp = array[data->start->num];
	temp->level = 0;
	data->end->level = 2147483647;
	while (temp)
	{

	}

}