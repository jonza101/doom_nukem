/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 15:17:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/02 20:15:42 by zjeyne-l         ###   ########.fr       */
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

void	ft_sect_obj_dist(t_mlx *mlx, int sect)
{
	t_obj *obj = mlx->sect[sect]->obj_list;
	while (obj)
	{
		double dx = obj->specs->x - mlx->player->pos->x;
		double dy = obj->specs->y - mlx->player->pos->y;
		obj->dist = sqrtf(dx * dx + dy * dy);
		obj = obj->next;
	}
}

void	ft_sect_obj_sort(t_mlx *mlx, int sect)
{
	if (mlx->sect[sect]->obj_count <= 0)
		return;
	t_obj *obj = mlx->sect[sect]->obj_list;
	ft_sect_obj_dist(mlx, sect);
	while (mlx->sect[sect]->obj_list)
	{
		t_obj *nxt = mlx->sect[sect]->obj_list->next;
		while (nxt)
		{
			if (mlx->sect[sect]->obj_list->dist < nxt->dist)
			{
				t_obj_specs *temp = mlx->sect[sect]->obj_list->specs;
				mlx->sect[sect]->obj_list->specs = nxt->specs;
				nxt->specs = temp;
			}
			nxt = nxt->next;
		}
		mlx->sect[sect]->obj_list = mlx->sect[sect]->obj_list->next;
	}
	mlx->sect[sect]->obj_list = obj;
}

void	ft_drawseg_sort(t_mlx *mlx)
{
	int i = -1;
	while (++i <= mlx->seg_i - 1)
	{
		int j = i - 1;
		while (++j <= mlx->seg_i)
		{
			if (mlx->drawseg[i].dist > mlx->drawseg[j].dist)
			{
				t_drawseg temp = mlx->drawseg[i];
				mlx->drawseg[i] = mlx->drawseg[j];
				mlx->drawseg[j] = temp;
			}
		}
	}
}

void	ft_drawseg_clear(t_mlx *mlx)
{
	int i = -1;
	while (++i <= mlx->seg_i)
	{
		mlx->drawseg[i].seg_type = -1;
		mlx->drawseg[i].x1 = -1;
		mlx->drawseg[i].x2 = -1;
		mlx->drawseg[i].dist = DBL_MAX;
	}
}

void	ft_opening_clear(t_mlx *mlx)
{
	int y = -1;
	while (++y < H)
	{
		int x = -1;
		while (++x < W)
			mlx->opening[y][x] = -1;
	}
}

void	ft_obj_angle(t_mlx *mlx, t_obj *obj)
{
	double dx = obj->specs->x - mlx->player->pos->x;
	double dy = obj->specs->y - mlx->player->pos->y;

	double obj_angle = atan2f(dy, dx) + obj->specs->pov;
	if (obj_angle < -3.14159f)
		obj_angle += (2 * 3.14159f);
	if (obj_angle > 3.14159f)
		obj_angle -= (2 * 3.14159f);

	if (obj_angle >= -0.3839724f && obj_angle < 0.3839724f)
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[0];
	else if (obj_angle >= 0.3839724f && obj_angle < 1.169371f)
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[7];
	else if (obj_angle >= 1.169371f && obj_angle < 1.9547688f)
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[6];
	else if (obj_angle >= 1.9547688f && obj_angle < 2.7401669f)
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[5];
	else if ((obj_angle >= 2.7401669f && obj_angle <= 3.14159f) || (obj_angle <= -2.7401669f && obj_angle >= -3.14159f))
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[4];
	else if (obj_angle > -2.7401669f && obj_angle <= -1.9547688f)
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[3];
	else if (obj_angle > -1.9547688f && obj_angle <= -1.169371f)
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[2];
	else if (obj_angle > -1.169371f && obj_angle <= -0.3839724f)
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->rot[1];
}

