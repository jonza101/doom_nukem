/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/24 19:59:24 by jsteuber          #+#    #+#             */
/*   Updated: 2019/02/22 16:51:56 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

char			**ft_strsplit(char const *s, char c)
{
	unsigned int		len;
	unsigned int		words_num;
	char				**array;
	size_t				ofc;

	if (s == NULL)
		return (NULL);
	words_num = ft_ctwords((char *)s, c);
	if ((ofc = sizeof(char *) * (words_num + 1)) == 0)
		return (NULL);
	if ((array = (char **)malloc(ofc)) == NULL)
		return (NULL);
	ofc = 0;
	while (words_num--)
	{
		while (*s == c)
			s++;
		len = ft_wordlen((char *)s, c);
		if ((array[ofc] = ft_strsub(s, 0, len)) == NULL)
			return (ft_arrfree(&array, ofc));
		s += len;
		ofc++;
	}
	array[ofc] = NULL;
	return (array);
}
