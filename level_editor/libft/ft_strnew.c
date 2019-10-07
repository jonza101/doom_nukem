/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:33:10 by jsteuber          #+#    #+#             */
/*   Updated: 2019/02/21 19:54:47 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*dup;
	size_t	ofcheck;

	if ((ofcheck = (size + 1) * sizeof(char)) == 0)
		return (NULL);
	dup = (char *)malloc(ofcheck);
	if (dup == NULL || dup < 0)
		return (NULL);
	ft_bzero(dup, size + 1);
	return (dup);
}
