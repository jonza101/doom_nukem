/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:15 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/13 20:17:42 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_move_player(t_mlx *mlx, float dx, float dy)
{
	float px = mlx->player->pos->x;
	float py = mlx->player->pos->y;

	t_sector *sector = mlx->sect[mlx->player->sector];
	int s = -1;
	while (++s < sector->verts_count)
	{
		int neighbor = ft_atoi(sector->neighbors[s]);
		if (neighbor >= 0
			&& ft_intersect_box(px, py, px + dx, py + dy, sector->verts[s]->x, sector->verts[s]->y, sector->verts[s + 1]->x, sector->verts[s + 1]->y)
			&& ft_point_side(px + dx, py + dy, sector->verts[s]->x, sector->verts[s]->y, sector->verts[s + 1]->x, sector->verts[s + 1]->y) < 0)
			{
				mlx->player->sector = neighbor;
				break ;
			}
	}

	mlx->player->pos->x += dx;
	mlx->player->pos->y += dy;
	mlx->player->sin_angle = sinf(mlx->player->angle);
	mlx->player->cos_angle = cosf(mlx->player->angle);
}

void	ft_collision(t_mlx *mlx)
{
	//	VERTICAL COLLISION
	float eye_h = mlx->crouching ? CROUCH_H : EYE_H;
	mlx->ground = !mlx->falling;
	if (mlx->falling)
	{
		mlx->player->velocity->z -= 0.05f;
		float next_z = mlx->player->pos->z + mlx->player->velocity->z;
		if (mlx->player->velocity->z < 0 && next_z < mlx->sect[mlx->player->sector]->floor + eye_h)
		{
			mlx->player->pos->z = mlx->sect[mlx->player->sector]->floor + eye_h;
			mlx->player->velocity->z = 0;
			mlx->falling = 0;
			mlx->ground = 1;
		}
		else if (mlx->player->velocity->z > 0 && next_z > mlx->sect[mlx->player->sector]->ceiling)
		{
			mlx->player->velocity->z = 0;
			mlx->falling = 1;
		}
		if (mlx->falling)
		{
			mlx->player->pos->z += mlx->player->velocity->z;
			mlx->moving = 1;
		}
	}
	//	HORIZONTAL COLLISION
	if (mlx->moving)
	{
		float px = mlx->player->pos->x;
		float py = mlx->player->pos->y;
		float dx = mlx->player->velocity->x;
		float dy = mlx->player->velocity->y;

		t_sector *sector = mlx->sect[mlx->player->sector];
		int s = -1;
		while (++s < sector->verts_count)
		{
			if (ft_intersect_box(px, py, px + dx, py + dy, sector->verts[s]->x, sector->verts[s]->y, sector->verts[s + 1]->x, sector->verts[s + 1]->y)
				&& ft_point_side(px + dx, py + dy, sector->verts[s]->x, sector->verts[s]->y, sector->verts[s + 1]->x, sector->verts[s + 1]->y) < 0)
				{
					int neighbor = ft_atoi(sector->neighbors[s]);
					float hole_low = neighbor < 0 ? 9e9 : ft_max(sector->floor, mlx->sect[neighbor]->floor);
					float hole_high = neighbor < 0 ? -9e9 : ft_min(sector->ceiling, mlx->sect[neighbor]->ceiling);

					if (hole_high < mlx->player->pos->z + HEAD_MARGIN ||
						hole_low > mlx->player->pos->z - eye_h + STAIRS_H)
						{
							float xd = sector->verts[s + 1]->x - sector->verts[s]->x;
							float yd = sector->verts[s + 1]->y - sector->verts[s]->y;
							dx = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
							dy = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
							mlx->moving = 0;
						}
				}
		}
		ft_move_player(mlx, dx, dy);
		mlx->falling = 1;
	}
}

void	ft_move_calc(t_mlx *mlx)
{
	float move_vec[2] = { 0.0f, 0.0f };
	if (mlx->wsad[0])
	{
		move_vec[0] += mlx->player->cos_angle * 0.5f;
		move_vec[1] += mlx->player->sin_angle * 0.5f;
	}
	if (mlx->wsad[1])
	{
		move_vec[0] -= mlx->player->cos_angle * 0.5f;
		move_vec[1] -= mlx->player->sin_angle * 0.5f;
	}
	if (mlx->wsad[2])
	{
		move_vec[0] += mlx->player->sin_angle * 0.5f;
		move_vec[1] -= mlx->player->cos_angle * 0.5f;
	}
	if (mlx->wsad[3])
	{
		move_vec[0] -= mlx->player->sin_angle * 0.5f;
		move_vec[1] += mlx->player->cos_angle * 0.5f;
	}

	int pushing = mlx->wsad[0] || mlx->wsad[1] || mlx->wsad[2] || mlx->wsad[3];
	float acceleration = 1;//pushing ? 0.4f : 0.5f;

	mlx->player->velocity->x = mlx->player->velocity->x * (1 - acceleration) + move_vec[0] * acceleration;
	mlx->player->velocity->y = mlx->player->velocity->y * (1 - acceleration) + move_vec[1] * acceleration;

	if (pushing)
		mlx->moving = 1;
}
