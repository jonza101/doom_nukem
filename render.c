/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:26:57 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/31 19:11:24 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_wobj	*ft_find_wobj(t_mlx *mlx, int sect, int side)
{
	if (mlx->wobj_count <= 0)
		return (NULL);
	t_wobj *wobj = mlx->wobj_list;
	while (wobj)
	{
		if (!wobj->rendered && wobj->sect == sect && wobj->side == side)
		{
			wobj->rendered = 1;
			return (wobj);
		}
		wobj = wobj->next;
	}
	return (NULL);
}

double	ft_check(t_vec3 *p, t_vec2 *v1, t_vec2 *v2)
{
	double nx = v1->y - v2->y;
	double ny = v2->x - v1->x;

	double p_c = (nx * (p->x - v1->x) + ny * (p->y - v1->y)) / sqrtf(nx * nx + ny * ny);
	printf("check %f\n", p_c);
	return (p_c);
}

void	ft_skybox_render(t_mlx *mlx, int x, int y1, int y2)
{
	int offset_x = x + mlx->sky_offset_x;
	if (offset_x < 0)
		offset_x = abs(W + offset_x) % W;
	else if (offset_x > W - 1)
		offset_x = (offset_x - W) % W;

	int y = y1 - 1;
	while (++y <= y2)
	{
		if (y < mlx->cya && mlx->opening[y][x] == -1)
		{
			int offset_y = y + mlx->sky_offset_y;
			if (offset_y < 0)
				offset_y = abs(H - 1 + offset_y) % (H - 1);
			else if (offset_y > H - 1)
				offset_y = (offset_y - H) % H;
			double sx = (double)offset_x / (double)(W - 1);
			double sy = (double)offset_y / (double)(H - 1);
			int color = ft_texture_sampling(mlx->sky[0], sx, sy);
			mlx->data[y * W + x] = color;
		}
	}
}

