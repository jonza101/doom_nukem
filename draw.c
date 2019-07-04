/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:57 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/04 18:05:42 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_draw(t_mlx *mlx)
{
	int ytop[W] = {0};
	int ybottom[W];	
	// int rendered_sect[mlx->num_sec];
	int i = -1;
	while (++i < W)
		ybottom[i] = H - 1;
	i = -1;
	// while (++i < mlx->num_sec)
		// rendered_sect[i] = 0;

	mlx->head = mlx->queue;
	mlx->tail = mlx->queue;

	mlx->head->sector_n = mlx->player->sector;
	mlx->head->sx1 = 0;
	mlx->head->sx2 = W - 1;
	if (++mlx->head == mlx->queue + MAX_QUEUE)
		mlx->head = mlx->queue;

	// int i = 0;
	while (mlx->head != mlx->tail)
	{
		mlx->now = mlx->tail;
		if (++mlx->tail == mlx->queue + MAX_QUEUE)
			mlx->tail = mlx->queue;

		// if ((rendered_sect[mlx->now->sector_n] & 0x21))
			// continue;
		// ++rendered_sect[mlx->now->sector_n];

		t_sector *sector = mlx->sect[mlx->now->sector_n];

		// printf("now %d		head %d		tail %d\nx1 %d		x1 %d		x1 %d\nx2 %d		x2 %d		x2 %d\n\n", mlx->now->sector_n, mlx->head->sector_n, mlx->tail->sector_n, mlx->now->sx1, mlx->head->sx1, mlx->tail->sx1, mlx->now->sx2, mlx->head->sx2, mlx->tail->sx2);

		// printf("head_s %d tail_s %d\n", mlx->head->sector_n, mlx->tail->sector_n);
		int s = -1;
		while (++s < sector->verts_count)
		{
			//	ACQUIRE THE X,Y COORDINATES OF THE TWO ENDPOINTS (VERTICES) OF THIS EDGE OF THE SECTOR
			double vx1 = sector->verts[s + 0]->x - mlx->player->pos->x;
			double vy1 = sector->verts[s + 0]->y - mlx->player->pos->y;
			double vx2 = sector->verts[s + 1]->x - mlx->player->pos->x;
			double vy2 = sector->verts[s + 1]->y - mlx->player->pos->y;

			//	ROTATE THEM AROUND THE PLAYER
			double p_cos = mlx->player->cos_angle;
			double p_sin = mlx->player->sin_angle;

			double tx1 = vx1 * p_sin - vy1 * p_cos;
			double tz1 = vx1 * p_cos + vy1 * p_sin;
			double tx2 = vx2 * p_sin - vy2 * p_cos;
			double tz2 = vx2 * p_cos + vy2 * p_sin;

			//	IS THE WALL AT LEAST PARTIALLY IN FRONT OF THE PLAYER?
			if (tz1 <= 0 && tz2 <= 0)
				continue;

			int u0 = 0;
			int u1 = 511;

			//	IF IT'S PARTIALLY BEHIND THE PLAYER, CLIP IT AGAINST PLAYER'S VIEW FRUSTRUM
			if (tz1 <= 0 || tz2 <= 0)
			{
				double near_z = 1e-4f;
				double far_z = 5;
				double nearside = 1e-5f;
				double farside = 20.0f;

				// //	FIND AN INTERSECTION BETWEEN THE WALL AND THE APPROXIMATE EDGES OF PLAYER'S VIEW
				t_vec2 *i1 = (t_vec2*)malloc(sizeof(t_vec2));
				t_vec2 *i2 = (t_vec2*)malloc(sizeof(t_vec2));

				ft_intersect(i1, tx1, tz1, tx2, tz2, -nearside, near_z, -farside, far_z);
				ft_intersect(i2, tx1, tz1, tx2, tz2, nearside, near_z, farside, far_z);

				t_vec2 *org1 = (t_vec2*)malloc(sizeof(t_vec2));
				t_vec2 *org2 = (t_vec2*)malloc(sizeof(t_vec2));
				org1->x = tx1;
				org1->y = tz1;
				org2->x = tx2;
				org2->y = tz2;

				if (tz1 < near_z) { if (i1->y > 0) { tx1 = i1->x; tz1 = i1->y; } else { tx1 = i2->x; tz1 = i2->y; }}
				if (tz2 < near_z) { if (i1->y > 0) { tx2 = i1->x; tz2 = i1->y; } else { tx2 = i2->x; tz2 = i2->y; }}

				if (fabs(tx2 - tx1) > fabs(tz2 - tz1))
				{
					u0 = (tx1 - org1->x) * 511 / (org2->x - org1->x);
					u1 = (tx2 - org1->x) * 511 / (org2->x - org1->x);
				}
				else
				{
					u0 = (tz1 - org1->y) * 511 / (org2->y - org1->y);
					u1 = (tz2 - org1->y) * 511 / (org2->y - org1->y);
				}

				free(i1);
				free(i2);

				free(org1);
				free(org2);
			}

			//	DO PERSPECTIVE TRANSFORMATION
			double xscale1 = FOV_H / tz1;
			double yscale1 = FOV_V / tz1;
			int x1 = W / 2 - (int)(tx1 * xscale1);
			double xscale2 = FOV_H / tz2;
			double yscale2 = FOV_V / tz2;
			int x2 = W / 2 - (int)(tx2 * xscale2);

			if (x1 >= x2 || x2 < mlx->now->sx1 || x1 > mlx->now->sx2)
				continue;

			//	ACQUIRE THE FLOOR AND CEILING HEIGHTS, RELATIVE TO WHERE THE PLAYER'S VIEW IS
			double yceil = sector->ceiling - mlx->player->pos->z;
			double yfloor = sector->floor - mlx->player->pos->z;

			//	CHECK NEIGHBORS
			int neighbor = ft_atoi(sector->neighbors[s]);
			double nyceil = 0;
			double nyfloor = 0;
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

			mlx->ya_int = ft_scaler_init(mlx->ya_int, x1,beginx,x2, y1a,y2a);
            mlx->yb_int = ft_scaler_init(mlx->yb_int, x1,beginx,x2, y1b,y2b);
            mlx->nya_int = ft_scaler_init(mlx->nya_int, x1,beginx,x2, ny1a,ny2a);
            mlx->nyb_int = ft_scaler_init(mlx->nyb_int, x1,beginx,x2, ny1b,ny2b);

			int x = beginx - 1;
			while (++x <= endx)
			{
				int txtx = (u0 * ((x2 - x) * tz2) + u1 * ((x - x1) * tz1)) / ((x2 - x) * tz2 + (x - x1) * tz1);

				//	ACQUIRE THE Y COORDINATES FOR OUR CEILING & FLOOR FOR THIS X COORDINATE. CLAMP THEM
				int ya = ft_scaler_next(mlx->ya_int);
				int yb = ft_scaler_next(mlx->yb_int);
				
                int cya = ft_clamp(ya, ytop[x],ybottom[x]);
                int cyb = ft_clamp(yb, ytop[x],ybottom[x]);

				//	ACQUIRE THE Y COORDINATES FOR OUR CEILING & FLOOR FOR THIS X COORDINATE. CLAMP THEM
				// int ya = (x - x1) * (y2a - y1a) / (x2 - x1) + y1a;
				// int cya = ft_clamp(ya, ytop[x], ybottom[x]);
				// int yb = (x - x1) * (y2b - y1b) / (x2 - x1) + y1b;
				// int cyb = ft_clamp(yb, ytop[x], ybottom[x]);

				//	RENDER CEILING
				ft_draw_vline(mlx, x, ytop[x], cya - 1, 0, 0x252525, 0);		//		0x757575
				//	RENDER FLOOR
				ft_draw_vline(mlx, x, cyb + 1, ybottom[x], 0, 0x252525, 0);

				// RENDER NEIGBORS
				if (neighbor >= 0)
				{
					int nya = ft_scaler_next(mlx->nya_int);
					int nyb = ft_scaler_next(mlx->nyb_int);

                    int cnya = ft_clamp(nya, ytop[x],ybottom[x]);
                    int cnyb = ft_clamp(nyb, ytop[x],ybottom[x]);

					// int nya = (x - x1) * (ny2a - ny1a) / (x2 - x1) + ny1a;
					// int cnya = ft_clamp(nya, ytop[x], ybottom[x]);
					// int nyb = (x - x1) * (ny2b - ny1b) / (x2 - x1) + ny1b;
					// int cnyb = ft_clamp(nyb, ytop[x], ybottom[x]);

					if (sector->txt_count > 0)
					{
						char **asd = ft_strsplit(sector->texts[s], '/');
						int count = 0;
						while (asd[count])
							count++;
						if (count == 2)
						{
							int up = ft_atoi(asd[1]);
							int low = ft_atoi(asd[0]);
							
							if (up >= 0)
								ft_upper_txt(mlx, x, cya, cnya, txtx, up, ya, yb, &ytop[x]);
							else
								ft_upper_solid(mlx, x, cya, cnya, 0, x == x1 || x == x2 ? 0 : 0x330315, 0, &ytop[x]);

							if (low >= 0)
								ft_lower_txt(mlx, x, cnyb, cyb, txtx, low, ya, yb, &ybottom[x]);
							else
								ft_lower_solid(mlx, x, cnyb, cyb, 0, x == x1 || x == x2 ? 0 : 0x1B0030, 0, &ybottom[x]);
						}
						else
						{
							int txt_i = ft_atoi(sector->texts[s]);
							if (txt_i >= 0)
							{
								ft_upper_txt(mlx, x, cya, cnya, txtx, txt_i, ya, yb, &ytop[x]);
								ft_lower_txt(mlx, x, cnyb, cyb, txtx, txt_i, ya, yb, &ybottom[x]);
							}
							else
							{
								ft_upper_solid(mlx, x, cya, cnya, 0, x == x1 || x == x2 ? 0 : 0x330315, 0, &ytop[x]);
								ft_lower_solid(mlx, x, cnyb, cyb, 0, x == x1 || x == x2 ? 0 : 0x1B0030, 0, &ybottom[x]);
							}
							
						}
					}
					else
					{
						// // RENDER UPPER WALL
						// ft_draw_vline(mlx, x, cya, cnya - 1, 0, x == x1 || x == x2 ? 0 : 0x330315, 0);
						// ytop[x] = ft_clamp(ft_max(cya, cnya), ytop[x], H - 1);
						ft_upper_solid(mlx, x, cya, cnya, 0, x == x1 || x == x2 ? 0 : 0x330315, 0, &ytop[x]);

						// // RENDER LOWER WALL
						// ft_draw_vline(mlx, x, cnyb + 1, cyb, 0, x == x1 || x == x2 ? 0 : 0x1B0030, 0);
						// ybottom[x] = ft_clamp(ft_min(cyb, cnyb), 0, ybottom[x]);
						ft_lower_solid(mlx, x, cnyb, cyb, 0, x == x1 || x == x2 ? 0 : 0x1B0030, 0, &ybottom[x]);
					}
				}
				else
				{
					if (sector->txt_count > 0)
					{
						int txt_i = ft_atoi(sector->texts[s]);
						if (txt_i >= 0)
						{
							mlx->scaler = ft_scaler_init(mlx->scaler, ya, cya, yb, 0, 511);
							ft_draw_tvline(mlx, x, cya, cyb, mlx->scaler, txtx, mlx->txt_temp[txt_i]);
						}
						else
							ft_draw_vline(mlx, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : 0x454545, 0);
					}
					else
						ft_draw_vline(mlx, x, cya, cyb, 0, x == x1 || x == x2 ? 0 : 0x454545, 0);
				}
			}
			if (neighbor >= 0 && beginx <= endx && (mlx->head + MAX_QUEUE + 1 - mlx->tail) % MAX_QUEUE)
			{
				mlx->head->sector_n = neighbor;
				mlx->head->sx1 = beginx;
				mlx->head->sx2 = endx;
				if (++mlx->head == mlx->queue + MAX_QUEUE)
					mlx->head = mlx->queue;
				// printf("neig %d		begin %d		end %d			bool %ld\n", neighbor, beginx, endx, (mlx->head + MAX_QUEUE + 1 - mlx->tail) % MAX_QUEUE);
				// printf("sect %d		s %d\n", mlx->now->sector_n, s);
				// ft_draw_vline(mlx, beginx, 0, H - 1, 0xDB0B0B, 0xDB0B0B, 0xDB0B0B);
				// ft_draw_vline(mlx, endx, 0, H - 1, 0xDB0B0B, 0xDB0B0B, 0xDB0B0B);
			}
			// else
			// {
			// 	printf("\nnot!\n");
			// 	printf("neig %d		begin %d		end %d			bool %ld\n", neighbor, beginx, endx, (mlx->head + MAX_QUEUE + 1 - mlx->tail) % MAX_QUEUE);
			// 	printf("sect %d		s %d\n", mlx->now->sector_n, s);
			// }
		}
		// ++rendered_sect[mlx->now->sector_n];
	}
	// printf("\n__________________________________________________________\n\n");
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}