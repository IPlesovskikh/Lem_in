#include "validator.h"

int 		get_x(int *i, t_room *temp, t_lines *lines)
{
	int 	i2;

	while (lines->line[*i] == ' ' || lines->line[*i] == '\t')
		(*i)++;
	i2 = *i;
	if (lines->line[*i] == '+' || lines->line[*i] == '-')
		(*i)++;
	while (lines->line[*i] != '\0' && lines->line[*i] != ' ' && lines->line[*i] != '\t')
		if (ft_isdigit(lines->line[(*i)++]) == 0)
			return (-1);
	if ((*i) == i2)
		return (-1);
	if ((temp->x = ft_atoi(&(lines->line[i2]))) == 0)
	{
		if (lines->line[i2] == '+' || lines->line[i2] == '-')
			i2++;
		if (lines->line[i2] == '\0' || (lines->line[i2] != '0'
										&& lines->line[i2 + 1] != ' ' && lines->line[i2 + 1] != '\t'))
			return (-1);
	}
	return (0);
}

int 		get_y(int *i, t_room *temp, t_lines *lines)
{
	int 	i2;

	while (lines->line[*i] == ' ' || lines->line[*i] == '\t')
		(*i)++;
	i2 = *i;
	if (lines->line[*i] == '+' || lines->line[*i] == '-')
		(*i)++;
	while (lines->line[*i] != '\0')
		if (ft_isdigit(lines->line[(*i)++]) == 0)
			return (-1);
	if (i2 == *i)
		return (-1);
	if ((temp->y = ft_atoi(&(lines->line[i2]))) == 0)
	{
		if (lines->line[i2] == '+' || lines->line[i2] == '-')
			i2++;
		if (lines->line[i2] == '\0' || (lines->line[i2] != '0' &&
										lines->line[i2 + 1] != ' ' && lines->line[i2 + 1] != '\0'
										&& lines->line[i2 + 1] != '\t'))
			return (-1);
	}
	return (0);
}