/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 14:47:39 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 14:58:07 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*temp;
	int				i;

	i = 0;
	temp = (unsigned char*)str;
	while (n-- > 0)
	{
		temp[i] = 0;
		i++;
	}
}
