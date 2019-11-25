/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdonnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:45:52 by pdonnie           #+#    #+#             */
/*   Updated: 2019/04/10 16:48:00 by pdonnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

static int		ft_check_size(char const *s1, char const *s2)
{
	size_t	size_s1;
	size_t	size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	if ((size_s1 + size_s2) < size_s1)
		return (1);
	if ((size_s1 + size_s2 + 1) < (size_s1 + size_s2))
		return (1);
	return (0);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char		*str;
	size_t		index;
	size_t		index2;

	if (!s1 || !s2 || (ft_check_size(s1, s2)) == 1)
		return (NULL);
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == 0)
		return (NULL);
	index = 0;
	while (s1[index] != '\0')
	{
		str[index] = s1[index];
		index++;
	}
	index2 = 0;
	while (s2[index2] != '\0')
	{
		str[index] = s2[index2];
		index++;
		index2++;
	}
	str[index] = '\0';
	return (str);
}
