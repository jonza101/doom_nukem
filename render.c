/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:57 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/04 18:36:46 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

//		UNSTABLE
void	ft_transparent(t_mlx *mlx)
{
	int ytop[W] = {0};
	int ybottom[W];	
	int rendered_sect[mlx->num_sec];
	int i = -1;
	while (++i < W)
		ybottom[i] = H - 1;
	i = -1;
	while (++i < mlx->num_sec)
		rendered_sect[i] = 0;

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

		if ((rendered_sect[mlx->now->sector_n] & 0x21))
			continue;
		++rendered_sect[mlx->now->sector_n];

		t_sector *sector = mlx->sect[mlx->now->sector_n];
		int s = -1;
		while (++s < sector->verts_count)
		{
			int neighbor = ft_atoi(sector->neighbors[s]);
			if (neighbor < 0)
				continue ;
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
			int u1 = mlx->u1;

			//	IF IT'S PARTIALLY BEHIND THE PLAYER, CLIP IT AGAINST PLAYER'S VIEW FRUSTRUM
			if (tz1 <= 0 || tz2 <= 0)
			{
				double near_z = 1e-4f;
				double far_z = 5.0f;
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

				if (tz1 < near_z)
				{
					if (i1->y > 0)
					{
						tx1 = i1->x;
						tz1 = i1->y;
					}
					else
					{
						tx1 = i2->x;
						tz1 = i2->y;
					}
				}
				if (tz2 < near_z)
				{
					if (i1->y > 0)
					{
						tx2 = i1->x;
						tz2 = i1->y;
					}
					else
					{
						tx2 = i2->x;
						tz2 = i2->y;
					}
				}

				if (fabs(tx2 - tx1) > fabs(tz2 - tz1))
				{
					u0 = (tx1 - org1->x) * mlx->u1 / (org2->x - org1->x);
					u1 = (tx2 - org1->x) * mlx->u1 / (org2->x - org1->x);
				}
				else
				{
					u0 = (tz1 - org1->y) * mlx->u1 / (org2->y - org1->y);
					u1 = (tz2 - org1->y) * mlx->u1 / (org2->y - org1->y);
				}

				free(i1);
				free(i2);

				free(org1);
				free(org2);
			}

			//	DO PERSPECTIVE TRANSFORMATION
			double xscale1 = (W * FOV_H) / tz1;
			double yscale1 = (H * FOV_V) / tz1;
			int x1 = W / 2 + (int)(-tx1 * xscale1);
			double xscale2 = (W * FOV_H) / tz2;
			double yscale2 = (H * FOV_V) / tz2;
			int x2 = W / 2 + (int)(-tx2 * xscale2);

			if (x1 >= x2 || x2 < mlx->now->sx1 || x1 > mlx->now->sx2)
				continue;

			//	ACQUIRE THE FLOOR AND CEILING HEIGHTS, RELATIVE TO WHERE THE PLAYER'S VIEW IS
			double yceil = sector->ceiling - mlx->player->pos->z;
			double yfloor = sector->floor - mlx->player->pos->z;

			//	CHECK NEIGHBORS
			double nyceil = 0;
			double nyfloor = 0;
			if (neighbor >= 0)
			{
				nyceil = mlx->sect[neighbor]->ceiling - mlx->player->pos->z;
				nyfloor = mlx->sect[neighbor]->floor - mlx->player->pos->z;
			}

			//	PROJECT OUR CEILING & FLOOR HEIGHTS INTO SCREEN COORDINATES (Y COORDINATE)
			int y1a = H / 2 + (int)(-ft_yaw(yceil, tz1, mlx->player->yaw) * yscale1);
			int y1b = H / 2 + (int)(-ft_yaw(yfloor, tz1, mlx->player->yaw) * yscale1);
			int y2a = H / 2 + (int)(-ft_yaw(yceil, tz2, mlx->player->yaw) * yscale2);
			int y2b = H / 2 + (int)(-ft_yaw(yfloor, tz2, mlx->player->yaw) * yscale2);

			//	SAME FOR NEIGHBORS
			int ny1a = H / 2 + (int)(-ft_yaw(nyceil, tz1, mlx->player->yaw) * yscale1);
			int ny1b = H / 2 + (int)(-ft_yaw(nyfloor, tz1, mlx->player->yaw) * yscale1);
			int ny2a = H / 2 + (int)(-ft_yaw(nyceil, tz2, mlx->player->yaw) * yscale2);
			int ny2b = H / 2 + (int)(-ft_yaw(nyfloor, tz2, mlx->player->yaw) * yscale2);

			//	RENDER THE WALL
			int beginx = ft_max(x1, mlx->now->sx1);
			int endx = ft_min(x2, mlx->now->sx2);

			ft_scaler_init(mlx->ya_int, x1, beginx, x2, y1a, y2a);
            ft_scaler_init(mlx->yb_int, x1, beginx, x2, y1b, y2b);
            ft_scaler_init(mlx->nya_int, x1, beginx, x2, ny1a, ny2a);
            ft_scaler_init(mlx->nyb_int, x1, beginx, x2, ny1b, ny2b);

			int x = beginx - 1;
			while (++x <= endx)
			{
				int txtx = (u0 * ((x2 - x) * tz2) + u1 * ((x - x1) * tz1)) / ((x2 - x) * tz2 + (x - x1) * tz1);

				//	ACQUIRE THE Y COORDINATES FOR OUR CEILING & FLOOR FOR THIS X COORDINATE. CLAMP THEM
				int ya = ft_scaler_next(mlx->ya_int);
				int yb = ft_scaler_next(mlx->yb_int);
				
                int cya = ft_clamp(ya, ytop[x],ybottom[x]);
                int cyb = ft_clamp(yb, ytop[x],ybottom[x]);

				// RENDER NEIGBORS
				if (neighbor >= 0)
				{
					int nya = ft_scaler_next(mlx->nya_int);
					int nyb = ft_scaler_next(mlx->nyb_int);

                    int cnya = ft_clamp(nya, ytop[x], ybottom[x]);
                    int cnyb = ft_clamp(nyb, ytop[x], ybottom[x]);

					int ceil_p = (mlx->sect[neighbor]->ceiling > sector->ceiling) ? ya : nya;
					int floor_p = (mlx->sect[neighbor]->floor > sector->floor) ? nyb : yb;

					ft_scaler_init(mlx->scaler, ceil_p, nya, floor_p, mlx->u0, mlx->u1);
					ft_draw_tvline(mlx, x, ceil_p, floor_p, txtx, mlx->transparent[0], 1);
				}
			}
			if (neighbor >= 0 && beginx <= endx && (mlx->head + MAX_QUEUE + 1 - mlx->tail) % MAX_QUEUE)
			{
				mlx->head->sector_n = neighbor;
				mlx->head->sx1 = beginx;
				mlx->head->sx2 = endx;
				if (++mlx->head == mlx->queue + MAX_QUEUE)
					mlx->head = mlx->queue;
			}
		}
		++rendered_sect[mlx->now->sector_n];
	}
	// printf("\n__________________________________________________________\n\n");
}

