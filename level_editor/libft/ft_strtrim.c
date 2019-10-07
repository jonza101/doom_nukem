/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 18:25:58 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/12 21:26:46 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ct_spaces(const char *s, char flag)
{
	size_t	i;

	i = 0;
	while (*s)
	{
		if (*s == ' ' || *s == '\n' || *s == '\t')
		{
			if (flag == 0)
				s++;
			else
				s--;
		}
		else
			return (i);
		i++;
	}
	return (i);
}

char			*ft_strtrim(char const *s)
{
	char	*ptr;
	size_t	spaces;

	if (s == NULL)
		return (NULL);
	spaces = ct_spaces(s + (ft_strlen(s) - 1), 1) + \
(ct_spaces(s, 0));
	if (spaces >= ft_strlen(s))
		return (ft_strnew(0));
	ptr = ft_strsub(s, ct_spaces(s, 0), ft_strlen(s) - spaces);
	if (ptr == NULL)
		return (NULL);
	return (ptr);
}
