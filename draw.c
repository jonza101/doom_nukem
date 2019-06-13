/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:57 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/13 20:32:17 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_draw(t_mlx *mlx)
{
	int ytop[W] = {0};
	int ybottom[W];	
	int x = -1;
	while (++x < W)
		ybottom[x] = H - 1;

	mlx->head = mlx->queue;
	mlx->tail = mlx->queue;

	mlx->head->sector_n = mlx->player->sector;
	mlx->head->sx1 = 0;
	mlx->head->sx2 = W - 1;
	if (++mlx->head == mlx->queue + MAX_QUEUE)
		mlx->head = mlx->queue;

	int i = 0;
	while (mlx->head != mlx->tail)
	{
		mlx->now = mlx->tail;
		if (++mlx->tail == mlx->queue + MAX_QUEUE)
			mlx->tail = mlx->queue;

		t_sector *sector = mlx->sect[mlx->now->sector_n];

		int s = -1;
		while (++s < sector->verts_count)
		{
			// printf("s %d\n", s);
			//	ACQUIRE THE X,Y COORDINATES OF THE TWO ENDPOINTS (VERTICES) OF THIS EDGE OF THE SECTOR
			float vx1 = sector->verts[s + 0]->x - mlx->player->pos->x;
			float vy1 = sector->verts[s + 0]->y - mlx->player->pos->y;
			float vx2 = sector->verts[s + 1]->x - mlx->player->pos->x;
			float vy2 = sector->verts[s + 1]->y - mlx->player->pos->y;

			//	ROTATE THEM AROUND THE PLAYER
			float p_cos = mlx->player->cos_angle;
			float p_sin = mlx->player->sin_angle;

			float tx1 = vx1 * p_sin - vy1 * p_cos;
			float tz1 = vx1 * p_cos + vy1 * p_sin;
			float tx2 = vx2 * p_sin - vy2 * p_cos;
			float tz2 = vx2 * p_cos + vy2 * p_sin;

			//	IS THE WALL AT LEAST PARTIALLY IN FRONT OF THE PLAYER?
			if (tz1 <= 0 && tz2 <= 0)
				continue;

			//	IF IT'S PARTIALLY BEHIND THE PLAYER, CLIP IT AGAINST PLAYER'S VIEW FRUSTRUM
			if (tz1 <= 0 || tz2 <= 0)
			{
				float near_z = 1e-4f;
				float far_z = 5;
				float nearside = 1e-5f;
				float farside = 20.0f;

				// //	FIND AN INTERSECTION BETWEEN THE WALL AND THE APPROXIMATE EDGES OF PLAYER'S VIEW
				t_vec2 *i1 = (t_vec2*)malloc(sizeof(t_vec2));
				t_vec2 *i2 = (t_vec2*)malloc(sizeof(t_vec2));

				ft_intersect(i1, tx1, tz1, tx2, tz2, -nearside, near_z, -farside, far_z);
				ft_intersect(i2, tx1, tz1, tx2, tz2, nearside, near_z, farside, far_z);

				if (tz1 < near_z) { if (i1->y > 0) { tx1 = i1->x; tz1 = i1->y; } else { tx1 = i2->x; tz1 = i2->y; }}
				if (tz2 < near_z) { if (i1->y > 0) { tx2 = i1->x; tz2 = i1->y; } else { tx2 = i2->x; tz2 = i2->y; }}

				free(i1);
				free(i2);
			}

			//	DO PERSPECTIVE TRANSFORMATION
			float xscale1 = FOV_H / tz1;
			float yscale1 = FOV_V / tz1;
			int x1 = W / 2 - (int)(tx1 * xscale1);
			float xscale2 = FOV_H / tz2;
			float yscale2 = FOV_V / tz2;
			int x2 = W / 2 - (int)(tx2 * xscale2);

			if (x1 >= x2 || x2 < mlx->now->sx1 || x1 > mlx->now->sx2)
				continue;

			//	ACQUIRE THE FLOOR AND CEILING HEIGHTS, RELATIVE TO WHERE THE PLAYER'S VIEW IS
			float yceil = sector->ceiling - mlx->player->pos->z;
			float yfloor = sector->floor - mlx->player->pos->z;

			//	CHECK NEIGHBORS
			int neighbor = ft_atoi(sector->neighbors[s]);
			float nyceil = 0;
			float nyfloor = 0;
			if (neighbor >= 0)
			{
				nyceil = mlx->sect[neighbor]->ceiling - mlx->player->pos->z;
				nyfloor = mlx->sect[neighbor]->floor - mlx->player->pos->z;
			}

			//	PROJECT OUR CEILING & FLOOR HEIGHTS INTO SCREEN COORDINATES (Y COORDINATE)
			int y1a = H / 2 - (int)(ft_yaw(yceil, tz1, mlx->player->yaw) * yscale1);
			int y1b = H / 2 - (int)(ft_yaw(yfloor, tz1, mlx->player->yaw) * yscale1);
			int y2a = H / 2 - (int)(ft_yaw(yceil, tz2, mlx->player->yaw) * yscale2);
			int y2b = H / 2 - (int)(ft_yaw(yfloor, tz2, mlx->player->yaw) * yscale2);

			//	SAME FOR NEIGHBORS
			int ny1a = H / 2 - (int)(ft_yaw(nyceil, tz1, mlx->player->yaw) * yscale1);
			int ny1b = H / 2 - (int)(ft_yaw(nyfloor, tz1, mlx->player->yaw) * yscale1);
			int ny2a = H / 2 - (int)(ft_yaw(nyceil, tz2, mlx->player->yaw) * yscale2);
			int ny2b = H / 2 - (int)(ft_yaw(nyfloor, tz2, mlx->player->yaw) * yscale2);

			//	RENDER THE WALL
			int beginx = ft_max(x1, mlx->now->sx1);
			int endx = ft_min(x2, mlx->now->sx2);
			int x = beginx - 1;
			while (++x <= endx)
			{
				//	ACQUIRE THE Y COORDINATES FOR OUR CEILING & FLOOR FOR THIS X COORDINATE. CLAMP THEM
				int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				int cya = ft_clamp(ya, ytop[x], ybottom[x]);
				int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				int cyb = ft_clamp(yb, ytop[x], ybottom[x]);

				//	RENDER CEILING
				ft_draw_vline(mlx, x, ytop[x], cya - 1, 0, 0x252525, 0);		//		0x757575
				//	RENDER FLOOR
				ft_draw_vline(mlx, x, cyb + 1, ybottom[x], 0, 0x252525, 0);

				// RENDER NEIGBORS
				if (neighbor >= 0)
				{
					int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					int cnya = ft_clamp(nya, ytop[x], ybottom[x]);
					int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					int cnyb = ft_clamp(nyb, ytop[x], ybottom[x]);

					ft_draw_vline(mlx, x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : 0x4A0909, 0);
					ytop[x] = ft_clamp(ft_max(cya, cnya), ytop[x], H - 1);

					ft_draw_vline(mlx, x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : 0x290A42, 0);
					ybottom[x] = ft_clamp(ft_min(cyb, cnyb), 0, ybottom[x]);
				}
				else
					ft_draw_vline(mlx, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : 0x454545, 0);
			}
			if (neighbor >= 0 && endx >= beginx && (mlx->head + MAX_QUEUE + 1 - mlx->tail) % MAX_QUEUE)
			{
				mlx->head->sector_n = neighbor;
				mlx->head->sx1 = beginx;
				mlx->head->sx2 = endx;
				if (++mlx->head == mlx->queue + MAX_QUEUE)
					mlx->head = mlx->queue;
			}
		}
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}