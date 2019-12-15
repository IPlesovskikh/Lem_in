
#include "validator.h"

int		ft_check_comment(t_lines **lines)
{
	int		i;

	i = 0;
	while (i == 0)
	{
		if ((*lines)->line[0] == '#' && (*lines)->line[1] == '#')
			return (-1);
		else if ((*lines)->line[0] == '#')
			(*lines) = (*lines)->next;
		else
			i++;
	}
	return (0);
}

int		skip_comments(int status, t_data *data, t_lines **lines, int fd)
{
	char	*line;

	while (status == 2 && (status = get_next_line(fd, &line)) > 0)
	{
		status = (line[0] == '#' && line[1] != '#') ? 2 : status;
		if (*lines)
		{
			if (((*lines)->next = (t_lines*)malloc(sizeof(t_lines))) == NULL)
				return (-1);
			(*lines) = (*lines)->next;
			(*lines)->line = line;
			(*lines)->next = NULL;
		}
		else
		{
			if (((*lines) = (t_lines*)malloc(sizeof(t_lines))) == NULL)
				return (-1);
			(*lines)->line = line;
			(*lines)->next = NULL;
			data->first_line_print = (*lines);
		}
	}
	if (status <= 0)
		return (-1);
	return (0);
}

void 	start_move(t_data *data, int *max, int *min)
{
	if (data->k > 1)
		data->k -= 65000;
	if (data->ants > *max)
	{
		data->ants_max = *max;
		data->ants_min = *min;
		data->ants -= 65000;
		*max += 65000;
		*min += 65000;
	}
	else
	{
		data->ants_max = data->ants;
		data->ants_min = 0;
		data->ants = 0;
	}
}

void  move_ant(t_data *data, t_room **array, int **paths)
{
	int 	max;
	int 	min;

	max = 65000;
	min = 0;
	while (data->ants)
	{
		start_move(data, &max, &min);
		move_ants(data, array, paths, NULL);
	}
}
