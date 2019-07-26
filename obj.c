/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:17:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/26 18:53:39 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_texture_sampling(t_img *img, double sample_x, double sample_y)
{
	int sx;
	int sy;

	sx = sample_x * (double)img->w;
	sy = sample_y * (double)img->h;
	if (sx < 0 || sx > img->w || sy < 0 || sy > img->h)
		return (0x0);
	else
		return (img->data[sy * img->w + sx]);
}

void	ft_obj_dist(t_mlx *mlx)
{
	t_obj *obj = mlx->obj_list;
	while (obj)
	{
		double dx = obj->specs->x - mlx->player->pos->x;
		double dy = obj->specs->y - mlx->player->pos->y;
		obj->dist = sqrtf(dx * dx + dy * dy);
		obj = obj->next;
	}
}

void	ft_obj_sort(t_mlx *mlx)
{
	t_obj *obj = mlx->obj_list;
	ft_obj_dist(mlx);
	while (mlx->obj_list)
	{
		t_obj *nxt = mlx->obj_list->next;
		while (nxt)
		{
			if (mlx->obj_list->dist < nxt->dist)
			{
				t_obj_specs *temp = mlx->obj_list->specs;
				mlx->obj_list->specs = nxt->specs;
				nxt->specs = temp;
			}
			nxt = nxt->next;
		}
		mlx->obj_list = mlx->obj_list->next;
	}
	mlx->obj_list = obj;
}

double	ft_dot_prod(double x0, double y0, double x1, double y1)
{
	return (x0 * x1 + y0 * y1);
}

void	ft_obj(t_mlx *mlx)
{
	ft_obj_sort(mlx);
	t_obj *obj = mlx->obj_list;
	
	while (obj)
	{
		double px = mlx->player->pos->x;
		double py = mlx->player->pos->y;

		double dx = obj->specs->x -px;
		double dy = obj->specs->y - py;

		double dist_from_player = sqrtf(dx * dx + dy * dy);

		double eye_y = mlx->player->sin_angle;
		double eye_x = mlx->player->cos_angle;
		double obj_angle = atan2f(dy, dx) - atan2f(eye_y, eye_x);
		if (obj_angle < -3.14159f)
			obj_angle += (2 * 3.14159f);
		if (obj_angle > 3.14159f)
			obj_angle -= (2 * 3.14159f);
		obj_angle *= ((double)H / (double)W);
		int inf_fov = (fabs(obj_angle) <= 0.83f) ? 1 : 0;

		double obj_aspect_ratio = (double)mlx->obj[obj->specs->txt_index]->h / (double)mlx->obj[obj->specs->txt_index]->w;

		double vx1_l = (obj->specs->x - px) / dist_from_player;
		double vy1_l = (obj->specs->y - py) / dist_from_player;
		double vx2_l = vy1_l;
		double vy2_l = vx1_l;
		double vx1 = (obj->specs->x - px);
		double vy1 = (obj->specs->y - py);
		double vx2 = vx2_l + obj->specs->x - px;
		double vy2 = vy2_l + obj->specs->y - py;

		double p_cos = mlx->player->cos_angle;
		double p_sin = mlx->player->sin_angle;
		double tx1 = vx1 * p_sin - vy1 * p_cos;
		double tz1 = vx1 * p_cos + vy1 * p_sin;
		double tx2 = vx1 * p_sin - vy1 * p_cos;		//	vx2		vy2
		double tz2 = vx1 * p_cos + vy1 * p_sin;		//	vx2		vy2

		if (tz1 <= 0 && tz2 <= 0)
		{
			obj = obj->next;
			continue;
		}

		double xscale1 = (W * FOV_H) / tz1;
		double yscale1 = (H * FOV_V) / tz1;
		int x1 = W / 2 + (int)(-tx1 * xscale1);
		double xscale2 = (W * FOV_H) / tz2;
		double yscale2 = (H * FOV_V) / tz2;
		int x2 = W / 2 + (int)(-tx2 * xscale2);

		double yceil = mlx->sect[obj->specs->sect]->ceiling - mlx->player->pos->z;		//	TODO: FIX IT
		double yfloor = mlx->sect[obj->specs->sect]->floor - mlx->player->pos->z;

		int add_y1 = mlx->player->pos->z * (yscale1 - 41 / dist_from_player);
		int add_y2 = mlx->player->pos->z * (yscale2 - 41 / dist_from_player);
		int	offset_y1 = yscale1 * mlx->obj[obj->specs->txt_index]->scaler;
		int offset_y2 = yscale2 * mlx->obj[obj->specs->txt_index]->scaler;
		int ya1 = H / 2 + (int)(-ft_yaw(yceil, tz1, mlx->player->yaw * 4) * yscale1) / 4 + add_y1 + offset_y1;
		int yb1 = H / 2 + (int)(-ft_yaw(yfloor, tz1, mlx->player->yaw) * yscale1);
		int ya2 = H / 2 + (int)(-ft_yaw(yceil, tz2, mlx->player->yaw * 4) * yscale2) / 4 + add_y2 + offset_y2;
		int yb2 = H / 2 + (int)(-ft_yaw(yfloor, tz2, mlx->player->yaw) * yscale2);
		// printf("dist		%f\n", dist_from_player);
		// printf("x1 %d		x2 %d\n", x1, x2);
		// printf("ya %d	yb %d\n\n", ya1, yb1);
		// printf("ya1 %d	yb1 %d\n\n", ya2, yb2);

		int ojb_h, yb, ya;
		if (ya1 < ya2)
			ya = ya1;
		else
			ya = ya2;
		if (yb1 > yb2)
			yb = yb1;
		else
			yb = yb2;
		int obj_h = (yb - ya);
		int obj_w = obj_h / (double)obj_aspect_ratio;
		int obj_middle = (obj_w / 2) + x1;
		x1 = x1 - (obj_w / 2);
		obj_middle = (obj_w / 2) + x1;

		// printf("ya %d		yb %d\n\n", ya, yb);

		if (x1 >= (-W * 1) && x1 < (W * 2) && x2 >= (-W * 1) && x2 < (W * 2)
				&& ya >= (-H * 3) && ya < (H * 3) && yb >= (-H * 3) && yb < (H * 3)
				&& dist_from_player >= 1.0f)
		{
			int ox = -1;
			while (++ox < obj_w)
			{
				int oy = -1;
				while (++oy < obj_h)
				{
					double sample_ox = (double)ox / (double)obj_w;
					double sample_oy = (double)oy / (double)obj_h;
					int color = ft_texture_sampling(mlx->obj[obj->specs->txt_index], sample_ox, sample_oy);
					int xc = (int)(obj_middle - (obj_w / 2.0f) + ox);
					int yc = (int)ya + (int)oy;
					if (color != IGNORE_COLOR)
						ft_image(mlx, xc, yc, color);
				}
			}
		}
		obj = obj->next;
	}
}