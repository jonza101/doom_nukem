/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:32:01 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/12/01 16:08:20 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_strncmp(const char *str1, const char *str2, size_t n)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && str1[i] == str2[i] && n > 0)
	{
		i++;
		n--;
	}
	if (str1[i] != str2[i] && n > 0)
		return ((unsigned char)str1[i] - (unsigned char)str2[i]);
	return (0);
}
