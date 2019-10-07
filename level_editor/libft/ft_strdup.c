/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:22:39 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/22 19:10:23 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*sdup;

	sdup = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (sdup == NULL)
		return (NULL);
	else
		return (ft_strcpy(sdup, s1));
}
