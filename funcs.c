/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:38 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/13 17:30:04 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

float		ft_min(float a, float b)
{
	if (b < a)
		return (b);
	return (a);
}

float		ft_max(float a, float b)
{
	if (b > a)
		return (b);
	return (a);
}

float		ft_clamp(float a, float min, float max)
{
	return (ft_min(ft_max(a, min), max));
}

float		ft_overlap(float a0, float a1, float b0, float b1)
{
	return(ft_min(a0, a1) <= ft_max(b0, b1) && ft_min(b0, b1) <= ft_max(a0, a1));
}

float		ft_intersect_box(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
	return (ft_overlap(x0, x1, x2, x3) && ft_overlap(y0, y1, y2, y3));
}

float	ft_vec_cross_prod(float x0, float y0, float x1, float y1)
{
	return (x0 * y1 - x1 * y0);
}

float	ft_point_side(float px, float py, float x0, float y0, float x1, float y1)
{
	return (ft_vec_cross_prod(x1 - x0, y1 - y0, px - x0, py - y0));
}

void	ft_intersect(t_vec2 *p, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
	p->x = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), x1 - x2, ft_vec_cross_prod(x3, y3, x4, y4), x3 - x4) /
		ft_vec_cross_prod(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	p->y = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), y1 - y2, ft_vec_cross_prod(x3, y3, x4, y4), y3 - y4) /
		ft_vec_cross_prod(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
}

float	ft_yaw(float y, float z, float p_yaw)
{
	return (y + z * p_yaw);
}

void	ft_draw_vline(t_mlx *mlx, int x, int y1,int y2, int top_color,int middle_color,int bottom_color)
{
	if (y1 < 0 || y1 > H - 1 || y2 < 0 || y2 > H - 1)
		return ;
	// y1 = ft_clamp(y1, 0, H - 1);
	// y2 = ft_clamp(y2, 0, H - 1);
	if (y1 == y2)
	{
		if (y1 != H - 1 && y1 != 0)
			ft_image(mlx, x, y1, bottom_color);
		else
			ft_image(mlx, x, y1, middle_color);
		return ;
	}
	else if (y2 > y1)
	{
		if (y1 != H - 1 && y1 != 0)
			ft_image(mlx, x, y1, top_color);
		else
			ft_image(mlx, x, y1, middle_color);
		int y = y1 + 1;
		while (y < y2)
		{
			ft_image(mlx, x, y, middle_color);
			y++;
		}
		if (y2 != H - 1 && y2 != 0)
			ft_image(mlx, x, y2, bottom_color);
		else
			ft_image(mlx, x, y2, middle_color);
	}
}

void	ft_()
{
	
}