void	ft_draw(t_mlx *mlx)
{
	short ytop[W];
	short ybottom[W];	
	short rendered_sect[mlx->num_sec];
	int i = -1;
	while (++i < W)
	{
		ytop[i] = 0;
		ybottom[i] = H - 1;
	}

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

	mlx->seg_i = 0;
	mlx->obj_i = 0;
	mlx->trans_i = 0;
	int f = 0;
	while (mlx->head != mlx->tail || !f)
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
			mlx->open_f = 0;

			mlx->r_trans = -1;

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

			// if (mlx->now->sector_n == mlx->player->sector)
				// printf("tz1 %f			tz2 %f\n", tz1, tz2);

			//	IS THE WALL AT LEAST PARTIALLY IN FRONT OF THE PLAYER?
			if (tz1 <= 0.0f && tz2 <= 0.0f)
			{
				// if (mlx->now->sector_n == mlx->player->sector)
					// printf("\n");
				continue;
			}

			int u0 = 0;
			int u1 = mlx->u1;

			//	IF IT'S PARTIALLY BEHIND THE PLAYER, CLIP IT AGAINST PLAYER'S VIEW FRUSTRUM
			if (tz1 <= 0.0f || tz2 <= 0.0f)
			{
				double near_z = 1e-4f;
				double far_z = 5.0f;
				double nearside = 1e-5f;
				double farside = 20.0f;

				// //	FIND AN INTERSECTION BETWEEN THE WALL AND THE APPROXIMATE EDGES OF PLAYER'S VIEW

				ft_intersect(mlx->i1, tx1, tz1, tx2, tz2, -nearside, near_z, -farside, far_z);
				ft_intersect(mlx->i2, tx1, tz1, tx2, tz2, nearside, near_z, farside, far_z);

				mlx->org1->x = tx1;
				mlx->org1->y = tz1;
				mlx->org2->x = tx2;
				mlx->org2->y = tz2;

				if (tz1 < near_z)
				{
					if (mlx->i1->y > 0)
					{
						tx1 = mlx->i1->x;
						tz1 = mlx->i1->y;
					}
					else
					{
						tx1 = mlx->i2->x;
						tz1 = mlx->i2->y;
					}
				}
				if (tz2 < near_z)
				{
					if (mlx->i1->y > 0)
					{
						tx2 = mlx->i1->x;
						tz2 = mlx->i1->y;
					}
					else
					{
						tx2 = mlx->i2->x;
						tz2 = mlx->i2->y;
					}
				}

				if (fabs(tx2 - tx1) > fabs(tz2 - tz1))
				{
					u0 = (tx1 - mlx->org1->x) * mlx->u1 / (mlx->org2->x - mlx->org1->x);
					u1 = (tx2 - mlx->org1->x) * mlx->u1 / (mlx->org2->x - mlx->org1->x);
				}
				else
				{
					u0 = (tz1 - mlx->org1->y) * mlx->u1 / (mlx->org2->y - mlx->org1->y);
					u1 = (tz2 - mlx->org1->y) * mlx->u1 / (mlx->org2->y - mlx->org1->y);
				}
			}

			//	DO PERSPECTIVE TRANSFORMATION
			double xscale1 = (W * FOV_H) / tz1;
			double yscale1 = (H * FOV_V) / tz1;
			int x1 = W / 2 + (int)(-tx1 * xscale1);
			double xscale2 = (W * FOV_H) / tz2;
			double yscale2 = (H * FOV_V) / tz2;
			int x2 = W / 2 + (int)(-tx2 * xscale2);

			if (mlx->now->sector_n == mlx->player->sector)
			{
				// printf("x1 %d				x2 %d\n", x1, x2);
				// printf("sx1 %d				sx2 %d\n", mlx->now->sx1, mlx->now->sx2);
			}

			if (x1 >= x2 || x2 < mlx->now->sx1 || x1 > mlx->now->sx2)
			{
				// if (mlx->now->sector_n == mlx->player->sector)
					// printf("next\n\n");
				continue;
			}

			//	ACQUIRE THE FLOOR AND CEILING HEIGHTS, RELATIVE TO WHERE THE PLAYER'S VIEW IS
			double yceil = sector->ceiling - mlx->player->pos->z;
			double yfloor = sector->floor - mlx->player->pos->z;

			//	CHECK NEIGHBORS
			int neighbor = (sector->neighbors[s]);
			double nyceil = 0;
			double nyfloor = 0;
			if (neighbor >= 0)
			{
				nyceil = mlx->sect[neighbor]->ceiling - mlx->player->pos->z;
				nyfloor = mlx->sect[neighbor]->floor - mlx->player->pos->z;
			}

			//	PROJECT OUR CEILING & FLOOR HEIGHTS INTO SCREEN COORDINATES (Y COORDINATE)
			int y1a = H / 2 + (int)(-(yceil + tz1 * mlx->player->yaw) * yscale1);
			int y1b = H / 2 + (int)(-(yfloor + tz1 * mlx->player->yaw) * yscale1);
			int y2a = H / 2 + (int)(-(yceil + tz2 * mlx->player->yaw) * yscale2);
			int y2b = H / 2 + (int)(-(yfloor + tz2 * mlx->player->yaw) * yscale2);

			//	SAME FOR NEIGHBORS
			int ny1a = H / 2 + (int)(-(nyceil + tz1 * mlx->player->yaw) * yscale1);
			int ny1b = H / 2 + (int)(-(nyfloor + tz1 * mlx->player->yaw) * yscale1);
			int ny2a = H / 2 + (int)(-(nyceil + tz2 * mlx->player->yaw) * yscale2);
			int ny2b = H / 2 + (int)(-(nyfloor + tz2 * mlx->player->yaw) * yscale2);

			//	RENDER THE WALL
			int beginx = ft_max(x1, mlx->now->sx1);
			int endx = ft_min(x2, mlx->now->sx2);

			if (mlx->now->sector_n == mlx->player->sector)
			{
				// printf("x1 %d			x2 %d\n", x1, x2);
				// printf("sx1 %d			sx2 %d\n", mlx->now->sx1, mlx->now->sx2);
				// printf("bx %d				ex %d\n\n", beginx, endx);
			}

			ft_scaler_init(mlx->ya_int, x1, beginx, x2, y1a, y2a);
            ft_scaler_init(mlx->yb_int, x1, beginx, x2, y1b, y2b);
            ft_scaler_init(mlx->nya_int, x1, beginx, x2, ny1a, ny2a);
            ft_scaler_init(mlx->nyb_int, x1, beginx, x2, ny1b, ny2b);

			////////////////////////////////////////////////////// WALL_OBJECTS //////////////////////////////////////////////////////
			int w_count = -1;
			while (++w_count < MAX_WSPRITES_ON_WALL)
			{
				mlx->rend_wobj[w_count]->wobj = ft_find_wobj(mlx, mlx->now->sector_n, s);
				mlx->rend_wobj[w_count]->w_flag = 1;
				if (!mlx->rend_wobj[w_count]->wobj)
					break;

				mlx->rend_wobj[w_count]->wu0 = mlx->wobj_l[mlx->rend_wobj[w_count]->wobj->wobj_i]->wobj_specs->u0;
				mlx->rend_wobj[w_count]->wu1 = mlx->wobj_l[mlx->rend_wobj[w_count]->wobj->wobj_i]->wobj_specs->u1;
			}

			ft_wobj_specs_calc(mlx, sector, s, w_count);
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			int x = beginx - 1;
			while (++x <= endx)
			{
				mlx->cya = -1;
				mlx->cyb = -1;
				mlx->cnya = -1;
				mlx->cnyb = -1;

				int txtx = (u0 * ((x2 - x) * tz2) + u1 * ((x - x1) * tz1)) / ((x2 - x) * tz2 + (x - x1) * tz1);

				//	ACQUIRE THE Y COORDINATES FOR OUR CEILING & FLOOR FOR THIS X COORDINATE. CLAMP THEM
				int ya = ft_scaler_next(mlx->ya_int);					//		 + x / 25
				int yb = ft_scaler_next(mlx->yb_int);					//		 + x / 25

                mlx->cya = ft_clamp(ya, ytop[x], ybottom[x]);
                mlx->cyb = ft_clamp(yb, ytop[x], ybottom[x]);

				//	SAME FOR NEIGHBORS
				int nya = ft_scaler_next(mlx->nya_int);
				int nyb = ft_scaler_next(mlx->nyb_int);

				mlx->cnya = ft_clamp(nya, ytop[x], ybottom[x]);
				mlx->cnyb = ft_clamp(nyb, ytop[x], ybottom[x]);

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

						//	RENDER CEILING TXT
						if (y < mlx->cya && ceil_f && mlx->opening[y][x] == -1 && !sector->sky)
						{
							int color = mlx->txt[ceil_t]->data[txtz % mlx->txt[ceil_t]->h * mlx->txt[ceil_t]->w + txtx % mlx->txt[ceil_t]->w];
							if (mlx->sect[mlx->now->sector_n]->light == 0)
								color = ft_color_convert(color, mlx->sect[mlx->now->sector_n]->lum);
							mlx->data[y * W + x] = color;
							if (mlx->cya != mlx->cnya && neighbor >= 0)
								mlx->opening[y][x] = mlx->now->sector_n;
						}
						else if (y >= mlx->cya && floor_f && mlx->opening[y][x] == -1)
						{
							int color = mlx->txt[floor_t]->data[txtz % mlx->txt[floor_t]->h * mlx->txt[floor_t]->w + txtx % mlx->txt[floor_t]->w];
							if (mlx->sect[mlx->now->sector_n]->light == 0)
								color = ft_color_convert(color, mlx->sect[mlx->now->sector_n]->lum);
							mlx->data[y * W + x] = color;
							if (mlx->cyb != mlx->cnyb && neighbor >= 0)
								mlx->opening[y][x] = mlx->now->sector_n;
						}
					}
				}
				if (!ceil_f && !sector->sky)
				{
					if (mlx->cya != mlx->cnya && neighbor >= 0)
						mlx->open_f = 1;
					ft_draw_vline(mlx, x, ytop[x], (mlx->cya), LINE_COLOR, CEILING_COLOR, LINE_COLOR);
					mlx->open_f = 0;
				}
				if (!floor_f)
				{
					if (mlx->cyb != mlx->cnyb && neighbor >= 0)
						mlx->open_f = 1;
					ft_draw_vline(mlx, x, (mlx->cyb), ybottom[x], LINE_COLOR, FLOOR_COLOR, LINE_COLOR);
					mlx->open_f = 0;
				}
				if (sector->sky)
					ft_skybox_render(mlx, x, ytop[x], ybottom[x]);

				// RENDER NEIGHBORS
				if (neighbor >= 0)
				{
					mlx->open_f = 1;
					if (sector->texts[s])
					{
						char **tmp = ft_strsplit(sector->texts[s], '/');
						int count = 0;
						while (tmp[count])
							count++;
						if (count == 2)
						{
							int up = ft_atoi(tmp[1]);
							int low = ft_atoi(tmp[0]);
							
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
						ft_strsplit_free(tmp);
					}
					else
					{
						// RENDER UPPER WALL
						ft_upper_solid(mlx, x, mlx->cya, mlx->cnya, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : UPPER_COLOR, LINE_COLOR, &ytop[x]);

						// RENDER LOWER WALL
						ft_lower_solid(mlx, x, mlx->cnyb, mlx->cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : LOWER_COLOR, LINE_COLOR, &ybottom[x]);
					}

					//////////////////////////////////////////////////////////	TRANSPARENT	//////////////////////////////////////////////////////////
					int trans_i = ft_find_trans_sect(mlx, mlx->now->sector_n, s);
					if (trans_i != -1)
					{
						int cl = (mlx->sect[neighbor]->ceiling < mlx->sect[mlx->now->sector_n]->ceiling) ? nya : ya;
						int fl = (mlx->sect[neighbor]->floor > mlx->sect[mlx->now->sector_n]->floor) ? nyb : yb;

						int c_cl = (cl == nya) ? mlx->cnya : mlx->cya;
						int c_fl = (fl == nyb) ? mlx->cnyb : mlx->cyb;

						if ((mlx->sect[neighbor]->ceiling > mlx->sect[mlx->now->sector_n]->floor) && (mlx->sect[mlx->now->sector_n]->ceiling > mlx->sect[neighbor]->floor))
						{
							ft_scaler_init(mlx->scaler, cl, c_cl, fl, mlx->u0, mlx->u1);
							ft_draw_tvline(mlx, x, c_cl, c_fl, txtx, mlx->trans[trans_i]->anim[0], 1);
						}
					}
					///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
					mlx->open_f = 0;
				}
				else
				{
					// mlx->open_f = 1;
					if (sector->texts[s])
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
					else
						ft_draw_vline(mlx, x, mlx->cya, mlx->cyb, LINE_COLOR, x == x1 || x == x2 ? LINE_COLOR : WALL_COLOR, LINE_COLOR);
					// mlx->open_f = 0;
				}

				////////////////////////////////////////////////////// WALL_OBJECTS //////////////////////////////////////////////////////
				int w = -1;
				while (++w < w_count)
				{
					if (mlx->rend_wobj[w]->w_flag && x >= mlx->rend_wobj[w]->wbeginx && x <= mlx->rend_wobj[w]->wendx)
					{
						int wtxtx = (mlx->rend_wobj[w]->wu0 * ((mlx->rend_wobj[w]->wx2 - x) * mlx->rend_wobj[w]->wtz2) +
									mlx->rend_wobj[w]->wu1 * ((x - mlx->rend_wobj[w]->wx1) * mlx->rend_wobj[w]->wtz1)) /
											((mlx->rend_wobj[w]->wx2 - x) * mlx->rend_wobj[w]->wtz2 + (x - mlx->rend_wobj[w]->wx1) * mlx->rend_wobj[w]->wtz1);

						int wya = ft_scaler_next(mlx->rend_wobj[w]->wya_int);
						int wyb = ft_scaler_next(mlx->rend_wobj[w]->wyb_int);

						int wcya = ft_clamp(wya, 0, H - 1);
						int wcyb = ft_clamp(wyb, 0, H - 1);

						ft_scaler_init(mlx->scaler, wya, wcya, wyb + 1, mlx->rend_wobj[w]->wu0, mlx->rend_wobj[w]->wu1);
						if (neighbor >= 0)
							ft_draw_tvline(mlx, x, wcya, wcyb, wtxtx, mlx->rend_wobj[w]->wobj->frame, 1);
						else
							ft_draw_tvline(mlx, x, wcya, wcyb, wtxtx, mlx->rend_wobj[w]->wobj->frame, 1);
					}
				}
				//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}

			int w = -1;
			while (++w < w_count)
			{
				mlx->rend_wobj[w]->wobj->rendered = 0;
				mlx->rend_wobj[w]->wobj = NULL;
			}

			if (mlx->r_trans != -1)
				mlx->trans_i++;

			int index = mlx->seg_i;
			if (index >= MAX_DRAWSEG)
				ft_drawseg_error();

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//	SPRITE CLIPPING
			if (neighbor < 0)												//		SOLID	WALL
			{
				t_vec2 *v1 = sector->verts[s + 0];
				t_vec2 *v2 = sector->verts[s + 1];
				t_vec3 *p = mlx->player->pos;

				mlx->drawseg[index].seg_type = 0;
				mlx->drawseg[index].x1 = beginx;
				mlx->drawseg[index].x2 = endx;

				double v1_dist = sqrtf(powf(v1->x - p->x, 2) + powf(v1->y - p->y, 2));
				double v2_dist = sqrtf(powf(v2->x - p->x, 2) + powf(v2->y - p->y, 2));
				double min_dist = ft_min(v1_dist, v2_dist);

				mlx->drawseg[index].dist = min_dist;
				mlx->drawseg[index].sect = mlx->now->sector_n;
			}
			mlx->seg_i++;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
		ft_sect_obj(mlx, mlx->now->sector_n);
		// if (mlx->now->sector_n == mlx->player->sector)
			// printf("----------------------------\n");
	}
}