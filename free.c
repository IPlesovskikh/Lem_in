

#include "validator.h"

static 	void	ft_delete_child(t_child *child)
{
	t_child		*temp;

	while (child)
	{
		temp = child->next;
		free(child);
		child = temp;
	}
}

static void		ft_delete_rooms(t_room **rooms)
{
	t_room *temp;

	while (*rooms)
	{
		temp = (*rooms)->next;
		free((*rooms)->name);
		(*rooms)->name = NULL;
		if ((*rooms)->parent)
			ft_delete_child((*rooms)->parent);
		(*rooms)->parent = NULL;
		if ((*rooms)->child)
			ft_delete_child((*rooms)->child);
		(*rooms)->child = NULL;
		free(*rooms);
		(*rooms) = temp;
	}
	(*rooms) = NULL;
}

static void		ft_delete_links(t_link **links)
{
	t_link	*temp;

	while (*links)
	{
		temp = (*links)->next;
		free((*links));
		(*links) = temp;
	}
	(*links) = NULL;
}

static void 	free_lines(t_lines **line)
{
	t_lines		*temp;

	while (*line)
	{
		temp = (*line)->next;
		free((*line)->line);
        (*line)->line = NULL;
		free((*line));
		(*line) = temp;
	}
	(*line) = NULL;
}

int		ft_free(t_data *data, t_room ***array, int ***numbers)
{
	int 	i;

	if (data->links)
		ft_delete_links(&(data->links));
	if (data->rooms)
		ft_delete_rooms(&(data->rooms));
	if ((data)->first_line_print)
		free_lines(&(data->first_line_print));
	if (*array)
		free(*array);
	i = 0;
	if (*numbers)
	{
		while ((*numbers)[i])
		{
			free((*numbers)[i]);
			(*numbers)[i] = NULL;
			i++;
		}
		free(*numbers);
		(*numbers) = NULL;
	}
	return (0);
}
