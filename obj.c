/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:17:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/20 19:49:18 by zjeyne-l         ###   ########.fr       */
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

void	ft_obj(t_mlx *mlx)
{
	ft_obj_sort(mlx);
	t_obj *obj = mlx->obj_list;
	
	while (obj)
	{
		double dx = obj->specs->x - mlx->player->pos->x;
		double dy = obj->specs->y - mlx->player->pos->y;

		double dist_from_player = sqrtf(dx * dx + dy * dy);

		double eye_y = mlx->player->sin_angle;
		double eye_x = mlx->player->cos_angle;
		double obj_angle = atan2f(eye_y, eye_x) - atan2f(dy, dx);
		if (obj_angle < -3.14159f)
			obj_angle += 2 * 3.14159f;
		if (obj_angle > 3.14159f)
			obj_angle -= 2 * 3.14159f;

		obj_angle = obj_angle * H / W;
		int inf_fov = (fabs(obj_angle) <= 0.83f) ? 1 : 0;
		if (inf_fov && dist_from_player >= 1.0f)
		{
			double obj_middle = (W - (0.5 * (obj_angle / (0.63 / 1.0)) + 0.5) * W);

			double yceil = mlx->sect[obj->specs->sect]->ceiling - mlx->player->pos->z;
			double yfloor = mlx->sect[obj->specs->sect]->floor - mlx->player->pos->z;

			double p_cos = mlx->player->cos_angle;
			double p_sin = mlx->player->sin_angle;

			double yscale = (H * FOV_V) / dist_from_player;

			double obj_aspect_ratio = (double)mlx->obj[0]->h / (double)mlx->obj[0]->w;
			// printf("aspect_ratio	%f\n", obj_aspect_ratio);

			int ya = H / 2 + (int)(-ft_yaw(yceil, dist_from_player, mlx->player->yaw) * yscale) + ((H * mlx->obj[obj->specs->txt_index]->scaler) / dist_from_player);
			int yb = H / 2 + (int)(-ft_yaw(yfloor, dist_from_player, mlx->player->yaw) * yscale);

			double obj_h = (double)yb - (double)ya;
			double obj_w = (double)obj_h / (double)obj_aspect_ratio;

			// printf("yaw 		%f\n", mlx->player->yaw);
			// printf("yceil 		%f\n", yceil);
			// printf("yscale 		%f\n", yscale);
			// printf("dist 		%f\n", dist_from_player);
			// printf("middle 		%f\n", obj_middle);
			// printf("ya %d		yb %d\n", ya, yb);
			// printf("h %f	w %f\n", obj_h, obj_w);

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