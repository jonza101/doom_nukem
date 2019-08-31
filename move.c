/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:15 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/31 21:13:31 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_trans_find(t_mlx *mlx, int sect, int s)
{
	if (mlx->trans_count <= 0)
		return (0);
	t_trans *trans = mlx->trans_list;
	while (trans)
	{
		if (trans->sect == sect && trans->side == s)
			return (1);
		trans = trans->next;
	}
	return (0);
}

int		ft_line_intersect_move(t_mlx *mlx, t_vec2 *p0, t_vec2 *p1, t_vec2 *v0, t_vec2 *v1)
{
	double	s1_x;
	double	s1_y;
	double	s2_x;
	double	s2_y;

	s1_x = p1->x - p0->x;
	s1_y = p1->y - p0->y;
	s2_x = v1->x - v0->x;
	s2_y = v1->y - v0->y;

	double 	s;
	double	t;

	s = (-s1_y * (p0->x - v0->x) + s1_x * (p0->y - v0->y)) / (-s2_x * s1_y + s1_x * s2_y);
	t = (s2_x * (p0->y - v0->y) - s2_y * (p0->x - v0->x)) / (-s2_x * s1_y + s1_x * s2_y);

	if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
		return (1);
	return (0);
}

void	ft_move_player(t_mlx *mlx, double dx, double dy)
{
	double px = mlx->player->pos->x;
	double py = mlx->player->pos->y;

	t_sector *sector = mlx->sect[mlx->player->sector];

	int s = -1;
	while (++s < sector->verts_count)
	{
		int neighbor = (sector->neighbors[s]);
		if (neighbor >= 0
			&& ft_intersect_box(px, py, px + dx, py + dy,
				sector->verts[s + 0]->x, sector->verts[s + 0]->y,
				sector->verts[s + 1]->x, sector->verts[s + 1]->y)
			&& ft_point_side(px + dx, py + dy,
				sector->verts[s + 0]->x, sector->verts[s + 0]->y,
				sector->verts[s + 1]->x, sector->verts[s + 1]->y) < 0)
			{
				mlx->player->sector = neighbor;
				break ;
			}
	}
	mlx->player->sin_angle = sinf(mlx->player->angle);
	mlx->player->cos_angle = cosf(mlx->player->angle);
	mlx->player->pos->x += dx;
	mlx->player->pos->y += dy;

	ft_obj_search(mlx);
}

int		ft_inter(t_vec2 *v1, t_vec2 *v2, t_vec2 *p)
{
	if (((v1->y >= p->y && v2->y < p->y) || (v1->y < p->y && v2->y >= p->y)) && (p->x < (v2->x - v1->x) * (p->y - v1->y) / (v2->y - v1->y) + v1->x))
		return (1);
	return (0);
}

int		ft_poly_col(t_sector *sect, t_vec2 *p)
{
	int col = 0;
	int s = -1;
	while (++s < sect->verts_count)
	{
		t_vec2 *vc = sect->verts[s + 0];
		t_vec2 *vn = sect->verts[s + 1];
		if (((vc->y >= p->y && vn->y < p->y) || (vc->y < p->y && vn->y >= p->y)) && (p->x < (vn->x - vc->x) * (p->y - vc->y) / (vn->y - vc->y) + vc->x))
			col = !col;
	}
	printf("collision %d\n", col);
	return (col);
}

