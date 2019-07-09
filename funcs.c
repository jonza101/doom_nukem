/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:38 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/09 19:36:05 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double		ft_min(double a, double b)
{
	if (b < a)
		return (b);
	return (a);
}

double		ft_max(double a, double b)
{
	if (b > a)
		return (b);
	return (a);
}

double	ft_clamp(double a, double min, double max)
{
	return (ft_min(ft_max(a, min), max));
}

int		ft_sign(double val)
{
	if (val > 0)
		return (1);
	if (val < 0)
		return (-1);
	return (0);
}

int		ft_line_intersect(t_vec2 *p0, t_vec2 *p1, t_vec2 *v0, t_vec2 *v1)
{
	double s1_x, s1_y;
	double s2_x, s2_y;
	s1_x = p1->x - p0->x;
	s1_y = p1->y - p0->y;
	s2_x = v1->x - v0->x;
	s2_y = v1->y - v0->y;

	float s, t;
	s = (-s1_y * (p0->x - v0->x) + s1_x * (p0->y - v0->y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0->y - v0->y) - s2_y * (p0->x - v0->x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		return (1);
	return (0);
}

int		ft_is_inside(t_sector *sector, double px, double py, double dx, double dy)
{
	int count = 0;
	int s = -1;
	t_vec2 *ray = (t_vec2*)malloc(sizeof(t_vec2));
	ray->x = dx;
	ray->y = dy;

	t_vec2 *p = (t_vec2*)malloc(sizeof(t_vec2));
	p->x = px;
	p->y = py;
	t_vec2 *v0 = (t_vec2*)malloc(sizeof(t_vec2));
	t_vec2 *v1 = (t_vec2*)malloc(sizeof(t_vec2));
	while (++s < sector->verts_count)
	{
		v0->x = sector->verts[s]->x;
		v0->y = sector->verts[s]->y;
		v1->x = sector->verts[s + 1]->x;
		v1->y = sector->verts[s + 1]->y;
		if (ft_line_intersect(p, ray, v0, v1))
			count++;
	}
	free(ray);
	free(p);
	free(v0);
	free(v1);
	return (count);
}

int		ft_overlap(int a0, int a1, int b0, int b1)
{
	return(ft_min(a0, a1) <= ft_max(b0, b1) && ft_min(b0, b1) <= ft_max(a0, a1));
}

int		ft_intersect_box(int x0, int y0, int x1, int y1, int x2, int y2, int x3, int y3)
{
	return (ft_overlap(x0, x1, x2, x3) && ft_overlap(y0, y1, y2, y3));
}

double	ft_vec_cross_prod(double x0, double y0, double x1, double y1)
{
	return ((x0 * y1) - (x1 * y0));
}

int		ft_point_side(double px, double py, double x0, double y0, double x1, double y1)
{
	return (ft_sign(ft_vec_cross_prod(x1 - x0, y1 - y0, px - x0, py - y0)));
}

void	ft_intersect(t_vec2 *p, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
	p->x = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), x1 - x2, ft_vec_cross_prod(x3, y3, x4, y4), x3 - x4) /
		ft_vec_cross_prod(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
	p->y = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), y1 - y2, ft_vec_cross_prod(x3, y3, x4, y4), y3 - y4) /
		ft_vec_cross_prod(x1 - x2, y1 - y2, x3 - x4, y3 - y4);
}

double	ft_yaw(double y, double z, double p_yaw)
{
	return (y + z * p_yaw);
}

void	ft_scaler_init(t_scaler *scaler, int a, int b, int c, int d, int f)
{
	scaler->result = d + (b - 1 - a) * (f - d) / (c - a);
	scaler->bop = ((f < d) ^ (c < a)) ? -1 : 1;
	scaler->fd = abs(f - d);
	scaler->ca = abs(c - a);
	scaler->cache = (int)((b - 1 - a) * abs(f - d)) % abs(c  - a);
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
	if ((y1 < 0 || y1 > H - 1 || y2 < 0 || y2 > H - 1)
			&& (x < 0 || x > W - 1))
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
	if ((y1 < 0 || y1 > H - 1 || y2 < 0 || y2 > H - 1)
			&& (x < 0 || x > W - 1))
		return ;
	int y = y1 - 1;
	while (++y <= y2)
	{
		unsigned txty = ft_scaler_next(ty);
		ft_image(mlx, x, y, texture->data[txty % texture->h * texture->w + txtx % texture->w]);
	}
}

void	ft_upper_solid(t_mlx *mlx, int x, int cya, int cnya, int top_c, int middle_c, int bottom_c, int *ar_top)
{
	ft_draw_vline(mlx, x, cya, cnya - 1, top_c, middle_c, bottom_c);
	*ar_top = ft_clamp(ft_max(cya, cnya), *ar_top, H - 1);
}

void	ft_lower_solid(t_mlx *mlx, int x, int cnyb, int cyb, int bottom_c, int middle_c, int top_c, int *ar_bottom)
{
	ft_draw_vline(mlx, x, cnyb + 1, cyb, top_c, middle_c, bottom_c);
	*ar_bottom = ft_clamp(ft_min(cyb, cnyb), 0, *ar_bottom);
}

void	ft_upper_txt(t_mlx *mlx, int x, int cya, int cnya, int txtx, int txt_i, int ya, int yb, int *ar_top)
{
	ft_scaler_init(mlx->scaler, ya, cya, yb, mlx->u0, mlx->u1);
	ft_draw_tvline(mlx, x, cya, cnya - 1, mlx->scaler, txtx, mlx->txt_temp[txt_i]);
	*ar_top = ft_clamp(ft_max(cya, cnya), *ar_top, H - 1);
}

void	ft_lower_txt(t_mlx *mlx, int x, int cnyb, int cyb, int txtx, int txt_i, int ya, int yb, int *ar_bottom)
{
	ft_scaler_init(mlx->scaler, ya, cnyb + 1, yb, mlx->u0, mlx->u1);
	ft_draw_tvline(mlx, x, cnyb + 1, cyb, mlx->scaler, txtx, mlx->txt_temp[txt_i]);
	*ar_bottom = ft_clamp(ft_min(cyb, cnyb), 0, *ar_bottom);
}

void	ft_relative_to_absolute(t_mlx *mlx)
{
	double rt_x = mlx->map_z * mlx->player->cos_angle + mlx->map_x * mlx->player->sin_angle;
	double rt_z = mlx->map_z * mlx->player->sin_angle - mlx->map_x * mlx->player->cos_angle;
	mlx->map_x = rt_x + mlx->player->pos->x;
	mlx->map_z = rt_z + mlx->player->pos->y;
}

void	ft_screenpoint_to_mappoint(t_mlx *mlx, double map_y, double screen_x, double screen_y)
{
	mlx->map_z = map_y * H * FOV_V / ((H / 2 - screen_y) - mlx->player->yaw * H * FOV_V);
	mlx->map_x = mlx->map_z * (W / 2 - (screen_x)) / (W * FOV_H);
	ft_relative_to_absolute(mlx);
}
