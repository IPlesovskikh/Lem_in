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

static int	ft_isspace(int c)
{
	if (c == 0x20 || c == 0x90 || c == 0x0a || c == (0x0b) ||
		c == (0x0c) || c == (0x0d) || c == '\t')
		return (c);
	else
		return (0);
}

static int	ft_check(char dig, char sign, long int res)
{
	if ((sign == '+' && res > 214748364) ||
		(res == 214748364 && dig > '7'))
		return (0);
	if ((sign == '-' && res < -214748364) ||
		(res == -214748364 && dig > '8'))
		return (0);
	else
		return (10);
}

static int	ft_result(const char *dig)
{
	size_t		i;
	long int	res;
	char		sign;

	i = 0;
	res = 0;
	sign = '+';
	if (dig[i] == '+' || dig[i] == '-')
	{
		sign = dig[i];
		i++;
	}
	while (ft_isdigit(dig[i]))
	{
		if (ft_check(dig[i], sign, res) == -1
			|| ft_check(dig[i], sign, res) == 0)
			return (ft_check(dig[i], sign, res));
		if (sign == '-')
			res = res * 10 - (dig[i] - '0');
		else
			res = res * 10 + (dig[i] - '0');
		i++;
	}
	return (res);
}

int			ft_atoi(const char *str)
{
	size_t		i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	return (ft_result(str + i));
}
