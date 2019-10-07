/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:16:25 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"
#include "math.h"

float		calc_dist(int x0, int y0, int x1, int y1)
{
	int	dx;
	int	dy;

	dx = abs(x0) > abs(x1) ? x0 - x1 : x1 - x0;
	dy = abs(y0) > abs(y1) ? y0 - y1 : y1 - y0;
	return (sqrt(pow(dx, 2) + pow(dy, 2)));
}

static void	ft_ftoa_part(char **str, float num, char *tmpm, char *tmpa)
{
	ft_strcat(*str, tmpm);
	ft_strcat(*str, ".");
	if (floor(num) != 0)
		ft_strcat(*str, tmpa);
	else
		ft_strcat(*str, "00");
}

char		*ft_ftoa(float num)
{
	char	*str;
	char	*tmpm;
	char	*tmpa;
	int		i;
	float	mem;

	mem = num;
	i = num >= 0 ? floor(num) : ceil(num);
	num = num - i;
	num = fabs(num * 100);
	num = round(num);
	if (num == 100)
	{
		num = 0;
		i += mem > 0 ? 1 : -1;
	}
	tmpm = ft_itoa(abs(i));
	tmpa = ft_itoa(num);
	strnew_nullcheck(&str, ft_strlen(tmpm) + ft_strlen(tmpa));
	ft_strcat(str, mem >= 0 ? "" : "-");
	ft_ftoa_part(&str, num, tmpm, tmpa);
	free(tmpm);
	free(tmpa);
	return (str);
}

double		ft_atof(const char *str)
{
	double	res;
	double	res2;
	char	*c;
	int		len;
	int		sign;

	sign = 1;
	c = (char *)str;
	while (!ft_isdigit(*c) && *c)
	{
		if (*c == '-')
			sign = -1;
		c++;
	}
	res = (double)ft_atoi(c);
	while (*c && *c != '.')
		c++;
	if (*c == '.')
		c++;
	*(c + 1) = ' ';
	res2 = (double)ft_atoi(c);
	len = 1;
	while (len--)
		res2 /= 10;
	return ((res + res2) * sign);
}

int			ft_arrlen(char **arr)
{
	int		i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}
