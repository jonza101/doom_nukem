/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:28:03 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/09 19:28:57 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_interact_check(t_mlx *mlx, int sect, int side, t_vec3 *pos)
{
	t_wobj *wobj = mlx->wobj_list;
	while (wobj)
	{
		double down_z = wobj->pos->z - mlx->wobj_l[wobj->wobj_i]->wobj_specs->abs_h / 2.0f - 0.15f;
		double up_z = wobj->pos->z + mlx->wobj_l[wobj->wobj_i]->wobj_specs->abs_h / 2.0f + 0.15f;
		// printf("wx %f		wy %f		wz %f\n", wobj->pos->x, wobj->pos->y, wobj->pos->z);
		// printf("px %f		py %f		pz %f\n", pos->x, pos->y, pos->z);
		// printf("x1 %f		y %f\n", wobj->p1->x, wobj->p1->y);
		// printf("x2 %f		y2 %f\n\n", wobj->p2->x, wobj->p2->y);
		double x1 = ft_min(wobj->p1->x, wobj->p2->x) - 0.15f;
		double x2 = ft_max(wobj->p1->x, wobj->p2->x) + 0.15f;
		double y1 = ft_min(wobj->p1->y, wobj->p2->y) - 0.15f;
		double y2 = ft_max(wobj->p1->y, wobj->p2->y) + 0.15f;
		if (wobj->wobj_i == 8 && wobj->sect == sect && wobj->side == side
				&& pos->x >= x1 && pos->x <= x2
				&& pos->y >= y1 && pos->y <= y2
				&& pos->z >= down_z && pos->z <= up_z)
		{
			wobj->frame = (wobj->frame == mlx->wobj_l[wobj->wobj_i]->anim[0]) ? mlx->wobj_l[wobj->wobj_i]->anim[1] : mlx->wobj_l[wobj->wobj_i]->anim[0];
			mlx->sect[sect]->light = !mlx->sect[sect]->light;
			return;
		}
		wobj = wobj->next;
	}
}

void	ft_add_first_wobj(t_mlx *mlx, t_vec3 *pos, int sect, int side)
{
	mlx->wobj_list = (t_wobj*)malloc(sizeof(t_wobj));
	mlx->wobj_list->sect = sect;
	mlx->wobj_list->side = side;

	mlx->wobj_list->pos = (t_vec3*)malloc(sizeof(t_vec3));
	mlx->wobj_list->pos->x = pos->x;
	mlx->wobj_list->pos->y = pos->y;
	mlx->wobj_list->pos->z = pos->z;
	mlx->wobj_list->wobj_i = 4;
	mlx->wobj_list->rendered = 0;

	mlx->wobj_list->del = 0;
	mlx->wobj_list->anim_i = 0;
	mlx->wobj_list->frame = mlx->wobj_l[mlx->wobj_list->wobj_i]->anim[0];

	mlx->wobj_list->p1 = (t_vec2*)malloc(sizeof(t_vec2));
	mlx->wobj_list->p2 = (t_vec2*)malloc(sizeof(t_vec2));

	double dx1 = mlx->sect[sect]->verts[side + 0]->x - mlx->wobj_list->pos->x;
	double dy1 = mlx->sect[sect]->verts[side + 0]->y - mlx->wobj_list->pos->y;
	double dx2 = mlx->wobj_list->pos->x - mlx->sect[sect]->verts[side + 1]->x;
	double dy2 = mlx->wobj_list->pos->y - mlx->sect[sect]->verts[side + 1]->y;
	double dist1 = sqrtf(dx1 * dx1 + dy1 * dy1);
	double dist2 = sqrtf(dx2 * dx2 + dy2 * dy2);

	double half_w = (double)mlx->wobj_l[mlx->wobj_list->wobj_i]->wobj_specs->abs_w / 2.0f;

	mlx->wobj_list->p1->x = mlx->wobj_list->pos->x - ((half_w * (mlx->wobj_list->pos->x - mlx->sect[sect]->verts[side + 0]->x)) / dist1);
	mlx->wobj_list->p1->y = mlx->wobj_list->pos->y - ((half_w * (mlx->wobj_list->pos->y - mlx->sect[sect]->verts[side + 0]->y)) / dist1);

	mlx->wobj_list->p2->x = mlx->wobj_list->pos->x - ((half_w * (mlx->wobj_list->pos->x - mlx->sect[sect]->verts[side + 1]->x)) / dist2);
	mlx->wobj_list->p2->y = mlx->wobj_list->pos->y - ((half_w * (mlx->wobj_list->pos->y - mlx->sect[sect]->verts[side + 1]->y)) / dist2);

	mlx->wobj_list->next = NULL;
	mlx->last_wobj = mlx->wobj_list;
	mlx->wobj_count++;
}

