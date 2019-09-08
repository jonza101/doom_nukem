/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:15 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/08 15:48:39 by adoyle           ###   ########.fr       */
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

		int s = -1;
		while (++s < sector->verts_count)
		{
			if (ft_intersect_box(px, py, px + dx, py + dy,
					sector->verts[s + 0]->x, sector->verts[s + 0]->y,
					sector->verts[s + 1]->x, sector->verts[s + 1]->y)
				&& ft_point_side(px + dx, py + dy,
					sector->verts[s + 0]->x, sector->verts[s + 0]->y,
					sector->verts[s + 1]->x, sector->verts[s + 1]->y) <= 0)
			{
				neighbor = (sector->neighbors[s]);

				int has_trans = ft_trans_find(mlx, mlx->player->sector, s);
				double hole_low = 9e9;
				double hole_high = -9e9;
				if (neighbor >= 0)
				{
					hole_low = ft_max(sector->floor, mlx->sect[neighbor]->floor);
					hole_high = ft_min(sector->ceiling, mlx->sect[neighbor]->ceiling);
				}

				int prev = (s - 1 <= 0) ? ((s > 0) ? sector->verts_count : sector->verts_count - 1) : s - 1;
				int next = (s + 2 >= sector->verts_count) ? ((s + 1 < sector->verts_count) ? 0 : 1) : s + 2;

				if ((ft_intersect_box(px, py, px + dx, py + dy,
						sector->verts[prev]->x, sector->verts[prev]->y,
						sector->verts[s + 0]->x, sector->verts[s + 0]->y)
					|| ft_line_intersect_move(mlx, mlx->p0, mlx->p1, sector->verts[prev], sector->verts[s + 0]))
					&& ft_point_side(px + dx, py + dy,
						sector->verts[prev]->x, sector->verts[prev]->y,
						sector->verts[s + 0]->x, sector->verts[s + 0]->y) <= 0)
				{
					int p_neigh = sector->neighbors[prev % sector->verts_count];
					int p_has_trans = ft_trans_find(mlx, mlx->player->sector, prev);
					double p_hole_low = 9e9;
					double p_hole_high = -9e9;
					if (p_neigh >= 0)
					{
						p_hole_low = ft_max(sector->floor, mlx->sect[p_neigh]->floor);
						p_hole_high = ft_min(sector->ceiling, mlx->sect[p_neigh]->ceiling);
					}
					if ((p_hole_high < mlx->player->pos->z + HEAD_MARGIN || p_hole_low > (mlx->player->pos->z - mlx->player->eye_h) + STAIRS_H || p_has_trans)
							&& (hole_high < mlx->player->pos->z + HEAD_MARGIN || hole_low > (mlx->player->pos->z - mlx->player->eye_h) + STAIRS_H || has_trans))
						stop = 1;
				}
				if ((ft_intersect_box(px, py, px + dx, py + dy,
						sector->verts[s + 1]->x, sector->verts[s + 1]->y,
						sector->verts[next]->x, sector->verts[next]->y)
					|| ft_line_intersect_move(mlx, mlx->p0, mlx->p1, sector->verts[s + 1], sector->verts[next]))
					&& ft_point_side(px + dx, py + dy,
						sector->verts[s + 1]->x, sector->verts[s + 1]->y,
						sector->verts[next]->x, sector->verts[next]->y) <= 0)
				{
					int n_neigh = (s + 1 < sector->verts_count) ? sector->neighbors[s + 1] : sector->neighbors[0];
					int n_has_trans = ft_trans_find(mlx, mlx->player->sector, n_neigh);
					double n_hole_low = 9e9;
					double n_hole_high = -9e9;
					if (n_neigh >= 0)
					{
						n_hole_low = ft_max(sector->floor, mlx->sect[n_neigh]->floor);
						n_hole_high = ft_min(sector->ceiling, mlx->sect[n_neigh]->ceiling);
					}
					if ((n_hole_high < mlx->player->pos->z + HEAD_MARGIN || n_hole_low > (mlx->player->pos->z - mlx->player->eye_h) + STAIRS_H || n_has_trans)
							&& (hole_high < mlx->player->pos->z + HEAD_MARGIN || hole_low > (mlx->player->pos->z - mlx->player->eye_h) + STAIRS_H || has_trans))
						stop = 1;
				}

				if (!stop && (hole_high < (mlx->player->pos->z + HEAD_MARGIN) || hole_low > (mlx->player->pos->z - mlx->player->eye_h) + STAIRS_H || has_trans))
				{
					double xd = sector->verts[s + 1]->x - sector->verts[s + 0]->x;
					double yd = sector->verts[s + 1]->y - sector->verts[s + 0]->y;
					mlx->player->velocity->x = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
					mlx->player->velocity->y = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);

					mlx->moving = 0;
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

		mlx->sky_offset_x -= 20;
	}
	if (mlx->player->right)
	{
		mlx->player->angle += 0.045f;
		mlx->player->sin_angle = sinf(mlx->player->angle);
		mlx->player->cos_angle = cosf(mlx->player->angle);

		mlx->sky_offset_x += 20;
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
