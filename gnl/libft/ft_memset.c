/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:08:33 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/12/04 13:08:20 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int c, size_t len)
{
	int				i;
	unsigned char	*temp;

	i = 0;
	temp = (unsigned char*)dest;
	while (len > 0)
	{
		temp[i] = c;
		i++;
		len--;
	}
	return (temp);
}
