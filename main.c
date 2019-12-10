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
	/*
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
		printf("%s-%s\n", array[temp_link->a]->name, array[temp_link->b]->name); //  a = b = 32677 prev = error, next = a = 25 b = 0 (prev у некст тоже error)
		temp_link = temp_link->next;
	}
	 */
	printf("\n"); // одна линия тесты проходит две линии не проходит
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
	//int 	y;
	int 	i;
	int 	**queue;
	//t_link	*temp;
	t_lines	*line;


    fd = open("../mapp", O_RDONLY); //как сделать чтобы fd ловил < ?
    fill_data(&data);
    if ((line = validator(&data, fd)) == NULL)
    	return (-1);// дата удалить // универсальная функция + посмотреть случаи когда не успели записать в дата
    close(fd);
	array = NULL;
	if (create_array_rooms(&data, &array) == -1)
		return (-1);
	fill_array_rooms(&data, array);
	if (ft_create_queue(&data, &queue) == -1)
		return (-1);
	if (bfs(&data, array, queue) == -1) // когда определить, когда вообще нет пути ?
		return (-1);
	if (algo_prepare_graph(&data, array, queue) == -1)
		return (0); // нужно ли удалять 0 и когда удалять во время  удаления input forks ?
	if ((paths = (int**)malloc(sizeof(int*) * (data.end->input + 1))) == NULL)
		return (-1);
	i = -1;
	paths[data.end->input] = NULL;
	while (++i < data.end->input)
		paths[i] = NULL;
	/*
	i = -1;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			printf("%d ", queue[i][y]);
		}
		printf("\n");
	}
	temp = data.links;
	while (temp)
	{
		printf("%s-%s |", array[temp->a]->name, array[temp->b]->name);
		temp = temp->next;
	}
	printf("\n");
	*/
	/*
	y = 0;
	while (paths[y] != NULL)         ///!!!!! я когда удаляю звено и потом queu использую ???
	{
    	i = 1;
    	while (paths[y][i] != -1) // ошибка i = 0; y = 13;
		{
			printf("%s ", array[paths[y][i]]->name);
			i++;
		}
    	printf("\n");
    	y++;
	}
	 */
	//printf("Hello, World!\n");
	if (get_path(&data, array, paths) == -1)
		return (-1);
	print_ants_rooms_links(&data);
    ft_first(&data, array, paths, NULL);
    return 0;
}
