/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:17:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/15 20:45:06 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


// 	int i = 0;
// 	while (i < OBJ)
// 	{
// 		double vector_x = mlx->objs[i]->x - mlx->player->x;
// 		double vector_y = mlx->objs[i]->y - mlx->player->y;

// 		double dist_from_player = sqrtf(vector_x * vector_x + vector_y * vector_y);

// 		double eye_x = sinf(mlx->player->pov);
// 		double eye_y = cosf(mlx->player->pov);
// 		double obj_angle = atan2f(eye_y, eye_x) - atan2f(vector_y, vector_x);
// 		if (obj_angle < -3.14159)
// 			obj_angle += 2.0 * 3.14159;
// 		if (obj_angle > 3.14159)
// 			obj_angle -= 2.0 * 3.14159;

// 		int in_fov = (fabs(obj_angle) <= mlx->player->fov / 2.0) ? 1 : 0;

// 		if (in_fov == 1 && dist_from_player >= 1 && dist_from_player < mlx->depth)
// 		{
// 			double obj_ceiling = (double)(H / 2.0) - (double)H / (double)dist_from_player;
// 			double obj_floor = (double)H - (double)obj_ceiling;
// 			double obj_h = (double)obj_floor - (double)obj_ceiling;
// 			double obj_aspect_ratio = (double)mlx->objs[i]->img->h / (double)mlx->objs[i]->img->w;
// 			double obj_w = (double)obj_h / (double)obj_aspect_ratio;

// 			double obj_middle = (double)(0.5 * (obj_angle / (mlx->player->fov / 2.0)) + 0.5) * (double)W;

// 			int ox = 0;
// 			while (ox < obj_w)
// 			{
// 				int oy = 0;
// 				while (oy < obj_h)
// 				{
// 					double sample_ox = ox / obj_w;
// 					double sample_oy = oy / obj_h;

// 					int color = ft_texture_sampling(mlx->objs[i]->img, sample_ox, sample_oy);

// 					int obj_col = (int)(obj_middle + ox - (obj_w / 2.0));
// 					if (obj_col >= 0 && obj_col < W)
// 						if (color != 0x980088 && mlx->depth_buff[obj_col] >= dist_from_player)
// 						{
// 							ft_image(mlx, obj_col, obj_ceiling + oy, color);
// 							//mlx->depth_buff[obj_col] = dist_from_player;
// 						}
// 					oy++;
// 				}
// 				ox++;
// 			}
// 		}
// 		i++;
// 	}

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
			int inf_fov = (fabs(obj_angle) <= 0.63 / 1.0) ? 1 : 0;
			if (inf_fov)
			{
				// printf("draw\n");
				double obj_ceil = (sector->ceiling - 0) / (double)dist_from_player;		//	mlx->player->pos->z
				double obj_floor = fabs((sector->floor - 0) / (double)dist_from_player);	//	mlx->player->pos->z
				double obj_h = fabs((double)obj_floor - (double)obj_ceil) * 10;
				double obj_aspect_ratio = (double)mlx->obj[0]->h / (double)mlx->obj[0]->w;
				double obj_w = (double)obj_h / (double)obj_aspect_ratio * 1;
				// printf("dist %f\n", dist_from_player);
				// printf("ceil %f			floor %f\n", obj_ceil, obj_floor);
				// printf("h %f			w %f\n", obj_h, obj_w);
				// printf("aspect_ratio 			%f\n", obj_aspect_ratio);
				double obj_middle = W - (0.5 * (obj_angle / (0.63 / 1.0)) + 0.5) * W;

				int ox = -1;
				while (++ox < obj_w)
				{
					int oy = -1;
					while (++oy < obj_h)
					{
						double sample_ox = (double)ox / (double)obj_w;
						double sample_oy = (double)oy / (double)obj_h;
						int color = ft_texture_sampling(mlx->obj[0], sample_ox, sample_oy);
						int obj_col = (int)(obj_middle) + ox - (obj_w / 2.0);
						if (obj_col >= 0 && obj_col < W && color != IGNORE_COLOR)
							ft_image(mlx, obj_col, obj_ceil + oy, color);
					}
				}
			}
			
		// }
	// }
}