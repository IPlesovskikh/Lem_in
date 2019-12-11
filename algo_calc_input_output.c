
#include	"validator.h"

void			calculate_input_and_output(t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*child;

	i = -1;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			child = array[queue[i][y]]->child;
			while (child)
			{
				array[queue[i][y]]->output++;
				array[child->num]->input++;
				child = child->next;
			}
		}
	}
}