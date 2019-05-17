/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:37:29 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 17:52:21 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str1, const char *str2)
{
	int i;
	int j;

	i = 0;
	if (!str2[0])
		return ((char*)str1);
	while (str1[i])
	{
		j = 0;
		if (str1[i] == str2[j])
		{
			while (str1[i + j] && (str1[i + j] == str2[j]))
			{
				if (!str2[j + 1])
					return ((char*)&str1[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
