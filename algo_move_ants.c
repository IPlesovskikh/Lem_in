
#include "validator.h"

static t_ant	*ft_create_ant(int i, int k, t_ant *prev_ant, int ant_order)
{
	t_ant	*ant;

	if ((ant = malloc(sizeof(t_ant))) == NULL)
		exit (-1);
	if (k != 1)
	{
		ant->prev = prev_ant;
		prev_ant->next = ant;
		ant->next = NULL;
	}
	else
	{
		ant->prev = NULL;
		ant->next = NULL;
	}
	ant->i = i;
	ant->j = 2;
	ant->name = ant_order;
	return (ant);
}

t_ant	*ft_move(t_ant *ant, int **paths, t_room **array)
{
	t_ant		*tmp;

	while (ant->prev != NULL)
		ant = ant->prev;
	while (ant->next != NULL)
	{
		if (ant->j <= paths[ant->i][0])
		{
			printf("L%d-%s ", ant->name, array[paths[ant->i][ant->j]]->name);
			ant->j++;
			ant = ant->next;
		}
		else
		{
			tmp = ant;
			ant = ant->next;
			if (ant != NULL)
				ant->prev = tmp->prev;
			if (tmp->prev != NULL)
				(tmp->prev)->next = ant;
			free(tmp);
		}
	}
	return (ant);
}

static t_ant	*choose_path(t_data *data, t_ant * ant, int **paths)
{
	int			i;
	int 		j;
	int 		sum;

	i = 0;
	j = 0;
	sum = 0;
	while (data->ants_max > data->ants_min && i < data->total_paths &&
		(data->ants_max - data->ants_min) > sum)
	{
		while (j < i)
		{
			sum = sum + (paths[j + 1][0] - paths[j][0]);
			j++;
		}
		if ((data->ants_max - data->ants_min) > sum)
		{
			ant = ft_create_ant(i, data->k, ant, data->ant_order);
			data->ants_max--;
			i++;
			data->k++;
			data->ant_order++;
		}
	}
	return (ant);
}

t_ant	*ft_check_ant(t_ant *ant)
{
	t_ant		*tmp;

	if (ant != NULL && ant->next != NULL)
	{
		tmp = ant;
		ant = ant->next;
		if (ant != NULL)
			ant->prev = tmp->prev;
		if (tmp->prev != NULL)
			(tmp->prev)->next = ant;
		free(tmp);
	}
	else
	{
		tmp = ant;
		if (ant->prev == NULL && ant->next == NULL)
		{
			free(ant);
			return (NULL);
		}
		ant = ant->prev;
		ant->next = NULL;
		free(tmp);
	}
	return (ant);
}

void 	move_ants(t_data *data, t_room **array, int **paths, t_ant *ant)
{
	ant = choose_path(data, ant, paths);
	ant = ft_move(ant, paths, array);
	if (ant->j <= paths[ant->i][0])
	{
		printf("L%d-%s ", ant->name, array[paths[ant->i][ant->j]]->name);
		ant->j++;
	}
	else
		if ((ant = ft_check_ant(ant)) == NULL)
			return ;
	if (ant == NULL)
		return ;
	else
	{
		printf("\n");
		move_ants(data, array, paths, ant);
	}
}
