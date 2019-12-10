#include <stdio.h>
#include "validator.h"

void 	print_ants_rooms_links(t_data *data)
{
	t_lines 	*temp;

	temp = data->first_line_print;
	while (temp)
	{
		printf("%s\n", temp->line);
		temp = temp->next;
	}
	printf("\n");
}

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

	if (((*queue) = (int**)malloc(sizeof(int*) * (data->total_rooms + 1))) == NULL)
		return (-1);
	(*queue)[data->total_rooms] = NULL;
	i = -1;
	while (++i < data->total_rooms)
	{
		if (((*queue)[i] = (int*)malloc(sizeof(int) * data->total_rooms)) == NULL)
			return (-1);
		(*queue)[i][0] = -1;
	}
	return (0);
}

int main()
{
    t_data  data;
    int     fd;
	t_room	**array;
	int 	**paths;
	int 	i;
	int 	**queue;

	array = NULL;
	queue = NULL;
    fd = open("../mapp", O_RDONLY);
    fill_data(&data);
    if ((validator(&data, fd)) == -1)
    	return (ft_free(&data, &array, &queue));
    close(fd);
	if (create_array_rooms(&data, &array) == -1)
		return (ft_free(&data, &array, &queue));
	fill_array_rooms(&data, array);
	if (ft_create_queue(&data, &queue) == -1)
		return (ft_free(&data, &array, &queue));
	if (bfs(&data, array, queue) == -1)
		return (ft_free(&data, &array, &queue));
	if (algo_prepare_graph(&data, array, queue) == -1)
		return (ft_free(&data, &array, &queue));
	if ((paths = (int**)malloc(sizeof(int*) * (data.end->input + 1))) == NULL)
		return (ft_free(&data, &array, &paths));
	i = -1;
	paths[data.end->input] = NULL;
	while (++i < data.end->input)
		paths[i] = NULL;
	if (get_path(&data, array, paths) == -1)
		return (ft_free(&data, &array, &paths));
	print_ants_rooms_links(&data);
    ft_first(&data, array, paths, NULL);
    return (ft_free(&data, &array, &paths));
}
