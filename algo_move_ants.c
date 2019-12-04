//
// Created by Peggie Donnie on 2019-12-01.
//

#include "validator.h"

void	move_ants(t_room **array, int *paths, int j, int k)
{
	j++;
	if (j == paths[0])
		return ;
	else
		printf("L%d-%s ", k, array[paths[j]]->name);
}

t_ant	*ft_create_ant(int i, int k, t_ant *prev_ant)
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
	ant->name = k;
	return (ant);
}

void 	ft_first(t_data *data, t_room **array, int **paths, t_ant *ant)
{
	int			i;
	int 		j;
	int 		sum;
	t_ant		*tmp;

	i = 0;
	j = 0;
	sum = 0;
	while (data->ants > 0 && i < data->total_paths && data->ants > sum)
	{
		while (j < i)
		{
			sum = sum + (paths[j + 1][0] - paths[j][0]);
			j++;
		}
		if (data->ants > sum)
		{
			ant = ft_create_ant(i, data->k, ant);
			data->ants--;
			i++;
			data->k++;
		}
	}
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
	if (ant->j <= paths[ant->i][0])
	{
		printf("L%d-%s ", ant->name, array[paths[ant->i][ant->j]]->name);
		ant->j++;
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
	if (ant == NULL)
		return ;
	else
	{
		printf("\n");
		ft_first(data, array, paths, ant);
	}
}
