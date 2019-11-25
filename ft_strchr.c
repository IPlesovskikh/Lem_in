/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdonnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 18:59:32 by pdonnie           #+#    #+#             */
/*   Updated: 2019/04/08 18:59:34 by pdonnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	chr;

	i = 0;
	chr = (int)c;
	while (s[i] != '\0' && s[i] != chr)
		i++;
	if (s[i] == chr)
		return (char *)(s + i);
	else
		return (NULL);
}
