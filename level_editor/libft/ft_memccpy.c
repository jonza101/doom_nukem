/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:07:56 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/22 19:53:54 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*s;
	unsigned char	*d;
	int				i;

	if (dst == NULL && src == NULL)
		return (dst);
	s = (unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	while ((size_t)i < n)
	{
		d[i] = s[i];
		if (s[i] == (unsigned char)c)
			return ((char *)d + i + 1);
		i++;
	}
	return (NULL);
}
