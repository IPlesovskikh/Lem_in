#include "validator.h"

//
// Created by Peggie Donnie on 2019-11-28.
//
int			create_array_rooms(t_data *data, t_room ***array)
{
	t_room	*temp;

	temp = data->rooms;
	if (((*array) = (t_room **)malloc(sizeof(t_room*) * data->total_rooms)) == NULL)
		return (-1);
	while (temp)
	{
		(*array)[temp->num] = temp;
		temp = temp->next;
	}
	return (0);
}

void		add_child(int parent, t_room **array, int children)
{
	t_child	*child;

	if (array[parent]->child == NULL)
	{
		array[parent]->child = (t_child*)malloc(sizeof(t_child));
		child = array[parent]->child;
		child->prev = NULL;
	}
	else
	{
		child = array[parent]->child;
		while (child->next != NULL)
			child = child->next;
		child->next = (t_child*)malloc(sizeof(t_child));
		child->next->prev = child;
		child = child->next;
	}
	child->num = children;
}

void		fill_array_rooms(t_data *data, t_room **array)
{
	t_link	*temp;

	temp = data->links;
	while (temp != NULL)
	{
		add_child(temp->a, array, temp->b);
		add_child(temp->b, array, temp->a);
		temp = temp->next;
	}
}