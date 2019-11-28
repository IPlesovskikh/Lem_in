//
// Created by Peggie Donnie on 2019-11-28.
//

#include "validator.h"

void		ft_put_child(t_child *temp_child, t_room **array, int **queue, int i)
{
	int 	y;

	y = 0;
	while (queue[i][y] != -1)
		y++;
	while (temp_child)
	{
		array[temp_child->num]->level = i;
		queue[i][y++] = temp_child->num;
		temp_child = temp_child->next;
	}
	queue[i][y] = -1;
}

int				bfs(t_data *data, t_room **array)
{
	t_room		*temp_room;
	int 		i;
	int 		**queue;
	int 		y;

	queue = (int**)malloc(sizeof(int*) * data->total_rooms);
	i = data->total_rooms;
	while (i < data->total_rooms)
	{
		queue[i] = (int*)malloc(sizeof(int) * data->total_rooms);
		queue[i++][0] = -1;
	}
	temp_room = array[data->start->num];
	temp_room->level = 0;
	data->end->level = 2147483647;
	i = 0;
	while (temp_room->level != 2147483647)
	{
		y = 0;
		ft_put_child(temp_room->child, array, queue, i + 1);

		temp_room = array[queue[i][]]
	}
	return (0);
}