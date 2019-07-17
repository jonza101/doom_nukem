/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:17:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/17 19:22:16 by zjeyne-l         ###   ########.fr       */
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

void	ft_obj(t_mlx *mlx)
{
	int s = -1;
	// while (++s < mlx->num_sec)
	// {
		// printf("s %d\n", s);
		int i = 0;
		t_sector *sector = mlx->sect[1];
		// while (sector->objects[i])
		// {
			double dx = sector->objects[i]->x - mlx->player->pos->x;
			double dy = sector->objects[i]->y - mlx->player->pos->y;

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
				double obj_middle = W - (0.5 * (obj_angle / (0.63 / 1.0)) + 0.5) * W;
				
				double yscale = (H * FOV_V) / dist_from_player;

				double yceil = sector->ceiling - mlx->player->pos->z;
				double yfloor = sector->floor - mlx->player->pos->z;

				int ya = H / 2 + (int)(-ft_yaw(yceil, dist_from_player, mlx->player->yaw) * yscale) / 1;
				int yb = H / 2 + (int)(-ft_yaw(yfloor, dist_from_player, mlx->player->yaw) * yscale) / 1;

				double obj_aspect_ratio = (double)mlx->obj[0]->h / (double)mlx->obj[0]->w;
				double obj_h = (double)yb - (double)ya;
				double obj_w = (double)obj_h / (double)obj_aspect_ratio;

				printf("yscale 		%f\n", yscale);
				printf("middle 		%f\n", obj_middle);
				printf("ya %d		yb %d\n", ya, yb);
				printf("h %f	w %f\n", obj_h, obj_w);

				int ox = -1;
				while (++ox < obj_w)
				{
					int oy = -1;
					while (++oy < obj_h)
					{
						double sample_ox = (double)ox / (double)obj_w;
						double sample_oy = (double)oy / (double)obj_h;
						int color = ft_texture_sampling(mlx->obj[0], sample_ox, sample_oy);
						int xc = (int)(obj_middle - (obj_w / 2.0f) + ox);
						int yc = (int)ya + (int)oy;
						if (color != IGNORE_COLOR)
							ft_image(mlx, xc, yc, color);
					}
				}
			}
		// }
	// }
}