void	ft_draw_sector_obj(t_mlx *mlx, t_obj *obj, int sector)
{
	ft_drawseg_sort(mlx);
	double px = mlx->player->pos->x;
	double py = mlx->player->pos->y;

	t_img *frame = obj->specs->frame;

	if (mlx->obj_l[obj->specs->obj_i]->anim_n > 1)
		ft_obj_anim(mlx, obj);

	if (mlx->obj_l[obj->specs->obj_i]->can_rotate)
		ft_obj_angle(mlx, obj);

	double obj_aspect_ratio = (double)frame->h / (double)frame->w;

	double vx1_l = (obj->specs->x - px) / obj->dist;
	double vy1_l = (obj->specs->y - py) / obj->dist;
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
	double tx2 = vx1 * p_sin - vy1 * p_cos;
	double tz2 = vx1 * p_cos + vy1 * p_sin;

	if (tz1 <= 0 && tz2 <= 0)
		return ;

	double xscale1 = (W * FOV_H) / tz1;
	double yscale1 = (H * FOV_V) / tz1;
	int x1 = W / 2 + (int)(-tx1 * xscale1);
	double yscale2 = (H * FOV_V) / tz2;

	double yfloor = mlx->sect[obj->specs->sect]->floor - mlx->player->pos->z;
	double yceil = mlx->sect[obj->specs->sect]->ceiling - mlx->player->pos->z;
	if (yfloor < 0)
		yceil = 30.0f - fabs(yfloor * 4.025f);
	else
		yceil = 30.0f + yfloor * 4.025f;

	int	fix_obj_h1 = yscale1 * mlx->obj_l[obj->specs->obj_i]->scaler;
	int fix_obj_h2 = yscale2 * mlx->obj_l[obj->specs->obj_i]->scaler;
	int ya1 = H / 2 + (int)(-ft_yaw(yceil, tz1, mlx->player->yaw * 4) * yscale1) / 4 + fix_obj_h1;
	int yb1 = H / 2 + (int)(-ft_yaw(yfloor, tz1, mlx->player->yaw) * yscale1);
	int ya2 = H / 2 + (int)(-ft_yaw(yceil, tz2, mlx->player->yaw * 4) * yscale2) / 4 + fix_obj_h2;
	int yb2 = H / 2 + (int)(-ft_yaw(yfloor, tz2, mlx->player->yaw) * yscale2);

	int ojb_h, yb, ya;
	if (ya1 < ya2)
		ya = ya1;
	else
		ya = ya2;
	if (yb1 > yb2)
		yb = yb1;
	else
		yb = yb2;

	double expl_scaler = (frame == mlx->obj_l[8]->anim[19] || frame == mlx->obj_l[8]->anim[20] || frame == mlx->obj_l[8]->anim[21]) ? 0.75 : 0.0f;

	int obj_h = (yb - ya);
	int obj_w = obj_h / ((double)obj_aspect_ratio * (mlx->obj_l[obj->specs->obj_i]->aspect_scaler + expl_scaler));
	x1 = x1 - (obj_w / 2.0f);
	int obj_middle = (obj_w / 2.0f) + x1;
	int x2 = x1 + obj_w;

	obj->specs->x1 = x1;
	obj->specs->x2 = x2;
	obj->specs->y1 = ya;
	obj->specs->y2 = yb;

	int f = -1;
	while (++f <= mlx->seg_i)
	{
		if (mlx->drawseg[f].seg_type == 0 && mlx->drawseg[f].sect != obj->specs->sect && mlx->drawseg[f].dist < obj->dist && ft_overlap(x1, x2, mlx->drawseg[f].x1, mlx->drawseg[f].x2))
		{
			int y = -1;
			while (++y < H)
			{
				int x = ft_clamp(mlx->drawseg[f].x1, 0, W - 1) - 1;
				int x_2 = ft_clamp(mlx->drawseg[f].x2, 0, W - 1);
				while (++x <= x_2)
				{
					if (x >= 0 && x < W && y >= 0 && y < H)
						mlx->opening[y][x] = mlx->drawseg[f].sect;
				}
			}
		}
	}

	if (x1 < -W || x1 > 2 * W || x2 < -W || x2 > 2 * W || obj->dist < 0.25f)
		return ;
	int ox = -1;
	while (++ox < obj_w)
	{
		int xc = (int)(obj_middle - (obj_w / 2.0f) + ox);
		int oy = -1;
		while (++oy < obj_h)
		{
			double sample_ox = (double)ox / (double)obj_w;
			double sample_oy = (double)oy / (double)obj_h;
			int color = ft_texture_sampling(frame, sample_ox, sample_oy);
			int yc = (int)ya + (int)oy;
			if (color != IGNORE_COLOR && color != IGNORE_COLOR1)
			{
				if (yc >= 0 && yc < H && xc >= 0 && xc < W)
				{
					if ((mlx->opening[yc][xc] == obj->specs->sect || mlx->opening[yc][xc] == -1))
					{
						if (mlx->sect[mlx->now->sector_n]->light == 0 && !mlx->obj_l[obj->specs->obj_i]->is_boost)
							color = ft_color_convert(color, mlx->sect[mlx->now->sector_n]->lum);
						mlx->data[yc * W + xc] = color;
						mlx->opening[yc][xc] = obj->specs->sect;
					}
				}
			}
		}
	}
	mlx->obj_i++;
}

void	ft_sect_obj(t_mlx *mlx, int sect)
{
	ft_sect_obj_sort(mlx, sect);
	t_obj *obj = mlx->sect[sect]->obj_list;
	while (obj)
	{
		if (mlx->obj_i >= MAX_VISSPRITES)
			return ;
		ft_draw_sector_obj(mlx, obj, sect);
		obj = obj->next;
	}
}

void	ft_boost_check(t_mlx *mlx)
{
	if (mlx->player->speed_boost)
	{
		mlx->player->speed_curr = time(NULL);
		double diff = difftime(mlx->player->speed_curr, mlx->player->speed_begin);
		mlx->player->speed_diff = SPEED_BOOST_DUR - diff;
		if (diff >= SPEED_BOOST_DUR)
		{
			mlx->player->speed_boost = 0;
			mlx->player->speed = 0.2f;
			mlx->player->revolver->reloading_delay = 3;
			mlx->player->a_rifle->reloading_delay = 3;
		}
	}
	if (mlx->player->hp_boost)
	{
		mlx->player->hp_curr = time(NULL);
		double diff = difftime(mlx->player->hp_curr, mlx->player->hp_begin);
		mlx->player->hp_diff = HP_BOOST_DUR - diff;
		if (diff >= HP_BOOST_DUR)
		{
			mlx->player->hp_boost = 0;
			mlx->player->max_hp = 100;
		}
	}
}

