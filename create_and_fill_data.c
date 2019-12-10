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