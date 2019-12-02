
#include "validator.h"

static void	del_child_or_parent(t_child	**child, int y, t_room **array, int i)
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
	}
	free(del);
	(*child) = temp;
}

static void	get_direction(t_child *child, t_room **array, int i)
{
	t_child	*parent;

	parent = array[i]->parent;
	if (parent)
	{
		while (parent->next)
			parent = parent->next;
		parent->next = (t_child *) malloc(sizeof(t_child));
		parent->next->prev = parent;
		parent->next->num = child->num;
		parent->next->next = NULL;
	}
	else
	{
		array[i]->parent = (t_child*)malloc(sizeof(t_child));
		array[i]->parent->prev = NULL;
		array[i]->parent->next = NULL;
		array[i]->parent->num = child->num;
	}
}

static void	del_same_lvl_and_get_directions(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;

	i = 0;
	max = data->total_rooms;
	while (i < max)
	{
		child = array[i]->child;
		while (child && array[child->num]->level != -1)
		{
			if (array[i]->level == array[child->num]->level)
				del_child_or_parent(&child, child->num, array, i);
			else if (array[i]->level > array[child->num]->level)
			{
				get_direction(child, array, i);
				del_child_or_parent(&child, child->num, array, i);
			}
			else
				child = child->next;
		}
		i++;
	}
}

static void	del_no_lvl(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;

	i = 0;
	max = data->total_rooms;
	while (i < max)
	{
		if (array[i]->level == -1)
		{
			child = array[i]->child;
			while (child)
			{
				del_child_or_parent(&(array[child->num]->child), i, array, child->num);
				del_child_or_parent(&child, child->num, array, i);
			}
		}
		i++;
	}
}

static void	calculate_input_and_output(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;

	i = 0;
	max = data->total_rooms;
	while (i < max)
	{
		child = array[i]->child;
		while (child)
		{
			array[i]->output++;
			array[child->num]->input++;
			child = child->next;
		}
		i++;
	}
}

static void		delete_no_one_link(t_data *data, t_room **array)
{
	int 	i;
	int 	max;
	t_child	*child;
	t_child	*temp_parent;

	i = -1;
	max = data->total_rooms;
	while (++i < max)
	{
		child = array[i]->child;
		while (child && array[child->num]->num != data->end->num &&
						  array[child->num]->num != data->start->num)
		{
			if (array[child->num]->output == 0)
			{
				temp_parent = array[child->num]->parent;
				del_child_or_parent(&temp_parent, i, array, child->num);
				array[child->num]->input--;
				del_child_or_parent(&child, child->num, array, i);
				array[i]->output--;
			}
			else
				child = child->next;
		}
	}
}

int			search_no_input_forks(t_data *data, t_room **array, t_child *parent, int i)
{
	if (data->start->num != array[parent->num]->num && array[parent->num]->output == 1)
	{
		parent = array[parent->num]->parent;
		while (parent)
		{
			if (search_no_input_forks(data, array, parent, parent->num) == 0)
				parent = parent->next;
			else
				return (1);
		}
	}
	else if (data->start->num == array[parent->num]->num)
		return (1);
	return (0);
}

void		delete_fork(t_room **array, int i, t_child *parent)
{
	t_child		*temp;
	t_child		*temp_parent;

	temp = array[i]->parent;
	while (temp)
	{
		if (temp->num == parent->num)
		{
			temp = temp->next;
			array[i]->parent = parent;
			array[i]->parent->next = NULL;
		}
		else
		{
			temp_parent = array[temp->num]->child;
			del_child_or_parent(&temp_parent, i, array, temp->num);
			array[temp->num]->output--;
			del_child_or_parent(&temp, temp->num, array, i);
			array[i]->input--;
		}
	}
}

void		del_input_forks(t_data *data, t_room **array, int i)
{
	int 	max;
	t_child	*parent;
	int 	status;

	max = data->total_rooms;
	status = 0;
	while (++i < max)
	{
		if (array[i]->num != data->end->num && array[i]->num !=
				data->start->num && array[i]->input > 1)
		{
			parent = array[i]->parent;
			while (status == 0 && parent)
			{
				if (search_no_input_forks(data, array, parent, i) == 0)
					parent = parent->next;
				else
					status = 1;
			}
			if (status == 1)
				delete_fork(array, i, parent);
			else
				delete_fork(array, i, array[i]->parent);
		}
	}
}


void		algo_prepare_graph(t_data *data, t_room **array)
{
	del_same_lvl_and_get_directions(data, array);
	del_no_lvl(data, array);
	calculate_input_and_output(data, array);
	delete_no_one_link(data, array);
	// считать инпуты старта надо ? может заранее удалить все?
	del_input_forks(data, array, 0);
	delete_no_one_link(data, array);
}
/*
нужно удалить путь если :
длина пути будет больше у пути который имеет общую вершина с аутпутом больше чем 1

создаем массив указателей на строки (по количеству инпутов)
начинаем с конца
ищем детей чей аутпут больше 1
начинаем с ребенка наименьше лвл, формируем путь (длина равна длине лвл и сам путь это массив интов)
следующий лвл движимся пока не найдем вилку

если есть вилка, ищем, если ли такое звено в уже сформированном пути (сравниваем инты)
если нет то формируем путь (создаем сроку в массиве)
если есть то если данный путь равен по длине иди больше, начинаем чекать следующей child
*/