void	ft_collect(t_mlx *mlx, int obj_i, short *check)
{
	if (obj_i == 1)
	{
		mlx->player->a_rifle->ammo_count += 30;
		mlx->player->revolver->ammo_count += 6;
	}
	else if (obj_i == 12)
	{
		mlx->player->a_rifle->ammo_count += 60;
		mlx->player->shotgun->ammo_count += 16;
		mlx->player->revolver->ammo_count += 12;
	}
	else if (obj_i == 13)
		mlx->player->revolver->ammo_count += 12;
	else if (obj_i == 14)
		mlx->player->a_rifle->ammo_count += 60;
	else if (obj_i == 15)
		mlx->player->shotgun->ammo_count += 16;
	else if (obj_i == 16 && !mlx->player->speed_boost)
	{
		mlx->player->speed = 0.3f;
		mlx->player->speed_boost = 1;
		mlx->player->revolver->reloading_delay = 2;
		mlx->player->a_rifle->reloading_delay = 2;
		mlx->player->speed_begin = time(NULL);
	}
	else if (obj_i == 17 && !mlx->player->hp_boost)
	{
		mlx->player->max_hp = 200;
		mlx->player->hp_boost = 1;
		mlx->player->hp_begin = time(NULL);
	}
	else if (obj_i == 18 && mlx->player->hp < mlx->player->max_hp)
	{
		mlx->player->hp += 45;
		mlx->player->hp = (mlx->player->hp > mlx->player->max_hp) ? mlx->player->max_hp : mlx->player->hp;
	}
	else if (obj_i == 19 && mlx->player->hp < mlx->player->max_hp)
	{
		mlx->player->hp += 15;
		mlx->player->hp = (mlx->player->hp > mlx->player->max_hp) ? mlx->player->max_hp : mlx->player->hp;
	}
	else
		*check = 0;
}

void	ft_obj_search(t_mlx *mlx)
{
	if (mlx->sect[mlx->player->sector]->obj_count <= 0)
		return;
	short check = 1;
	t_obj *obj = mlx->sect[mlx->player->sector]->obj_list;
	if (mlx->sect[mlx->player->sector]->obj_count == 1)
	{
		if (mlx->obj_l[obj->specs->obj_i]->is_collectable && ft_overlap(mlx->player->pos->x, mlx->player->pos->x, obj->specs->x - 0.75f, obj->specs->x + 0.75f)
			&& ft_overlap(mlx->player->pos->y, mlx->player->pos->y, obj->specs->y - 0.75f, obj->specs->y + 0.75f) && obj->specs->z == (mlx->player->pos->z - mlx->player->eye_h))
		{
			ft_collect(mlx, obj->specs->obj_i, &check);
			if (check)
			{
				free(obj->specs);
				free(obj);
				mlx->sect[mlx->player->sector]->obj_list = NULL;
				mlx->sect[mlx->player->sector]->obj_count--;
			}
			return;
		}
	}
	while (obj->next)
	{
		if (mlx->obj_l[obj->next->specs->obj_i]->is_collectable && ft_overlap(mlx->player->pos->x, mlx->player->pos->x, obj->next->specs->x - 0.75f, obj->next->specs->x + 0.75f)
			&& ft_overlap(mlx->player->pos->y, mlx->player->pos->y, obj->next->specs->y - 0.75f, obj->next->specs->y + 0.75f) && obj->next->specs->z == (mlx->player->pos->z - mlx->player->eye_h))
		{
			ft_collect(mlx, obj->next->specs->obj_i, &check);
			if (check)
			{
				free(obj->next->specs);
				free(obj->next);
				obj->next = obj->next->next;
				mlx->sect[mlx->player->sector]->obj_count--;
			}
			return;
		}
		obj = obj->next;
	}
}

int		ft_shoot_obj(t_mlx *mlx, double p_dist, int sect)
{
	t_obj *obj = mlx->sect[sect]->obj_list;
	while (obj)
	{
		if (mlx->obj_l[obj->specs->obj_i]->expl == 1 || obj->specs->has_collider)
		{
			if (ft_overlap(obj->specs->x1, obj->specs->x2, W / 2, W / 2) && ft_overlap(obj->specs->y1, obj->specs->y2, H / 2, H / 2) && obj->dist < p_dist)
			{
				if (mlx->obj_l[obj->specs->obj_i]->expl == 1)
				{
					if (obj->specs->obj_i == 3)
						obj->specs->obj_i = 6;
					obj->specs->expl_f = 1;
					if (obj->specs->has_collider)
					{
						int i = -1;
						while (++i < 5)
							free(obj->specs->verts[i]);
						free(obj->specs->verts);
						obj->specs->has_collider = 0;
					}
				}
				return (1);
			}
		}
		obj = obj->next;
	}
	return (0);
}
