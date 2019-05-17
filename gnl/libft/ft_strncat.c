/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:31:52 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 15:46:22 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	int i;
	int len;

	i = 0;
	len = 0;
	while (dest[len])
		len++;
	while (src[i] && n > 0)
	{
		dest[len + i] = src[i];
		i++;
		n--;
	}
	dest[len + i] = '\0';
	return (dest);
}
