/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 15:57:50 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/29 16:01:03 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dst;
	unsigned char	*temp_src;

	i = 0;
	dst = (unsigned char*)dest;
	temp_src = (unsigned char*)src;
	if (temp_src < dst)
	{
		while (++i <= len)
			dst[len - i] = temp_src[len - i];
	}
	else
	{
		while (len-- > 0)
		{
			dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}