void	ft_draw(t_mlx *mlx)
{
	short ytop[W] = {0};
	short ybottom[W];	
	short rendered_sect[mlx->num_sec];
	int i = -1;
	while (++i < W)
		ybottom[i] = H - 1;
	i = -1;
	while (++i < mlx->num_sec)
		rendered_sect[i] = 0;

	mlx->head = mlx->queue;
	mlx->tail = mlx->queue;

	mlx->head->sector_n = mlx->player->sector;
	mlx->head->sx1 = 0;
	mlx->head->sx2 = W - 1;
	if (++mlx->head == mlx->queue + MAX_QUEUE)
		mlx->head = mlx->queue;

	int f = 0;
	while (mlx->head != mlx->tail)
	{
		mlx->now = mlx->tail;
		if (++mlx->tail == mlx->queue + MAX_QUEUE)
			mlx->tail = mlx->queue;

		if ((rendered_sect[mlx->now->sector_n] & 0x21))
			continue;
		++rendered_sect[mlx->now->sector_n];

		t_sector *sector = mlx->sect[mlx->now->sector_n];
		mlx->seg = sector->verts_count;
		int s = -1;
		while (++s < sector->verts_count)
		{
			//	ACQUIRE THE X,Y COORDINATES OF THE TWO ENDPOINTS (VERTICES) OF THIS EDGE OF THE SECTOR
			double vx1 = sector->verts[s + 0]->x - mlx->player->pos->x;
			double vy1 = sector->verts[s + 0]->y - mlx->player->pos->y;
			double vx2 = sector->verts[s + 1]->x - mlx->player->pos->x;
			double vy2 = sector->verts[s + 1]->y - mlx->player->pos->y;

			// double dist = floorf(sqrtf(powf(sector->verts[s + 0]->x - sector->verts[s + 1]->x, 2) + powf(sector->verts[s + 0]->y - sector->verts[s + 1]->y, 2)));
			// printf("%f\n", dist);

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
			int u1 = mlx->u1;

			//	IF IT'S PARTIALLY BEHIND THE PLAYER, CLIP IT AGAINST PLAYER'S VIEW FRUSTRUM
			if (tz1 <= 0 || tz2 <= 0)
			{
				double near_z = 1e-4f;
				double far_z = 5.0f;
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

				if (tz1 < near_z)
				{
					if (i1->y > 0)
					{
						tx1 = i1->x;
						tz1 = i1->y;
					}
					else
					{
						tx1 = i2->x;
						tz1 = i2->y;
					}
				}
				if (tz2 < near_z)
				{
					if (i1->y > 0)
					{
						tx2 = i1->x;
						tz2 = i1->y;
					}
					else
					{
						tx2 = i2->x;
						tz2 = i2->y;
					}
				}

				if (fabs(tx2 - tx1) > fabs(tz2 - tz1))
				{
					u0 = (tx1 - org1->x) * mlx->u1 / (org2->x - org1->x);
					u1 = (tx2 - org1->x) * mlx->u1 / (org2->x - org1->x);
				}
				else
				{
					u0 = (tz1 - org1->y) * mlx->u1 / (org2->y - org1->y);
					u1 = (tz2 - org1->y) * mlx->u1 / (org2->y - org1->y);
				}

				free(i1);
				free(i2);

				free(org1);
				free(org2);
			}

			//	DO PERSPECTIVE TRANSFORMATION
			double xscale1 = (W * FOV_H) / tz1;
			double yscale1 = (H * FOV_V) / tz1;
			int x1 = W / 2 + (int)(-tx1 * xscale1);
			double xscale2 = (W * FOV_H) / tz2;
			double yscale2 = (H * FOV_V) / tz2;
			int x2 = W / 2 + (int)(-tx2 * xscale2);

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
			int y1a = H / 2 + (int)(-ft_yaw(yceil, tz1, mlx->player->yaw) * yscale1);
			int y1b = H / 2 + (int)(-ft_yaw(yfloor, tz1, mlx->player->yaw) * yscale1);
			int y2a = H / 2 + (int)(-ft_yaw(yceil, tz2, mlx->player->yaw) * yscale2);
			int y2b = H / 2 + (int)(-ft_yaw(yfloor, tz2, mlx->player->yaw) * yscale2);

			//	SAME FOR NEIGHBORS
			int ny1a = H / 2 + (int)(-ft_yaw(nyceil, tz1, mlx->player->yaw) * yscale1);
			int ny1b = H / 2 + (int)(-ft_yaw(nyfloor, tz1, mlx->player->yaw) * yscale1);
			int ny2a = H / 2 + (int)(-ft_yaw(nyceil, tz2, mlx->player->yaw) * yscale2);
			int ny2b = H / 2 + (int)(-ft_yaw(nyfloor, tz2, mlx->player->yaw) * yscale2);

			// int y1a = H / 2 + (int)(yceil * yscale1);
			// int y1b = H / 2 + (int)(yfloor * yscale1);
			// int y2a = H / 2 + (int)(yceil * yscale2);
			// int y2b = H / 2 + (int)(yfloor * yscale2);

			// //	SAME FOR NEIGHBORS
			// int ny1a = H / 2 + (int)(nyceil * yscale1);
			// int ny1b = H / 2 + (int)(nyfloor * yscale1);
			// int ny2a = H / 2 + (int)(nyceil * yscale2);
			// int ny2b = H / 2 + (int)(nyfloor * yscale2);

			//	RENDER THE WALL
			int beginx = ft_max(x1, mlx->now->sx1);
			int endx = ft_min(x2, mlx->now->sx2);

			ft_scaler_init(mlx->ya_int, x1, beginx, x2, y1a, y2a);
            ft_scaler_init(mlx->yb_int, x1, beginx, x2, y1b, y2b);
            ft_scaler_init(mlx->nya_int, x1, beginx, x2, ny1a, ny2a);
            ft_scaler_init(mlx->nyb_int, x1, beginx, x2, ny1b, ny2b);

			// double temp = dist / (endx -  beginx + 1);

			int x = beginx - 1;
			while (++x <= endx)
			{
				mlx->cya = -1;
				mlx->cyb = -1;
				mlx->cnya = -1;
				mlx->cnyb = -1;

				// double n = temp;
				// double nx = sector->verts[s + 0]->x + n * dist * (sector->verts[s + 1]->x - sector->verts[s + 0]->x);
				// double ny = sector->verts[s + 0]->y + n * dist * (sector->verts[s + 1]->y - sector->verts[s + 0]->y);
				// double interpolate_dist = sqrtf(powf(nx - mlx->player->pos->x, 2) + powf(ny - mlx->player->pos->y, 2));
				// printf("%f\n", interpolate_dist)
				// printf("nx %f			ny %f\n\n", nx, ny);
				// n += temp;

				int txtx = (u0 * ((x2 - x) * tz2) + u1 * ((x - x1) * tz1)) / ((x2 - x) * tz2 + (x - x1) * tz1);

				//	ACQUIRE THE Y COORDINATES FOR OUR CEILING & FLOOR FOR THIS X COORDINATE. CLAMP THEM
				int ya = ft_scaler_next(mlx->ya_int);
				int yb = ft_scaler_next(mlx->yb_int);
				
                mlx->cya = ft_clamp(ya, ytop[x],ybottom[x]);
                mlx->cyb = ft_clamp(yb, ytop[x],ybottom[x]);

				int ceil_t = sector->ceil_txt;
				int floor_t = sector->floor_txt;
				int ceil_f = (ceil_t >= 0) && (ceil_t < TXT);
				int floor_f = (floor_t >= 0) && (floor_t < TXT);
				if (ceil_f || floor_f)
				{
					int y = ytop[x] - 1;
					while (++y <= ybottom[x])
					{
						if (y >= mlx->cya && y <= mlx->cyb)
						{
							y = mlx->cyb;
							continue ;
						}
						double h = y < mlx->cya ? yceil : yfloor;
						ft_screenpoint_to_mappoint(mlx, h, x, y);
						unsigned txtx = (mlx->map_x * 32);
						unsigned txtz = (mlx->map_z * 32);
						//	RENDER CEILING
						if (y < mlx->cya && ceil_f)
							ft_image(mlx, x, y, mlx->txt[ceil_t]->data[txtz % mlx->txt[ceil_t]->h * mlx->txt[ceil_t]->w + txtx % mlx->txt[ceil_t]->w]);
						else if (y >= mlx->cya && floor_f)
							ft_image(mlx, x, y, mlx->txt[floor_t]->data[txtz % mlx->txt[floor_t]->h * mlx->txt[floor_t]->w + txtx % mlx->txt[floor_t]->w]);
					}
				}
				if (!ceil_f)
					ft_draw_vline(mlx, x, ytop[x], (mlx->cya - 1), LINE_COLOR, CEILING_COLOR, LINE_COLOR);
				if (!floor_f)
					ft_draw_vline(mlx, x, (mlx->cyb + 1), ybottom[x], LINE_COLOR, FLOOR_COLOR, LINE_COLOR);

				// ft_scaler_init(mlx->scaler, cya, cya, cyb, 0, 64);
				// ft_draw_tvline(mlx, x, 0, cya, txtx, mlx->sky[0], 0);

				// RENDER NEIGHBORS
				if (neighbor >= 0)
				{
					int nya = ft_scaler_next(mlx->nya_int);
					int nyb = ft_scaler_next(mlx->nyb_int);

                    mlx->cnya = ft_clamp(nya, ytop[x], ybottom[x]);
                    mlx->cnyb = ft_clamp(nyb, ytop[x], ybottom[x]);

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
							
							if (up >= 0 && up < TXT)
								ft_upper_txt(mlx, x, mlx->cya, mlx->cnya, txtx, up, ya, yb, &ytop[x]);
							else
								ft_upper_solid(mlx, x, mlx->cya, mlx->cnya, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : UPPER_COLOR, LINE_COLOR, &ytop[x]);

							if (low >= 0 && low < TXT)
								ft_lower_txt(mlx, x, mlx->cnyb, mlx->cyb, txtx, low, ya, yb, &ybottom[x]);
							else
								ft_lower_solid(mlx, x, mlx->cnyb, mlx->cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : LOWER_COLOR, LINE_COLOR, &ybottom[x]);
						}
						else
						{
							int txt_i = ft_atoi(sector->texts[s]);
							if (txt_i >= 0 && txt_i < TXT)
							{
								ft_upper_txt(mlx, x, mlx->cya, mlx->cnya, txtx, txt_i, ya, yb, &ytop[x]);
								ft_lower_txt(mlx, x, mlx->cnyb, mlx->cyb, txtx, txt_i, ya, yb, &ybottom[x]);
							}
							else
							{
								ft_upper_solid(mlx, x, mlx->cya, mlx->cnya, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : UPPER_COLOR, LINE_COLOR, &ytop[x]);
								ft_lower_solid(mlx, x, mlx->cnyb, mlx->cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : LOWER_COLOR, LINE_COLOR, &ybottom[x]);
							}
							
						}
						ft_strsplit_free(asd);
					}
					else
					{
						// RENDER UPPER WALL
						ft_upper_solid(mlx, x, mlx->cya, mlx->cnya, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : UPPER_COLOR, LINE_COLOR, &ytop[x]);
						// ft_image(mlx, x, mlx->cya, 0xFFFFF);
						// ft_image(mlx, x, mlx->cnya, 0xFFFF00);

						// RENDER LOWER WALL
						ft_lower_solid(mlx, x, mlx->cnyb, mlx->cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : LOWER_COLOR, LINE_COLOR, &ybottom[x]);
						// ft_image(mlx, x, mlx->cnyb + 1, 0xFFFFF);
						// ft_image(mlx, x, mlx->cyb, 0xFFFF00);
					}
				}
				else
				{
					if (sector->txt_count > 0)
					{
						int txt_i = ft_atoi(sector->texts[s]);
						if (txt_i >= 0 && txt_i < TXT)
						{
							ft_scaler_init(mlx->scaler, ya, mlx->cya, yb, mlx->u0, mlx->u1);
							ft_draw_tvline(mlx, x, mlx->cya, mlx->cyb, txtx, mlx->txt[txt_i], 0);
						}
						else
							ft_draw_vline(mlx, x, mlx->cya, mlx->cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : WALL_COLOR, LINE_COLOR);
					}
					// else if (s == 0)
					// 	ft_draw_vline(mlx, x, cya, cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : 0xFFFFF, LINE_COLOR);
					// else if (s == 1)
					// 	ft_draw_vline(mlx, x, cya, cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : 0xFF0000, LINE_COLOR);
					// else if (s == 2)
					// 	ft_draw_vline(mlx, x, cya, cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : 0x00FF00, LINE_COLOR);
					else
						ft_draw_vline(mlx, x, mlx->cya, mlx->cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : WALL_COLOR, LINE_COLOR);
				}
			}
			// if (f * mlx->seg + s >= mlx->drawseg_count)
			// {
			// 	printf("f %d\nseg %d\ns %d\n", f, mlx->seg, s);
			// 	printf("%d\n\n", f * mlx->seg + s);
			// }
			int index = f * mlx->seg + s;
			if (neighbor < 0 && index < mlx->drawseg_count)
			{
				mlx->drawseg[f * mlx->seg + s]->seg_type = 0;
				mlx->drawseg[f * mlx->seg + s]->x1 = beginx;
				mlx->drawseg[f * mlx->seg + s]->x2 = endx;

				t_vec2 *v1 = sector->verts[s + 0];
				t_vec2 *v2 = sector->verts[s + 1];
				t_vec3 *p = mlx->player->pos;
				double v1_dist = sqrtf(powf(v1->x - p->x, 2) + powf(v1->y - p->y, 2));
				double v2_dist = sqrtf(powf(v2->x - p->x, 2) + powf(v2->y - p->y, 2));
				mlx->drawseg[f * mlx->seg + s]->dist = (v1_dist > v2_dist) ? v1_dist : v2_dist;
				// // mlx->drawseg[f * mlx->seg + s]->dist = fabs((v2->y - v1->y) * p->x - (v2->x - v1->x) * p->y + v2->x * v1->y - v2->y * v1->x) / sqrtf(powf(v2->y - v1->y, 2) + powf(v2->x - v1->x, 2));
			}
			else if (neighbor >= 0 && index < mlx->drawseg_count)
			{
				if (mlx->cyb != mlx->cnyb && mlx->cya == mlx->cnya)
				{
					mlx->drawseg[f * mlx->seg + s]->seg_type = 1;
					mlx->drawseg[f * mlx->seg + s]->bottom_h = mlx->cnyb;
					mlx->drawseg[f * mlx->seg + s]->top_h = mlx->cya;
					mlx->drawseg[f * mlx->seg + s]->x1 = beginx;
					mlx->drawseg[f * mlx->seg + s]->x2 = endx;
				}
				else if (mlx->cyb == mlx->cnyb && mlx->cya != mlx->cnya)
				{
					mlx->drawseg[f * mlx->seg + s]->seg_type = 1;
					mlx->drawseg[f * mlx->seg + s]->bottom_h = mlx->cyb;
					mlx->drawseg[f * mlx->seg + s]->top_h = mlx->cnya;
					mlx->drawseg[f * mlx->seg + s]->x1 = beginx;
					mlx->drawseg[f * mlx->seg + s]->x2 = endx;
				}
				else if (mlx->cyb != mlx->cnyb && mlx->cya != mlx->cnya)
				{
					mlx->drawseg[f * mlx->seg + s]->seg_type = 1;
					mlx->drawseg[f * mlx->seg + s]->bottom_h = mlx->cnyb;
					mlx->drawseg[f * mlx->seg + s]->top_h = mlx->cnya;
					mlx->drawseg[f * mlx->seg + s]->x1 = beginx;
					mlx->drawseg[f * mlx->seg + s]->x2 = endx;
				}

				t_vec2 *v1 = sector->verts[s + 0];
				t_vec2 *v2 = sector->verts[s + 1];
				t_vec3 *p = mlx->player->pos;
				double v1_dist = sqrtf(powf(v1->x - p->x, 2) + powf(v1->y - p->y, 2));
				double v2_dist = sqrtf(powf(v2->x - p->x, 2) + powf(v2->y - p->y, 2));
				mlx->drawseg[f * mlx->seg + s]->dist = (v1_dist > v2_dist) ? v1_dist : v2_dist;
			}
			// printf("sector %d\n", mlx->now->sector_n);
			if (neighbor >= 0 && beginx <= endx && (mlx->head + MAX_QUEUE + 1 - mlx->tail) % MAX_QUEUE)
			{
				mlx->head->sector_n = neighbor;
				mlx->head->sx1 = beginx;
				mlx->head->sx2 = endx;
				if (++mlx->head == mlx->queue + MAX_QUEUE)
					mlx->head = mlx->queue;
			}
		}
		f++;
		++rendered_sect[mlx->now->sector_n];
	}
	// printf("\n__________________________________________________________\n\n");
}