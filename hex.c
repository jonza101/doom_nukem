/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 18:12:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/26 00:04:51 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_hex_letter(char hex_l)
{
	if (hex_l == 'A')
		return (10);
	if (hex_l == 'B')
		return (11);
	if (hex_l == 'C')
		return (12);
	if (hex_l == 'D')
		return (13);
	if (hex_l == 'E')
		return (14);
	if (hex_l == 'F')
		return (15);
	return (hex_l - '0');
}

int		ft_hex_to_dec(char *rgb)
{
	int i;
	int color;

	i = 0;
	color = 0;
	while (i < 6)
	{
		color += ft_hex_letter(rgb[i]) * pow(16, (5 - i));
		i++;
	}
	free(rgb);
	return (color);
}

char	*ft_dec_to_hex(int number)
{
	char *hex;
	int rem;
	int i;

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

int		ft_get_color(char *rgb, double lum)
{
	int r;
	int g;
	int b;
	char *temp;
	char *rc, *gc, *bc;
	int res;

	rc = ft_strnew(2);
	gc = ft_strnew(2);
	bc = ft_strnew(2);
	r = (ft_hex_letter(rgb[0]) * 16 + ft_hex_letter(rgb[1])) * lum;
	g = (ft_hex_letter(rgb[2]) * 16 + ft_hex_letter(rgb[3])) * lum;
	b = (ft_hex_letter(rgb[4]) * 16 + ft_hex_letter(rgb[5])) * lum;
	
	temp = ft_dec_to_hex(r);
	rc[0] = temp[4];
	rc[1] = temp[5];

	temp = ft_dec_to_hex(g);
	gc[0] = temp[4];
	gc[1] = temp[5];

	temp = ft_dec_to_hex(b);
	bc[0] = temp[4];
	bc[1] = temp[5];

	rc = ft_strjoin(rc, gc);
	rc = ft_strjoin(rc, bc);

	res = ft_hex_to_dec(rc);

	free(temp);
	free(gc);
	free(bc);
	
	return (res);
}
