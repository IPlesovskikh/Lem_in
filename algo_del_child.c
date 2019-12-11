#include "validator.h"

static t_child	*del_first_child(int y, t_room **array, int i, t_child *temp)
{
	if (array[i]->child && array[i]->child->num == y)
	{
		array[i]->child = temp->next;
		if (array[i]->child)
			array[i]->child->prev = NULL;
		temp = array[i]->child;
	}
	else
	{
		array[i]->parent = temp->next;
		if (array[i]->parent)
			array[i]->parent->prev = NULL;
		temp = array[i]->parent;
	}
	return (temp);
}

void			del_child_or_parent(t_child	**child, int y, t_room **array, int i)
{
	t_child		*temp;
	t_child		*del;

	temp = (*child);
	while (temp->num != y)
		temp = temp->next;
	del = temp;
	if (temp->prev)
	{
		temp->prev->next = temp->next;
		if (temp->next)
			temp->next->prev = temp->prev;
		temp = temp->next;
	}
	else
		temp = del_first_child(y, array, i, temp);
	free(del);
	(*child) = temp;
}

