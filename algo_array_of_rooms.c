#include "validator.h"

//
// Created by Peggie Donnie on 2019-11-28.
//
int			create_array_rooms(t_data *data, t_room ***array)
{
	t_room		*temp;

	temp = data->rooms;
	if (((*array) = (t_room **)malloc(sizeof(t_room*) * data->total_rooms)) == NULL)
		return (-1);
	while (temp)
	{
		(*array)[temp->num] = temp;
		temp = temp->next;
	}
	return (0);
}
