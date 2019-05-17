/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 18:13:37 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 14:50:07 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	void	ft_start(int *n, unsigned int *nb, size_t *i, int *is_negative)
{
	*i = 1;
	*is_negative = 0;
	if (*n < 0)
	{
		*i += 1;
		*is_negative = 1;
		*n *= -1;
	}
	*nb = *n;
	while (*nb > 9)
	{
		*i += 1;
		*nb /= 10;
	}
}

char			*ft_itoa(int n)
{
	unsigned int	nb;
	size_t			i;
	int				is_negative;
	char			*str;

	ft_start(&n, &nb, &i, &is_negative);
	if (!(str = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	str[i] = '\0';
	i--;
	nb = n;
	if (is_negative == 1)
		str[0] = '-';
	while (nb > 9)
	{
		str[i] = (nb % 10) + '0';
		i--;
		nb /= 10;
	}
	str[i] = nb + '0';
	return (str);
}
