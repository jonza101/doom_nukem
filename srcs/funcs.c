/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:38 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/19 19:52:52 by zjeyne-l         ###   ########.fr       */
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

int		ft_overlap(double a0, double a1, double b0, double b1)
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
	p->x = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), (x1) - (x2), ft_vec_cross_prod(x3, y3, x4, y4), (x3) - (x4)) /
		ft_vec_cross_prod((x1) - (x2), (y1) - (y2), (x3) - (x4), (y3) - (y4));
	p->y = ft_vec_cross_prod(ft_vec_cross_prod(x1, y1, x2, y2), (y1) - (y2), ft_vec_cross_prod(x3, y3, x4, y4), (y3) - (y4)) /
		ft_vec_cross_prod((x1) - (x2), (y1) - (y2), (x3) - (x4), (y3) - (y4));
}

double	ft_yaw(double y, double z, double p_yaw)
{
	return (y + z * p_yaw);
}

void	ft_scaler_init(t_scaler *scaler, int a, int b, int c, int d, int f)
{
	scaler->result = d + (b - 1 - a) * (f - d) / ((c - a != 0) ? (c - a) : 1);
	scaler->bop = ((f < d) ^ (c < a)) ? -1 : 1;
	scaler->fd = abs(f - d);
	scaler->ca = abs(c - a);
	scaler->cache = (int)((b - 1 - a) * abs(f - d)) % ((c - a != 0) ? abs(c - a) : 1);
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

int		ft_color_convert(int color, double lum)
{
	int r = ((color >> 16) & 0xFF) * lum;
	int g = ((color >> 8) & 0xFF) * lum;
	int b = (color & 0xFF) * lum;

	return (((r & 0xFF) << 16) + ((g & 0xFF) << 8) + ((b & 0xFF)));
}

void	ft_draw_vline(t_mlx *mlx, int x, int y1, int y2, int top_color,int middle_color, int bottom_color)
{
	y1 = ft_clamp(y1, 0, H - 1);
	y2 = ft_clamp(y2, 0, H - 1);

	if (mlx->sect[mlx->now->sector_n]->light == 0)
	{
		top_color = ft_color_convert(top_color, mlx->sect[mlx->now->sector_n]->lum);
		middle_color = ft_color_convert(middle_color, mlx->sect[mlx->now->sector_n]->lum);
		bottom_color = ft_color_convert(bottom_color, mlx->sect[mlx->now->sector_n]->lum);
	}

	if (y1 == y2)
	{
		if (y1 != H - 1 && y1 != 0)
		{
			if (mlx->opening[y1][x] == -1)
				mlx->data[x + y1 * W] = bottom_color;
		}
		else
		{
			if (mlx->opening[y1][x] == -1)
				mlx->data[x + y1 * W] = middle_color;
		}
		if (mlx->opening[y1][x] == -1 && mlx->open_f)
				mlx->opening[y1][x] = mlx->now->sector_n;
		return ;
	}
	else if (y2 > y1)
	{
		if (y1 != H - 1 && y1 != 0)
		{
			if (mlx->opening[y1][x] == -1)
				mlx->data[x + y1 * W] = top_color;
		}
		else
		{
			if (mlx->opening[y1][x] == -1)
				mlx->data[x + y1 * W] = middle_color;
		}
		if (mlx->opening[y1][x] == -1 && mlx->open_f)
			mlx->opening[y1][x] = mlx->now->sector_n;
		int y = y1 + 1;
		while (y <= y2)
		{
			if (mlx->opening[y][x] == -1)
			{
				mlx->data[x + y * W] = middle_color;
				if (mlx->open_f)
					mlx->opening[y][x] = mlx->now->sector_n;
			}
			y++;
		}
		if (y2 != H - 1 && y2 != 0)
		{
			if (mlx->opening[y1][x] == -1)
				mlx->data[x + y1 * W] = bottom_color;
		}
		else
		{
			if (mlx->opening[y1][x] == -1)
				mlx->data[x + y1 * W] = middle_color;
		}
		if (mlx->opening[y1][x] == -1 && mlx->open_f)
			mlx->opening[y1][x] = mlx->now->sector_n;
	}
}

void	ft_draw_tvline(t_mlx *mlx, int x, int y1, int y2, unsigned txtx, t_img *texture, int rend_i)
{
	y1 = ft_clamp(y1, 0, H - 1);
	y2 = ft_clamp(y2, 0, H - 1);

	int y = y1 - 1;
	while (++y < y2)
	{
		unsigned txty = ft_scaler_next(mlx->scaler);
		int color = texture->data[txty % texture->h * texture->w + txtx % texture->w];
		if (rend_i == 0 && mlx->opening[y][x] == -1)
		{
			if (mlx->sect[mlx->now->sector_n]->light == 0)
				color = ft_color_convert(color, mlx->sect[mlx->now->sector_n]->lum);
			mlx->data[x + y * W] = color;
			if (mlx->open_f)
				mlx->opening[y][x] = mlx->now->sector_n;
		}
		else if (rend_i == 1 && (mlx->opening[y][x] == -1 || mlx->opening[y][x] == mlx->now->sector_n) && color != IGNORE_COLOR && color != IGNORE_COLOR1)
		{
			if (mlx->sect[mlx->now->sector_n]->light == 0)
				color = ft_color_convert(color, mlx->sect[mlx->now->sector_n]->lum);
			mlx->data[x + y * W] = color;
			if (mlx->open_f)
				mlx->opening[y][x] = mlx->now->sector_n;
		}
	}
}

void	ft_upper_solid(t_mlx *mlx, int x, int cya, int cnya, int top_c, int middle_c, int bottom_c, short *ar_top)
{
	ft_draw_vline(mlx, x, cya, cnya - 1, top_c, middle_c, bottom_c);
	*ar_top = ft_clamp(ft_max(cya, cnya), *ar_top, H - 1);
}

void	ft_lower_solid(t_mlx *mlx, int x, int cnyb, int cyb, int bottom_c, int middle_c, int top_c, short *ar_bottom)
{
	ft_draw_vline(mlx, x, cnyb + 1, cyb, top_c, middle_c, bottom_c);
	*ar_bottom = ft_clamp(ft_min(cyb, cnyb), 0, *ar_bottom);
}

void	ft_upper_txt(t_mlx *mlx, int x, int cya, int cnya, int txtx, int txt_i, int ya, int yb, short *ar_top)
{
	ft_scaler_init(mlx->scaler, ya, cya, yb, mlx->u0, mlx->u1);
	ft_draw_tvline(mlx, x, cya, cnya - 1, txtx, mlx->txt[txt_i], 0);
	*ar_top = ft_clamp(ft_max(cya, cnya), *ar_top, H - 1);
}

void	ft_lower_txt(t_mlx *mlx, int x, int cnyb, int cyb, int txtx, int txt_i, int ya, int yb, short *ar_bottom)
{
	ft_scaler_init(mlx->scaler, ya, cnyb + 1, yb, mlx->u0, mlx->u1);
	ft_draw_tvline(mlx, x, cnyb + 1, cyb, txtx, mlx->txt[txt_i], 0);
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

void	ft_bzero(void *s, size_t n)
{
	size_t i;
	char *t;

	i = 0;
	t = (char *)s;
	while (n > i)
		t[i++] = '\0';
}