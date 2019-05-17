/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padright.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 20:02:32 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/12/01 20:06:22 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_padright(const char *str, size_t total_width, char c)
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
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	while (i < total_width)
	{
		res[i] = (unsigned char)c;
		i++;
	}
	res[i] = '\0';
	return (res);
}
