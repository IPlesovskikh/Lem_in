#include "validator.h"

void    fill_data(t_data *data)
{
	data->ants = 0;
	data->end = NULL;
	data->start = NULL;
	data->links = NULL;
	data->rooms = NULL;
	data->total_rooms = 0;
	data->total_paths = 0;
	data->k = 1;
	data->order = 0;
	data->first_line_print = NULL;
	data->ant_order = 1;
	data->ants_max = 0;
	data->ants_min = 0;
}

int 	ft_create_queue(t_data *data, int ***queue)
{
	int 	i;

	if (((*queue) = (int**)malloc(sizeof(int*) *
								  (data->total_rooms + 1))) == NULL)
		return (print_error());
	(*queue)[data->total_rooms] = NULL;
	i = -1;
	while (++i < data->total_rooms)
	{
		if (((*queue)[i] = (int*)malloc(sizeof(int) *
										data->total_rooms)) == NULL)
			return (print_error());
		(*queue)[i][0] = -1;
	}
	return (0);
}

int		create_paths(t_data *data, int ***paths)
{
	int 	i;

	if (((*paths) = (int**)malloc(sizeof(int*) *
			(data->end->input + 1))) == NULL)
		return(print_error());
	i = -1;
	(*paths)[data->end->input] = NULL;
	while (++i < data->end->input)
		(*paths)[i] = NULL;
	return (0);
}

void	ft_fill_room(t_room *room)
{
	room->next = NULL;
	room->name = NULL;
	room->x = 0;
	room->y = 0;
	room->level = -1;
	room->input = 0;
	room->output = 0;
	room->child = NULL;
	room->parent = NULL;
}

int 	ft_create_link(t_link **temp_link, t_data *data)
{
	t_link	*temp;

	if (data->links)
	{
		if ((temp = (t_link*)malloc(sizeof(t_link))) == NULL)
			return (-1);
		(*temp_link)->next = temp;
		(*temp_link)->next->prev = (*temp_link);
		(*temp_link) = (*temp_link)->next;
	}
	else
	{
		if ((data->links = (t_link*)malloc(sizeof(t_link))) == NULL)
			return (-1);
		(*temp_link) = data->links;
		(*temp_link)->prev = NULL;
	}
	(*temp_link)->next = NULL;
	(*temp_link)->a = -1;
	(*temp_link)->b = -1;
	return (0);
}