#include <stdio.h>
#include "validator.h"

void 	print_ants_rooms_links(t_data *data, t_room **array)
{
	t_room		*temp_room;
	t_link		*temp_link;

	printf("%d\n", data->ants);
	temp_room = data->rooms;
	while (temp_room != NULL)
	{
		if (temp_room->num == data->end->num)
			printf("##end\n");
		else if (temp_room->num == data->start->num)
			printf("##start\n");
		printf("%s %d %d\n", temp_room->name, temp_room->x, temp_room->y);
		temp_room = temp_room->next;
	}
	temp_link = data->links;
	while (temp_link != NULL)
	{
		printf("%s-%s\n", array[temp_link->a]->name, array[temp_link->b]->name);
		temp_link = temp_link->next;
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
}

int main()
{
    t_data  data;
    int     fd;
	t_room	**array;
	int 	**paths;
	int 	y;
	int 	i;

    fd = open("../mapp", O_RDONLY);
    fill_data(&data);
    if (validator(&data, fd) == -1)
    	return (-1);// дата удалить // универсальная функция + посмотреть случаи когда не успели записать в дата
    close(fd);
	array = NULL;
	if (create_array_rooms(&data, &array) == -1)
		return (-1);
	fill_array_rooms(&data, array);
	if (bfs(&data, array) == -1) // когда определить, когда вообще нет пути ?
		return (-1);
	if (algo_prepare_graph(&data, array) == -1)
		return (0); // нужно ли удалять 0 и когда удалять во время  удаления input forks ?
	paths = (int**)malloc(sizeof(int*) * (data.end->input + 1));
	paths[data.end->input] = NULL;
	get_path(&data, array, paths);
	/*
	y = 0;
    while (paths[y] != NULL)
	{
    	i = 0;
    	while (paths[y][i] != -1)
		{
			printf("%i", paths[y][i]);
			i++;
		}
    	printf("\n");
    	y++;
	}
	printf("Hello, World!\n");
	 */
	print_ants_rooms_links(&data, array);
    ft_first(&data, array, paths, NULL);
    return 0;
}