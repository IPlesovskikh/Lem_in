#include <stdio.h>
#include "validator.h"

void    fill_data(t_data *data)
{
    data->ants = 0;
    data->end = NULL;
    data->start = NULL;
    data->links = NULL;
}

int main()
{
    t_data  data;
    int     fd;
	t_room	**array;
	int 	**paths;
	int 	y;
	int 	i;

    printf("Hello, World!\n");
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
	algo_prepare_graph(&data, array);
	paths = (int**)malloc(sizeof(int*) * (data.end->output + 1));
	paths[data.end->output] = NULL;
	get_path(&data, array, paths);
	y = 0;
    while (paths[y] != NULL) // что делать со строками которые не заполнил но остались
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
    return 0;
}