void	ft_collision(t_mlx *mlx)
{
	//	VERTICAL COLLISION
	mlx->player->eye_h = mlx->crouching ? CROUCH_H : EYE_H;
	mlx->ground = !mlx->falling;
	if (mlx->falling)
	{
		if (!mlx->player->jetpack)
			mlx->player->velocity->z -= 0.05f;
		double next_z = mlx->player->pos->z + mlx->player->velocity->z;
		if (mlx->player->velocity->z < 0 && next_z < mlx->sect[mlx->player->sector]->floor + mlx->player->eye_h)
		{
			mlx->player->pos->z = mlx->sect[mlx->player->sector]->floor + mlx->player->eye_h;
			mlx->player->velocity->z = 0;
			mlx->falling = 0;
			mlx->ground = 1;
		}
		else if (mlx->player->velocity->z > 0 && next_z > mlx->sect[mlx->player->sector]->ceiling)
		{
			mlx->player->velocity->z = 0;
			mlx->falling = 1;
		}
		if (mlx->falling && !mlx->player->jetpack)
		{
			mlx->player->pos->z += mlx->player->velocity->z;
			mlx->moving = 1;
		}
		if (mlx->falling && mlx->player->jetpack)
		{
			mlx->player->pos->z += mlx->player->velocity->z;
			mlx->player->velocity->z = 0.0f;
			mlx->moving = 1;
		}
	}

	//	HORIZONTAL COLLISION
	if (mlx->moving)
	{
		double px = mlx->player->pos->x;
		double py = mlx->player->pos->y;
		double dx = mlx->player->velocity->x;
		double dy = mlx->player->velocity->y;
		int stop = 0;
		int neighbor;

		t_sector *sector = mlx->sect[mlx->player->sector];

		mlx->p0->x = px;
		mlx->p0->y = py;
		mlx->p1->x = px + dx;
		mlx->p1->y = py + dy;

		t_obj *obj = sector->obj_list;
		while (obj && obj->specs->z == (mlx->player->pos->z - mlx->player->eye_h))
		{
			if (obj->specs->has_collider)
			{
				int inters = 0;
				int v = -1;
				while (++v < 4)
				{
					if (ft_line_intersect_move(mlx, mlx->p0, mlx->p1, obj->specs->verts[v + 0], obj->specs->verts[v + 1])
							&& ft_point_side(px + dx, py + dy,
								obj->specs->verts[v + 0]->x, obj->specs->verts[v + 0]->y,
								obj->specs->verts[v + 1]->x, obj->specs->verts[v + 1]->y) >= 0)
					{
						double oxd = obj->specs->verts[v + 1]->x - obj->specs->verts[v + 0]->x;
						double oyd = obj->specs->verts[v + 1]->y - obj->specs->verts[v + 0]->y;
						mlx->player->velocity->x = oxd * (dx * oxd + oyd * dy) / (oxd * oxd + oyd * oyd);
						mlx->player->velocity->y = oyd * (dx * oxd + oyd * dy) / (oxd * oxd + oyd * oyd);
						mlx->moving = 0;
					}
				}
			}
			obj = obj->next;
		}

		// ft_poly_col(sector, mlx->p1);

		int s = -1;
		while (++s < sector->verts_count)
		{
			if (ft_intersect_box(px, py, px + dx, py + dy,
					sector->verts[s + 0]->x, sector->verts[s + 0]->y,
					sector->verts[s + 1]->x, sector->verts[s + 1]->y)
				&& ft_point_side(px + dx, py + dy,
					sector->verts[s + 0]->x, sector->verts[s + 0]->y,
					sector->verts[s + 1]->x, sector->verts[s + 1]->y) < 0)
			{
				neighbor = (sector->neighbors[s]);
				//	!!!
				if (neighbor == -1)
				{
					int n, nt, i;
					if (s != sector->verts_count - 1)
						n = (sector->neighbors[s + 1]);
					else
						n = (sector->neighbors[0]);
					if (s != 0)
					{
						nt = (sector->neighbors[s - 1]);
						i = s - 1;
					}
					else
					{
						nt = (sector->neighbors[sector->verts_count - 1]);
						i = sector->verts_count - 1;
					}
					if (n == -1 || nt == -1)
					{
						if ((n == -1 &&
								ft_intersect_box(px, py, px + dx, py + dy,
								sector->verts[(s + 1) % sector->verts_count]->x, sector->verts[(s + 1) % sector->verts_count]->y,
								sector->verts[(s + 2) % sector->verts_count]->x, sector->verts[(s + 2) % sector->verts_count]->y)
							&& ft_point_side(px + dx, py + dy,
								sector->verts[(s + 1) % sector->verts_count]->x, sector->verts[(s + 1) % sector->verts_count]->y,
								sector->verts[(s + 2) % sector->verts_count]->x, sector->verts[(s + 2) % sector->verts_count]->y) < 0)
							|| (nt == -1 &&
								ft_intersect_box(px, py, px + dx, py + dy,
								sector->verts[i + 0]->x, sector->verts[i + 0]->y,
								sector->verts[s + 0]->x, sector->verts[s + 0]->y)
							&& ft_point_side(px + dx, py + dy,
								sector->verts[i + 0]->x, sector->verts[i + 0]->y,
								sector->verts[s + 0]->x, sector->verts[s + 0]->y) < 0))
							stop = 1;
					}
				}
				//	!!!
				if (!stop)
				{
					int has_trans = ft_trans_find(mlx, mlx->player->sector, s);
					double hole_low = 9e9;
					double hole_high = -9e9;
					if (neighbor >= 0)
					{
						hole_low = ft_max(sector->floor, mlx->sect[neighbor]->floor);
						hole_high = ft_min(sector->ceiling, mlx->sect[neighbor]->ceiling);
					}
					if (mlx->player->eye_h > (hole_high - hole_low) || hole_low > (mlx->player->pos->z - mlx->player->eye_h) + STAIRS_H || has_trans)
					{
						double xd = sector->verts[s + 1]->x - sector->verts[s + 0]->x;
						double yd = sector->verts[s + 1]->y - sector->verts[s + 0]->y;
						mlx->player->velocity->x = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
						mlx->player->velocity->y = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);

						mlx->moving = 0;
					}
				}
			}
		}

		if (!stop)
			ft_move_player(mlx, mlx->player->velocity->x, mlx->player->velocity->y);
		mlx->falling = 1;
	}
}

