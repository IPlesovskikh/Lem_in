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
	t_room		**array;

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
	algo_prepare_graph(&data, array); // иногда проскакивает сига add_child while (child->next != NULL) child = child->next;
	// когда есть лвл не меняю но возможно надо сравнивать лвл, нет ?
    printf("Hello, World!\n");
    return 0;
}