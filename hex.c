/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:12:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/22 19:30:35 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

char	*ft_dec_to_hex(int number)
{
	char *hex;
	int rem;
	int i;

	if (number <= 0)
		return NULL;
	hex = (char*)malloc(sizeof(char) * 7);
	int j = 0;
	while (j < 6)
	{
		hex[j] = '0';
		j++;
	}
	hex[6] = '\0';
	i = 5;
	while (number > 0)
	{
		rem = number % 16;
		if (rem < 10)
			hex[i] = rem + '0';
		else
		{
			if (rem == 10)
				hex[i] = 'A' ;
			if (rem == 11)
				hex[i] = 'B' ;
			if (rem == 12)
				hex[i] = 'C' ;
			if (rem == 13)
				hex[i] = 'D' ;
			if (rem == 14)
				hex[i] = 'E' ;
			if (rem == 15)
				hex[i] = 'F' ;
		}
		number /= 16;
		i--;
	}
	return (hex);
}
