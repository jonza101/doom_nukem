
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:38 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/28 22:44:30 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// Utility functions. Because C doesn't have templates,
// we use the slightly less safe preprocessor macros to
// implement these functions that work with multiple types.
#define min(a,b) (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two values.
#define max(a,b) (((a) > (b)) ? (a) : (b)) // max: Choose bigger of two values.
#define abs(a) ((a) < 0 ? -(a) : (a))
#define clamp(a, mi,ma) min(max(a,mi),ma)  // clamp: Clamp value into set range.
#define sign(v) (((v) > 0) - ((v) < 0))    // sign: Return the sign of a value (-1, 0 or 1)
#define vxs(x0,y0, x1,y1) ((x0)*(y1) - (x1)*(y0)) // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: -1, 0 or 1.
#define PointSide(px,py, x0,y0, x1,y1) sign(vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0)))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
    vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
    vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) })

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

float	ft_clamp(float a, float min, float max)
{
	return (ft_min(ft_max(a, min), max));
}

int		ft_sign(float val)
{
	if (val > 0)
		return (1);
	if (val < 0)
		return (-1);
	return (0);
}

int		ft_overlap(float a0, float a1, float b0, float b1)
{
	return(ft_min(a0, a1) <= ft_max(b0, b1) && ft_min(b0, b1) <= ft_max(a0, a1));
}

int		ft_intersect_box(float x0, float y0, float x1, float y1, float x2, float y2, float x3, float y3)
{
	return (ft_overlap(x0, x1, x2, x3) && ft_overlap(y0, y1, y2, y3));
}

float	ft_vec_cross_prod(float x0, float y0, float x1, float y1)
{
	return ((x0 * y1) - (x1 * y0));
}

int		ft_point_side(float px, float py, float x0, float y0, float x1, float y1)
{
	return (ft_sign(ft_vec_cross_prod(x1 - x0, y1 - y0, px - x0, py - y0)));
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

t_scaler	*ft_scaler_init(t_scaler *scaler, int a, int b, int c, int d, int f)
{
	scaler->result = d + (b - 1 - a) * (f - d) / (c - a);
	scaler->bop = ((f < d) ^ (c < a)) ? -1 : 1;
	scaler->fd = abs(f - d);
	scaler->ca = abs(c - a);
	scaler->cache = (int)((b - 1 - a) * abs(f - d)) % abs(c  - a);
	return (scaler);
}

int		ft_scaler_next(t_scaler *scaler)
{
	scaler->cache += scaler->fd;
	if (scaler->ca == 0)
		return (0);
	while (scaler->cache >= scaler->ca)
	{
		scaler->result += scaler->bop;
		scaler->cache -= scaler->ca;
	}
	return (scaler->result);
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

void	ft_draw_tvline(t_mlx *mlx, int x, int y1, int y2, t_scaler *ty, unsigned txtx, t_img *texture)
{
	if (y1 < 0 || y1 > H - 1 || y2 < 0 || y2 > H - 1)
		return ;
	int y = y1 - 1;
	while (++y <= y2)
	{
		unsigned txty = ft_scaler_next(ty);
		// printf("txtx %u	txty %u\n", txtx, txty);
		ft_image(mlx, x, y, texture->data[txty % texture->h * texture->w + txtx % texture->w]);
	}
}
