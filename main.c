#include <stdio.h>
#include "validator.h"

int main()
{
    t_data  data;
    int     fd;
	t_room	**array;
	int 	**paths;
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
	bfs(&data, array, queue);
	if (algo_prepare_graph(&data, array, &queue) == -1 ||
		create_paths(&data, &paths) == -1 ||
			get_path(&data, array, paths) == -1)
		return (ft_free(&data, &array, &queue));
	print_ants_rooms_links(&data);
	move_ant(&data, array, paths);
    return (ft_free(&data, &array, &paths));
}
