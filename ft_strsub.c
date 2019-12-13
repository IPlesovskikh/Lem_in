/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdonnie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 16:09:18 by pdonnie           #+#    #+#             */
/*   Updated: 2019/09/29 18:31:43 by pdonnie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validator.h"


char			*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	index;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	if ((len + 1) < len)
		return (NULL);
	if ((str = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		return (NULL);
	if (str == NULL)
		return (NULL);
	index = 0;
	while (index < len && s[start] != '\0')
	{
		str[index] = s[start];
		start++;
		index++;
	}
	str[index] = '\0';
	return (str);
}