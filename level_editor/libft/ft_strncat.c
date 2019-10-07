/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:26:15 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/22 18:27:32 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dst, const char *src, size_t n)
{
	char	*cdst;

	cdst = dst;
	while (*cdst != '\0')
		cdst++;
	while (*src != '\0' && n-- != 0)
		*cdst++ = *src++;
	*cdst = '\0';
	return (dst);
}
