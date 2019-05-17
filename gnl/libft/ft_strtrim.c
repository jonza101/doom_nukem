/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:35:13 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/11/27 20:15:19 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	void	ft_start(int *i, int *j, int *len, char const *s)
{
	*i = 0;
	*j = 0;
	while (s[*i] && (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\n'))
		*i += 1;
	*len = ft_strlen((char*)s);
	while (s[*len - *j - 1] && (s[*len - *j - 1] == ' ' ||
	s[*len - *j - 1] == '\t' || s[*len - *j - 1] == '\n'))
		*j += 1;
}

char			*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		index;
	int		len;
	char	*str;

	if (!s)
		return (NULL);
	index = 0;
	ft_start(&i, &j, &len, (char*)s);
	if (i == (int)len && j == (int)len)
	{
		str = (char*)malloc(sizeof(char) * 1);
		str[0] = 0;
		return (str);
	}
	if (!(str = (char*)malloc(sizeof(char) * ((int)len - j - i + 1))))
		return (NULL);
	while (s[i] && i < (int)len - j)
	{
		str[index++] = s[i];
		i++;
	}
	str[index] = '\0';
	return (str);
}
