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

	(*queue) = (int**)malloc(sizeof(int*) * data->total_rooms);
	i = -1;
	while (++i < data->total_rooms)
	{
		(*queue)[i] = (int*)malloc(sizeof(int) * data->total_rooms);
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
    fd = open("../mapp", O_RDONLY); //как сделать чтобы fd ловил < ?
    fill_data(&data);
    if ((validator(&data, fd)) == -1)
    	return (ft_free(&data, &array));// дата удалить // универсальная функция + посмотреть случаи когда не успели записать в дата
    close(fd);
	if (create_array_rooms(&data, &array) == -1)
		return (ft_free(&data, &array));
	fill_array_rooms(&data, array);
	if (ft_create_queue(&data, &queue) == -1)
		return (ft_free(&data, &array));
	if (bfs(&data, array, queue) == -1) // когда определить, когда вообще нет пути ?
		return (ft_free(&data, &array));
	if (algo_prepare_graph(&data, array, queue) == -1)
		return (ft_free(&data, &array)); // нужно ли удалять 0 и когда удалять во время  удаления input forks ?
	if ((paths = (int**)malloc(sizeof(int*) * (data.end->input + 1))) == NULL)
		return (ft_free(&data, &array));
	i = -1;
	paths[data.end->input] = NULL;
	while (++i < data.end->input)
		paths[i] = NULL;
	if (get_path(&data, array, paths) == -1)
		return (ft_free(&data, &array));
	print_ants_rooms_links(&data);
    ft_first(&data, array, paths, NULL);
    return 0;
}
