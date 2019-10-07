/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 21:41:52 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/12 21:24:13 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*dup;

	if (size == 0)
		return (NULL);
	dup = malloc(size);
	if (dup == NULL)
		return (NULL);
	ft_memset(dup, 0, size);
	return (dup);
}
