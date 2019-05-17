/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:09:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 14:50:48 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
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
		i++;
	}
	return (dst);
}
