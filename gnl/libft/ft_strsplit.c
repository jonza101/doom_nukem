/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 15:59:50 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/12/02 19:09:32 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	int		ft_word_count(char const *s, char c, int *i, int *id)
{
	int j;
	int words;

	j = 0;
	words = 0;
	*i = 0;
	*id = 0;
	while (s[*i] && s[*i] == c)
		*i += 1;
	while (s[j])
	{
		if (s[j] != c && (s[j + 1] == c || !s[j + 1]))
			words++;
		j++;
	}
	return (words);
}

static	int		ft_sl(char *str, char c)
{
	int len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static	void	ft_word_input(char const *s, int start, int end, char *ar)
{
	int i;

	i = 0;
	while (start < end)
	{
		ar[i] = s[start];
		start++;
		i++;
	}
	ar[i] = '\0';
}

static	char	**ft_free(char **ar, int id)
{
	while (--id > 0)
		free(ar[id]);
	ar[id] = NULL;
	return (ar);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		l;
	int		id;
	char	**ar;

	if (!s || !c)
		return (NULL);
	if (!(ar = (char**)malloc(sizeof(char*) *
		ft_word_count((char*)s, c, &i, &id) + 1)))
		return (NULL);
	l = i;
	while (s[i++])
	{
		if (s[i] == c || !s[i])
		{
			if (!(ar[id] = (char*)malloc(ft_sl((char*)&s[l], c) + 1)))
				return (ft_free(ar, id));
			ft_word_input((char*)s, l, i, ar[id++]);
			while (s[i] == c)
				i++;
			l = i;
		}
	}
	ar[id] = NULL;
	return (ar);
}
