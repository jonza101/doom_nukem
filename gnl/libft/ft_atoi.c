/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:04:22 by zjeyne-l          #+#    #+#             */
/*   Updated: 2018/12/03 12:58:24 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	ft_start(int *i, int *is_negative, char *str, int *res)
{
	*res = 0;
	*i = 0;
	*is_negative = 0;
	while (str[*i] == '\n' || str[*i] == '\t' || str[*i] == '\v' ||
		str[*i] == '\f' || str[*i] == '\r' || str[*i] == ' ')
		*i += 1;
	if (str[*i] == '-')
		*is_negative = 1;
	if (str[*i] == '-' || str[*i] == '+')
		*i += 1;
}

int				ft_atoi(const char *str)
{
	int i;
	int is_negative;
	int res;
	int exc;
	int cut;

	exc = 0;
	cut = 0;
	ft_start(&i, &is_negative, (char*)str, &res);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (str[i] >= '1' && str[i] <= '9')
			cut = 1;
		if (exc > 20 && is_negative == 1)
			return (0);
		if (exc > 20 && is_negative == 0)
			return (-1);
		res = res * 10 + (str[i] - '0');
		i++;
		if (cut == 1)
			exc++;
	}
	if (is_negative == 1)
		return (-res);
	return (res);
}
