
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