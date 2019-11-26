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

    printf("Hello, World!\n");
    fd = open("../mapp", O_RDONLY);
    fill_data(&data);
    validator(&data, fd); // дата удалить // универсальная функция + посмотреть случаи когда не успели записать в дата
    close(fd);
    printf("Hello, World!\n");
    return 0;
}