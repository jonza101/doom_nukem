/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 17:55:57 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/12 21:23:43 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nbrlen(int n)
{
	int		i;

	i = 1;
	while (n > 9)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char		*ft_itoa(int n)
{
	int		i;
	int		fminus;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if ((fminus = n) < 0)
	{
		n = -n;
		if ((str = ft_strnew(ft_nbrlen(n) + 1)) == NULL)
			return (NULL);
	}
	else
		str = ft_strnew(ft_nbrlen(n));
	if (str == NULL)
		return (NULL);
	i = 0;
	str[i++] = n % 10 + '0';
	while ((n /= 10) > 0)
		str[i++] = n % 10 + '0';
	if (fminus < 0)
		str[i++] = '-';
	ft_strrev(str);
	return (str);
}