void	ft_add_wobj(t_mlx *mlx, t_vec3 *pos, int sect, int side)
{
	if (mlx->wobj_count <= 0)
	{
		ft_add_first_wobj(mlx, pos, sect, side);
		return;
	}
	if ((mlx->sect_wobj[sect]->side[side] >= MAX_WSPRITES_ON_WALL) || (mlx->last_wobj->pos->x == pos->x && mlx->last_wobj->pos->y == pos->y && mlx->last_wobj->pos->z == pos->z))
		return ;

	mlx->last_wobj->next = (t_wobj*)malloc(sizeof(t_wobj));
	mlx->last_wobj->next->sect = sect;
	mlx->last_wobj->next->side = side;
	mlx->last_wobj->next->pos = (t_vec3*)malloc(sizeof(t_vec3));
	mlx->last_wobj->next->pos->x = pos->x;
	mlx->last_wobj->next->pos->y = pos->y;
	mlx->last_wobj->next->pos->z = pos->z;
	mlx->last_wobj->next->wobj_i = 4;
	mlx->last_wobj->next->rendered = 0;

	mlx->last_wobj->next->del = 0;
	mlx->last_wobj->next->anim_i = 0;
	mlx->last_wobj->next->frame = mlx->wobj_l[mlx->last_wobj->next->wobj_i]->anim[0];

	mlx->last_wobj->next->p1 = (t_vec2*)malloc(sizeof(t_vec2));
	mlx->last_wobj->next->p2 = (t_vec2*)malloc(sizeof(t_vec2));

	double dx1 = mlx->sect[sect]->verts[side + 0]->x - mlx->last_wobj->next->pos->x;
	double dy1 = mlx->sect[sect]->verts[side + 0]->y - mlx->last_wobj->next->pos->y;
	double dx2 = mlx->last_wobj->next->pos->x - mlx->sect[sect]->verts[side + 1]->x;
	double dy2 = mlx->last_wobj->next->pos->y - mlx->sect[sect]->verts[side + 1]->y;
	double dist1 = sqrtf(dx1 * dx1 + dy1 * dy1);
	double dist2 = sqrtf(dx2 * dx2 + dy2 * dy2);

	double half_w = (double)mlx->wobj_l[mlx->last_wobj->next->wobj_i]->wobj_specs->abs_w / 2.0f;

	mlx->last_wobj->next->p1->x = mlx->last_wobj->next->pos->x - ((half_w * (mlx->last_wobj->next->pos->x - mlx->sect[sect]->verts[side + 0]->x)) / dist1);
	mlx->last_wobj->next->p1->y = mlx->last_wobj->next->pos->y - ((half_w * (mlx->last_wobj->next->pos->y - mlx->sect[sect]->verts[side + 0]->y)) / dist1);

	mlx->last_wobj->next->p2->x = mlx->last_wobj->next->pos->x - ((half_w * (mlx->last_wobj->next->pos->x - mlx->sect[sect]->verts[side + 1]->x)) / dist2);
	mlx->last_wobj->next->p2->y = mlx->last_wobj->next->pos->y - ((half_w * (mlx->last_wobj->next->pos->y - mlx->sect[sect]->verts[side + 1]->y)) / dist2);

	mlx->last_wobj = mlx->last_wobj->next;
	mlx->last_wobj->next = NULL;
	mlx->wobj_count++;
}

