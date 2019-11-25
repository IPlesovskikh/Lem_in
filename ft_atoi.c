/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdonnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:20:46 by pdonnie           #+#    #+#             */
/*   Updated: 2019/04/07 21:54:18 by pdonnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

static long int	conversion_negative(const char *str, int i)
{
	long int		n;
	long int		y;
	int				len;

	n = 0;
	len = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	y = 1;
	i--;
	if (str[i] == '-')
		return (0);
	while (i >= len)
	{
		n = n + (str[i] - '0') * y;
		if (n > 223372036854775806 ||
			(n == 223372036854775806 && str[i] == 9))
			return (0);
		i--;
		y = 10 * y;
	}
	n = -n;
	return (n);
}

static long int	conversion_positive(const char *str, int i)
{
	long int	n;
	long int	y;
	int			len;

	n = 0;
	if (str[i] == '+')
		i++;
	len = i;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	y = 1;
	i--;
	if (str[i] == '+')
		return (0);
	while (i >= len && str[i] != '+')
	{
		n = n + (str[i] - '0') * y;
		if (n > 223372036854775807 ||
			(n == 223372036854775807 && str[i] == 9))
			return (-1);
		i--;
		y = 10 * y;
	}
	return (n);
}

int				ft_atoi(const char *str)
{
	int			i;
	long int	n;

	i = 0;
	n = 0;
	while (str[i] != '\0' && (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
	|| str[i] == '\f' || str[i] == '\r' || str[i] == ' '))
		i++;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '-')
	{
		i++;
		n = conversion_negative(str, i);
	}
	else
	{
		n = conversion_positive(str, i);
	}
	return (int)(n);
}
