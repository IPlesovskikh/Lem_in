/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdonnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 20:17:12 by pdonnie           #+#    #+#             */
/*   Updated: 2019/04/10 20:35:18 by pdonnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	size_t			index;
	unsigned char	*s1;
	unsigned char	*s2;

	if (dst == NULL && src == NULL)
		return (NULL);
	s1 = (unsigned char *)dst;
	s2 = (unsigned char *)src;
	index = 0;
	while (n > 0)
	{
		s1[index] = s2[index];
		index++;
		n--;
	}
	return (dst);
}
