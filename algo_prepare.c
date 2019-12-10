
#include "validator.h"

void	del_child_or_parent(t_child	**child, int y, t_room **array, int i) // функцию отдельно сделать для парента и нет
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
/*
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
*/

static void	del_same_lvl_and_get_directions(t_data *data, t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*child;

	i = -1;
	while (queue[++i][0] != -1) // нужно ли у старта всех парентов удалять а у финиша всех детей ?
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			child = array[queue[i][y]]->child;
			while (child)
			{
				if (array[child->num]->level == array[queue[i][y]]->level)
					del_child_or_parent(&child, child->num, array, queue[i][y]);
				else if (array[child->num]->level < array[queue[i][y]]->level)
				{
					get_direction(child, array, queue[i][y]);
					del_child_or_parent(&child, child->num, array, queue[i][y]);
				}
				else
					child = child->next;
			}
		}
	}
	data->end->parent = data->end->child;
	data->end->child = NULL;
}

/*
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
 */

static void	del_no_lvl(t_data *data, t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*parent;
	t_child	*temp;

	i = -1;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			parent = array[queue[i][y]]->parent;
			while (parent)
			{
				if (array[parent->num]->level == -1)
				{
					//temp = array[parent->num]->child;
					//while (temp)
					//{
					//del_child_or_parent(&temp, temp->num, array, parent->num); //&child, child->num, array, queue[i][y]
					del_child_or_parent(&parent, parent->num, array, queue[i][y]);
					//}
				}
				else
					parent = parent->next;
			}
		}
	}
}

static void	calculate_input_and_output(t_data *data, t_room **array, int **queue)
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

static void		delete_no_one_link(t_data *data, t_room **array, int **queue)
{
	int 	i;
	int 	y;
	t_child	*child;
	t_child	*temp_parent;

	i = -1;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			child = array[queue[i][y]]->child;
			while (child)
			{
				if (array[child->num]->num != data->end->num && array[child->num]->output == 0)
				{
					temp_parent = array[child->num]->parent;
					del_child_or_parent(&temp_parent, queue[i][y], array, child->num);
					array[child->num]->input--;
					del_child_or_parent(&child, child->num, array, queue[i][y]);
					array[queue[i][y]]->output--;
				}
				else
					child = child->next;
			}
		}
	}
}

int			search_no_input_forks(t_data *data, t_room **array, t_child *parent)
{
	if (data->start->num != array[parent->num]->num && array[parent->num]->output == 1)
	{
		parent = array[parent->num]->parent;
		//while (parent)
		//{
		if (search_no_input_forks(data, array, parent) == 0) // в принципе при удалении всех инпутов до этого не возможно такой ситуации
			return (0); //parent = parent->next;
		else
			return (1);
		//}
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
			array[i]->parent->prev = NULL;
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

void		del_input_forks(t_data *data, t_room **array, int i, int **queue)
{
	int 	y;
	t_child	*parent;
	int 	status;

	i = 1;
	status = 0;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			if (array[queue[i][y]]->num != data->end->num && array[queue[i][y]]->input > 1)
			{
				parent = array[queue[i][y]]->parent;
				while (status == 0 && parent)
				{
					if (search_no_input_forks(data, array, parent) == 0)
						parent = parent->next;
					else
						status = 1;
				}
				if (status == 1)
					delete_fork(array, queue[i][y], parent);
				else
					delete_fork(array, queue[i][y], array[queue[i][y]]->parent);
			}
		}
	}
}

void		delete_no_lvl_from_end(t_data *data, t_room **array)
{
	t_child	*parent;

	parent = data->end->parent;
	while (parent)
	{
		if (array[parent->num]->num != data->start->num)
		{
			if (array[parent->num]->parent == NULL)
			{
				del_child_or_parent(&parent, parent->num, array, data->end->num);
				data->end->input--;
			}
			else
				parent = parent->next;
		}
		else
			parent = parent->next;
	}
}

void        delete_lvl_from_end(t_data *data, t_room **array)
{
    t_child     *parent;
    t_child     *child;
    int 		temp;

    parent = data->end->parent;
    while (parent)
    {
        child = array[parent->num]->parent;
        while (child)
        {
            if (array[child->num]->level > array[parent->num]->level)
			{
				temp = child->num;
            	del_child_or_parent(&child, child->num, array, parent->num);
            	del_child_or_parent(&(array[temp]->child), parent->num, array, temp);
			}
            else
            	child = child->next;
        }
        parent = parent->next;
    }
}

void		del_queue(t_room **array, int **queue)
{
	int 	i;
	int 	y;
	int 	temp;
	int 	status;

	i = 0;
	while (queue[++i][0] != -1)
	{
		y = -1;
		while (queue[i][++y] != -1)
		{
			if (array[queue[i][y]]->level == -1 || array[queue[i][y]]->input == 0 ||
				array[queue[i][y]]->output == 0)
			{
				temp = y;
				status = 0;
				while (status == 0)
				{
					if (queue[i][temp + 1] == -1)
						status = 1;
					array[queue[i][temp]] = array[queue[i][temp + 1]];
					temp++;
				}
				y--;
			}
		}
	}
}

int			algo_prepare_graph(t_data *data,t_room **array,int **queue)
{
	del_same_lvl_and_get_directions(data, array, queue);
	if (data->total_rooms == 2)
		return (0);
	delete_lvl_from_end(data, array);// зачем это ? вроде и так уже нет // тут падает - не потому как в бфс я удаляю на последнем уровне но не удаляю у тех кого удлали, а что с предпоследней строчкой она правильная ?
    if (data->end->parent == NULL)
	{
		printf("Error : no paths from start to end");
		return (-1);
	}
	del_no_lvl(data, array, queue);
	calculate_input_and_output(data, array, queue);
	delete_no_one_link(data, array, queue);
	//del_queue(array, queue);
	del_input_forks(data, array, 0, queue);
	delete_no_one_link(data, array, queue);
	//delete_no_lvl_from_end(data, array);
	return (0);
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