void	ft_player_view(t_mlx *mlx)
{	
	if (mlx->player->left)
	{
		mlx->player->angle -= 0.045f;
		mlx->player->sin_angle = sinf(mlx->player->angle);
		mlx->player->cos_angle = cosf(mlx->player->angle);

		mlx->sky_offset_x -= 18;
	}
	if (mlx->player->right)
	{
		mlx->player->angle += 0.045f;
		mlx->player->sin_angle = sinf(mlx->player->angle);
		mlx->player->cos_angle = cosf(mlx->player->angle);

		mlx->sky_offset_x += 18;
	}
	if (mlx->player->up)
	{
		mlx->player->yaw -= 0.1f;
		if (mlx->player->yaw > -5.0f)
			mlx->sky_offset_y -= 14;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -5, 5);
	}
	if (mlx->player->down)
	{
		mlx->player->yaw += 0.1f;
		if (mlx->player->yaw < 5.0f)
			mlx->sky_offset_y += 14;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -5, 5);
	}
}

void	ft_move_calc(t_mlx *mlx)
{
	double move_vec[2] = { 0.0f, 0.0f };
	if (mlx->player->wsad[0])
	{
		move_vec[0] += mlx->player->cos_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
		move_vec[1] += mlx->player->sin_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
	}
	if (mlx->player->wsad[1])
	{
		move_vec[0] -= mlx->player->cos_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
		move_vec[1] -= mlx->player->sin_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
	}
	if (mlx->player->wsad[2])
	{
		move_vec[0] += mlx->player->sin_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
		move_vec[1] -= mlx->player->cos_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
	}
	if (mlx->player->wsad[3])
	{
		move_vec[0] -= mlx->player->sin_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
		move_vec[1] += mlx->player->cos_angle * (mlx->player->speed + 0.1f * mlx->player->shift);
	}

	int pushing = mlx->player->wsad[0] || mlx->player->wsad[1] || mlx->player->wsad[2] || mlx->player->wsad[3];

	mlx->player->velocity->x = mlx->player->velocity->x * (1 - 0.35f) + move_vec[0] * 0.35f;
	mlx->player->velocity->y = mlx->player->velocity->y * (1 - 0.35f) + move_vec[1] * 0.35f;

	if (pushing)
		mlx->moving = 1;

	if (mlx->player->jump && mlx->ground && !mlx->crouching && !mlx->player->jetpack)
	{
		mlx->player->velocity->z += JUMP_H;
		mlx->falling = 1;
	}

	if (mlx->player->j_up && mlx->player->jetpack)
		mlx->player->velocity->z += 0.25f;
	if (mlx->player->j_down && mlx->player->jetpack)
		mlx->player->velocity->z -= 0.25f;
}
