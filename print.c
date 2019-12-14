//
// Created by Peggie Donnie on 2019-12-11.
//

#include "validator.h"

int 	print_error(void)
{
	printf("ERROR\n");
	return (-1);
}

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