void	ft_wobj_pos_correct(t_mlx *mlx)
{
	t_wobj *wobj = mlx->wobj_list;
	while (wobj)
	{
		double ang = atan2f(wobj->pos->y - mlx->player->pos->y, wobj->pos->x - mlx->player->pos->x);

		t_vec2 *v1 = mlx->sect[wobj->sect]->verts[wobj->side];
		t_vec2 *v2 = mlx->sect[wobj->sect]->verts[wobj->side + 1];

		double px = v2->x - v1->x;
		double py = v2->y - v1->y;
		double dxy = px * px + py * py;
		double u = ((wobj->pos->x - v1->x) * px + (wobj->pos->y - v1->y) * py) / dxy;
		wobj->pos->x = v1->x + u * px;
		wobj->pos->y = v1->y + u * py;

		double dx1 = mlx->sect[wobj->sect]->verts[wobj->side + 0]->x - wobj->pos->x;
		double dy1 = mlx->sect[wobj->sect]->verts[wobj->side + 0]->y - wobj->pos->y;
		double dx2 = wobj->pos->x - mlx->sect[wobj->sect]->verts[wobj->side + 1]->x;
		double dy2 = wobj->pos->y - mlx->sect[wobj->sect]->verts[wobj->side + 1]->y;
		double dist1 = sqrtf(dx1 * dx1 + dy1 * dy1);
		double dist2 = sqrtf(dx2 * dx2 + dy2 * dy2);

		double half_w = (double)mlx->wobj_l[wobj->wobj_i]->wobj_specs->abs_w / 2.0f;

		wobj->p1->x = wobj->pos->x - ((half_w * (wobj->pos->x - mlx->sect[wobj->sect]->verts[wobj->side + 0]->x)) / dist1);
		wobj->p1->y = wobj->pos->y - ((half_w * (wobj->pos->y - mlx->sect[wobj->sect]->verts[wobj->side + 0]->y)) / dist1);

		wobj->p2->x = wobj->pos->x - ((half_w * (wobj->pos->x - mlx->sect[wobj->sect]->verts[wobj->side + 1]->x)) / dist2);
		wobj->p2->y = wobj->pos->y - ((half_w * (wobj->pos->y - mlx->sect[wobj->sect]->verts[wobj->side + 1]->y)) / dist2);

		wobj = wobj->next;
	}
}

