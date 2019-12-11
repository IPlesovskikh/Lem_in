#include "validator.h"

static void	change_first_element(t_room *end, t_child *parent)
{
	end->parent = end->parent->next;
	parent->prev = end->parent;
	parent->next = end->parent->next;
	if (parent->next)
		parent->next->prev = parent;
	end->parent->next = parent;
	end->parent->prev = NULL;
}

void 		sort_childs(t_room **array, t_room *end, t_child *parent)
{
	while (parent->next)
	{
		if (array[parent->num]->level > array[parent->next->num]->level)
		{
			if (parent->prev)
			{
				parent->prev->next = parent->next;
				parent->next->prev = parent->prev;
				parent->prev = parent->next;
				parent->next = parent->next->next;
				if (parent->next)
					parent->next->prev = parent;
				parent->prev->next = parent;
			}
			else
				change_first_element(end, parent);
			parent = end->parent;
		}
		else
			parent = parent->next;
	}
}

void		check_path(t_room **array, int start, t_child *parent, int end)
{
	t_child		*child;
	int			status;

	while (parent)
	{
		child = array[parent->num]->parent;
		status = 0;
		while (status == 0 && child)
		{
			if (child->num == start)
				status = 1;
			else
				child = array[child->num]->parent;
		}
		if (status == 0 && parent->num != start)
			del_child_or_parent(&parent, parent->num, array, end);
		else
			parent = parent->next;
	}
}





