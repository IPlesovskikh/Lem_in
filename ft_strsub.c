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
	str = (char *)malloc(sizeof(char) * (len + 1));
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

static int		ft_count(char const *s, char c)
{
	int			nb_words;
	int			str_test;

	nb_words = 0;
	str_test = 0;
	while (*s != '\0')
	{
		if (str_test == 1 && *s == c)
			str_test = 0;
		if (str_test == 0 && *s != c)
		{
			str_test = 1;
			nb_words++;
		}
		s++;
	}
	return (nb_words);
}

static int		ft_word_length(char const *s, char c)
{
	size_t		i;

	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**my_tab;
	int			i;
	int			nb_words;

	i = 0;
	if (!s)
		return (NULL);
	nb_words = ft_count(s, c);
	my_tab = (char **)malloc(sizeof(char *) * ft_count(s, c) + 1);
	if (my_tab == NULL)
		return (NULL);
	while (nb_words--)
	{
		while (*s == c && *s != '\0')
			s++;
		if ((my_tab[i] = ft_strsub(s, 0, ft_word_length(s, c))) == NULL)
			return (NULL);
		s += ft_word_length(s, c);
		i++;
	}
	my_tab[i] = NULL;
	return (my_tab);
}