void	ft_wobj_specs_calc(t_mlx *mlx, t_sector *sector, int s, int w_count)
{
	int w = -1;
	while (++w < w_count)
	{
		mlx->rend_wobj[w]->wvx1 = (mlx->rend_wobj[w]->wobj->p1->x) - mlx->player->pos->x;
		mlx->rend_wobj[w]->wvy1 = (mlx->rend_wobj[w]->wobj->p1->y) - mlx->player->pos->y;
		mlx->rend_wobj[w]->wvx2 = (mlx->rend_wobj[w]->wobj->p2->x) - mlx->player->pos->x;
		mlx->rend_wobj[w]->wvy2 = (mlx->rend_wobj[w]->wobj->p2->y) - mlx->player->pos->y;

		double p_cos = mlx->player->cos_angle;
		double p_sin = mlx->player->sin_angle;

		mlx->rend_wobj[w]->wtx1 = mlx->rend_wobj[w]->wvx1 * p_sin - mlx->rend_wobj[w]->wvy1 * p_cos;
		mlx->rend_wobj[w]->wtz1 = mlx->rend_wobj[w]->wvx1 * p_cos + mlx->rend_wobj[w]->wvy1 * p_sin;
		mlx->rend_wobj[w]->wtx2 = mlx->rend_wobj[w]->wvx2 * p_sin - mlx->rend_wobj[w]->wvy2 * p_cos;
		mlx->rend_wobj[w]->wtz2 = mlx->rend_wobj[w]->wvx2 * p_cos + mlx->rend_wobj[w]->wvy2 * p_sin;

		if (mlx->rend_wobj[w]->wtz1 <= 0 && mlx->rend_wobj[w]->wtz2 <= 0)
		{
			mlx->rend_wobj[w]->w_flag = 0;
			continue;
		}

		if (mlx->rend_wobj[w]->w_flag && (mlx->rend_wobj[w]->wtz1 <= 0 || mlx->rend_wobj[w]->wtz2 <= 0))
		{
			double near_z = 1e-4f;
			double far_z = 5.0f;
			double nearside = 1e-5f;
			double farside = 20.0f;

			t_vec2 *wi1 = (t_vec2*)malloc(sizeof(t_vec2));
			t_vec2 *wi2 = (t_vec2*)malloc(sizeof(t_vec2));

			ft_intersect(wi1, mlx->rend_wobj[w]->wtx1, mlx->rend_wobj[w]->wtz1, mlx->rend_wobj[w]->wtx2, mlx->rend_wobj[w]->wtz2, -nearside, near_z, -farside, far_z);
			ft_intersect(wi2, mlx->rend_wobj[w]->wtx1, mlx->rend_wobj[w]->wtz1, mlx->rend_wobj[w]->wtx2, mlx->rend_wobj[w]->wtz2, nearside, near_z, farside, far_z);

			t_vec2 *worg1 = (t_vec2*)malloc(sizeof(t_vec2));
			t_vec2 *worg2 = (t_vec2*)malloc(sizeof(t_vec2));
			worg1->x = mlx->rend_wobj[w]->wtx1;
			worg1->y = mlx->rend_wobj[w]->wtz1;
			worg2->x = mlx->rend_wobj[w]->wtx2;
			worg2->y = mlx->rend_wobj[w]->wtz2;

			if (mlx->rend_wobj[w]->wtz1 < near_z)
			{
				if (wi1->y > 0)
				{
					mlx->rend_wobj[w]->wtx1 = wi1->x;
					mlx->rend_wobj[w]->wtz1 = wi1->y;
				}
				else
				{
					mlx->rend_wobj[w]->wtx1 = wi2->x;
					mlx->rend_wobj[w]->wtz1 = wi2->y;
				}
			}
			if (mlx->rend_wobj[w]->wtz2 < near_z)
			{
				if (wi1->y > 0)
				{
					mlx->rend_wobj[w]->wtx2 = wi1->x;
					mlx->rend_wobj[w]->wtz2 = wi1->y;
				}
				else
				{
					mlx->rend_wobj[w]->wtx2 = wi2->x;
					mlx->rend_wobj[w]->wtz2 = wi2->y;
				}
			}

			if (fabs(mlx->rend_wobj[w]->wtx2 - mlx->rend_wobj[w]->wtx1) > fabs(mlx->rend_wobj[w]->wtz2 - mlx->rend_wobj[w]->wtz1))
			{
				mlx->rend_wobj[w]->wu0 = (mlx->rend_wobj[w]->wtx1 - worg1->x) * mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->u1 / (worg2->x - worg1->x);
				mlx->rend_wobj[w]->wu1 = (mlx->rend_wobj[w]->wtx2 - worg1->x) * mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->u1 / (worg2->x - worg1->x);
			}
			else
			{
				mlx->rend_wobj[w]->wu0 = (mlx->rend_wobj[w]->wtz1 - worg1->y) * mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->u1 / (worg2->y - worg1->y);
				mlx->rend_wobj[w]->wu1 = (mlx->rend_wobj[w]->wtz2 - worg1->y) * mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->u1 / (worg2->y - worg1->y);
			}

			free(wi1);
			free(wi2);

			free(worg1);
			free(worg2);
		}

		if (mlx->rend_wobj[w]->w_flag)
		{
			mlx->rend_wobj[w]->wxscale1 = (W * FOV_H) / mlx->rend_wobj[w]->wtz1;
			mlx->rend_wobj[w]->wyscale1 = (H * FOV_V) / mlx->rend_wobj[w]->wtz1;
			mlx->rend_wobj[w]->wx1 = W / 2 + (int)(-mlx->rend_wobj[w]->wtx1 * mlx->rend_wobj[w]->wxscale1);
			mlx->rend_wobj[w]->wxscale2 = (W * FOV_H) / mlx->rend_wobj[w]->wtz2;
			mlx->rend_wobj[w]->wyscale2 = (H * FOV_V) / mlx->rend_wobj[w]->wtz2;
			mlx->rend_wobj[w]->wx2 = W / 2 + (int)(-mlx->rend_wobj[w]->wtx2 * mlx->rend_wobj[w]->wxscale2);

			if (mlx->rend_wobj[w]->wx1 == mlx->rend_wobj[w]->wx2 || mlx->rend_wobj[w]->wx2 < mlx->now->sx1 || mlx->rend_wobj[w]->wx1 > mlx->now->sx2)
			{
				mlx->rend_wobj[w]->w_flag = 0;
				continue;
			}
		}

		if (mlx->rend_wobj[w]->w_flag)
		{
			double diff_z = (double)mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->abs_h / 2.0f;
			mlx->rend_wobj[w]->wyceil = (mlx->rend_wobj[w]->wobj->pos->z + diff_z) - mlx->player->pos->z;
			mlx->rend_wobj[w]->wyfloor = (mlx->rend_wobj[w]->wobj->pos->z - diff_z) - mlx->player->pos->z;
			if (mlx->rend_wobj[w]->wobj->pos->z + diff_z > sector->ceiling || mlx->rend_wobj[w]->wobj->pos->z - diff_z < sector->floor)
			{
				mlx->rend_wobj[w]->w_flag = 0;
				continue;
			}
		}

		if (mlx->rend_wobj[w]->w_flag)
		{
			mlx->rend_wobj[w]->wy1a = H / 2 + (int)(-(mlx->rend_wobj[w]->wyceil + mlx->rend_wobj[w]->wtz1 * mlx->player->yaw) * mlx->rend_wobj[w]->wyscale1);
			mlx->rend_wobj[w]->wy1b = H / 2 + (int)(-(mlx->rend_wobj[w]->wyfloor + mlx->rend_wobj[w]->wtz1 * mlx->player->yaw) * mlx->rend_wobj[w]->wyscale1);
			mlx->rend_wobj[w]->wy2a = H / 2 + (int)(-(mlx->rend_wobj[w]->wyceil + mlx->rend_wobj[w]->wtz2 * mlx->player->yaw) * mlx->rend_wobj[w]->wyscale2);
			mlx->rend_wobj[w]->wy2b = H / 2 + (int)(-(mlx->rend_wobj[w]->wyfloor + mlx->rend_wobj[w]->wtz2 * mlx->player->yaw) * mlx->rend_wobj[w]->wyscale2);

			mlx->rend_wobj[w]->wbeginx = ft_max(mlx->rend_wobj[w]->wx1, mlx->now->sx1);
			mlx->rend_wobj[w]->wendx = ft_min(mlx->rend_wobj[w]->wx2, mlx->now->sx2);

			if (mlx->rend_wobj[w]->wbeginx > mlx->rend_wobj[w]->wendx)
			{
				int temp = mlx->rend_wobj[w]->wbeginx;
				mlx->rend_wobj[w]->wbeginx = mlx->rend_wobj[w]->wendx;
				mlx->rend_wobj[w]->wendx = temp;
			}
		}

		if (mlx->rend_wobj[w]->w_flag)
		{
			ft_scaler_init(mlx->rend_wobj[w]->wya_int, mlx->rend_wobj[w]->wx1, mlx->rend_wobj[w]->wbeginx, mlx->rend_wobj[w]->wx2, mlx->rend_wobj[w]->wy1a, mlx->rend_wobj[w]->wy2a);
			ft_scaler_init(mlx->rend_wobj[w]->wyb_int, mlx->rend_wobj[w]->wx1, mlx->rend_wobj[w]->wbeginx, mlx->rend_wobj[w]->wx2, mlx->rend_wobj[w]->wy1b, mlx->rend_wobj[w]->wy2b);
		}

		if (mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->anim_n > 1 && mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->is_switcher == 0)
			ft_wobj_anim(mlx, mlx->rend_wobj[w]->wobj);
	}
}
