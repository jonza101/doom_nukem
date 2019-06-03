/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 22:51:57 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/03 23:20:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double	ft_min(double a, double b)
{
	if (b < a)
		return (b);
	return (a);
}

double	ft_max(double a, double b)
{
	if (b > a)
		return (b);
	return (a);
}

double	ft_clamp(double a, double min, double max)
{
	return (ft_min(ft_max(a, min), max));
}

int		ft_overlap(double a0, double a1, double b0, double b1)
{
	if ((ft_min(a0, a1) <= ft_max(b0, b1)) && (ft_min(b0, b1) <= ft_max(a0, a1)))
		return (1);
	return (0);
}

int		ft_intersect_box(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
	if (ft_overlap(x0, x1, x2, x3) && ft_overlap(y0, y1, y2, y3))
		return (1);
	return (0);
}

double	ft_vec_cross_prod(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

double	ft_point_side(double px, double py, double x0, double y0, double x1, double y1)
{
	return (ft_vec_cross_prod(x1 - x0, y1 - y0, px - x0, py - y0));
}

t_vec2	*ft_intersect(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	t_vec2 *point;
	
	point = (t_vec2*)malloc(sizeof(t_vec2));
	point->x = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), x1 - x2, ft_vec_cross_prod(x3, y3, x4, y4), x3 - x4) /
		ft_vec_cross_prod(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	point->y = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), y1 - y2, ft_vec_cross_prod(x3, y3, x4, y4), y3 - y4) /
		ft_vec_cross_prod(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	return (point);
}

void	ft_draw_line_start(t_mlx *mlx, int xo, int yo, int x, int y, int *delta_x, int *delta_y)
{
	if (x < xo)
		*delta_x = -1;
	else
		*delta_x = 1;
	if (y < yo)
		*delta_y = -1;
	else
		*delta_y = 1;
}

void	ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color)
{
	int angle_x;
	int angle_y;
	int delta_x;
	int delta_y;
	int error;

	angle_x = abs(x - xo);
	angle_y = abs(y - yo);
	error = angle_x - angle_y;
	ft_draw_line_start(mlx, xo, yo, x, y, &delta_x, &delta_y);
	ft_image(mlx, x, y, color);
	while (xo != x || yo != y)
	{
		ft_image(mlx, xo, yo, color);
		if (error * 2 > -angle_y)
		{
			error -= angle_y;
			xo += delta_x;
		}
		else if (error * 2 < angle_x)
		{
			error += angle_x;
			yo += delta_y;
		}
		else
			break ;
	}
}
