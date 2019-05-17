/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padleft.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 19:53:47 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/12/02 12:58:28 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_padleft(const char *str, size_t total_width, char c)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	if (!(res = (char*)malloc(sizeof(char) * (total_width + 1))))
		return (NULL);
	while (i < total_width - len)
	{
		res[i] = (unsigned char)c;
		i++;
	}
	while (str[j])
	{
		res[i + j] = str[j];
		j++;
	}
	res[i + j] = '\0';
	return (res);
}
