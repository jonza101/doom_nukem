/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobj.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 18:28:03 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/17 18:30:56 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_wobj_specs_calc(t_mlx *mlx, t_sector *sector, int s, int w_count)
{
	int w = -1;
	while (++w < w_count)
	{
		t_vec2 *p0 = (t_vec2*)malloc(sizeof(t_vec2));
		t_vec2 *p1 = (t_vec2*)malloc(sizeof(t_vec2));
		p0->x = mlx->player->pos->x;
		p0->y = mlx->player->pos->y;
		p1->x = mlx->rend_wobj[w]->wobj->pos->x;
		p1->y = mlx->rend_wobj[w]->wobj->pos->y;

		ft_line_intersect(mlx, p0, p1, sector->verts[s + 0], sector->verts[s + 1]);

		double diff_x = 0.0f;
		double diff_y = 0.0f;
		if (sector->verts[s + 0]->y == sector->verts[s + 1]->y && sector->verts[s + 0]->x != sector->verts[s + 1]->x)
			diff_x = (double)mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->abs_w / 2.0f;
		else if (sector->verts[s + 0]->y != sector->verts[s + 1]->y && sector->verts[s + 0]->x == sector->verts[s + 1]->x)
			diff_y = (double)mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->abs_w / 2.0f;
		else
		{
			diff_x = (double)mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->abs_w / 2.0f;
			diff_y = (double)mlx->wobj_l[mlx->rend_wobj[w]->wobj->wobj_i]->wobj_specs->abs_w / 2.0f;
		}
		mlx->rend_wobj[w]->wvx1 = (mlx->shoot_p->x - diff_x) - mlx->player->pos->x;
		mlx->rend_wobj[w]->wvy1 = (mlx->shoot_p->y - diff_y) - mlx->player->pos->y;
		mlx->rend_wobj[w]->wvx2 = (mlx->shoot_p->x + diff_x) - mlx->player->pos->x;
		mlx->rend_wobj[w]->wvy2 = (mlx->shoot_p->y + diff_y) - mlx->player->pos->y;

		free(p0);
		free(p1);

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
	}
}
