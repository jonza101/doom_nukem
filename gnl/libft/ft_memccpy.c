/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:19:12 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/29 15:27:03 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src,
	int c, size_t n)
{
	int				i;
	unsigned char	*dst;
	unsigned char	*temp_src;

	i = 0;
	dst = (unsigned char*)dest;
	temp_src = (unsigned char*)src;
	while (n-- > 0)
	{
		dst[i] = temp_src[i];
		if (dst[i] == (unsigned char)c)
			return ((void*)&dst[i + 1]);
		i++;
	}
	return (NULL);
}
