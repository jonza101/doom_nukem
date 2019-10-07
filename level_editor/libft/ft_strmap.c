/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:38:02 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/12 21:26:03 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	char	*ret;
	size_t	len;

	if (!f || !s)
		return (NULL);
	len = ft_strlen(s);
	new = ft_strnew(len);
	if (new == NULL)
		return (NULL);
	ret = new;
	while (len--)
		*new++ = f((char)*s++);
	return (ret);
}
