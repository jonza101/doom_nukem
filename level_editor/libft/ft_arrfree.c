/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:17:01 by jsteuber          #+#    #+#             */
/*   Updated: 2019/02/26 17:23:11 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		**ft_arrfree(char ***array, size_t bp)
{
	size_t	k;

	k = 0;
	while (k < bp)
	{
		free((*array)[k]);
		(*array)[k++] = NULL;
	}
	free(*array);
	*array = NULL;
	return (NULL);
}
