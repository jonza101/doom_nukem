/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:49:02 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 19:19:14 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (!str2[0])
		return ((char*)str1);
	while (str1[i])
	{
		j = 0;
		if (str1[i] == str2[j])
		{
			while (str1[i + j] == str2[j])
			{
				if (i + j >= len)
					return (NULL);
				if (!str2[j + 1])
					return ((char*)&str1[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
