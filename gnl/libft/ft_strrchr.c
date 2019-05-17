/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:01:05 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 19:09:08 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*res;

	i = 0;
	res = 0;
	while (str[i])
	{
		if (str[i] == (unsigned char)c)
			res = (char*)&str[i];
		i++;
	}
	if (res)
		return (res);
	if (c == 0)
		return ((char*)&str[i]);
	return (NULL);
}
