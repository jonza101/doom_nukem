/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 15:06:15 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/04 16:57:47 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_move_player(t_mlx *mlx, double dx, double dy)
{
	double px = mlx->player->pos->x;
	double py = mlx->player->pos->y;

	t_sector *sector = mlx->sect[mlx->player->sector];

	int s = -1;
	while (++s < sector->verts_count)
	{
		int neighbor = ft_atoi(sector->neighbors[s]);
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
}

void	ft_collision(t_mlx *mlx)
{
	//	VERTICAL COLLISION
	double eye_h = mlx->crouching ? CROUCH_H : EYE_H;
	mlx->ground = !mlx->falling;
	if (mlx->falling)
	{
		mlx->player->velocity->z -= 0.05f;
		double next_z = mlx->player->pos->z + mlx->player->velocity->z;
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
		double px = mlx->player->pos->x;
		double py = mlx->player->pos->y;
		double dx = mlx->player->velocity->x;
		double dy = mlx->player->velocity->y;
		int stop = 0;

		t_sector *sector = mlx->sect[mlx->player->sector];
		int s = -1;
		while (++s < sector->verts_count)
		{
			if (ft_intersect_box(px, py, px + dx, py + dy,
					sector->verts[s + 0]->x, sector->verts[s + 0]->y,
					sector->verts[s + 1]->x, sector->verts[s + 1]->y)
				&& ft_point_side(px + dx, py + dy,
					sector->verts[s + 0]->x, sector->verts[s + 0]->y,
					sector->verts[s + 1]->x, sector->verts[s + 1]->y) < 0)		//	=
			{
				int neighbor = ft_atoi(sector->neighbors[s]);
				if (neighbor == -1)
				{
					int n, nt, i;
					if (s != sector->verts_count - 1)
						n = ft_atoi(sector->neighbors[s + 1]);
					else
						n = ft_atoi(sector->neighbors[0]);
					if (s != 0)
					{
						nt = ft_atoi(sector->neighbors[s - 1]);
						i = s - 1;
					}
					else
					{
						nt = ft_atoi(sector->neighbors[sector->verts_count - 1]);
						i = sector->verts_count - 1;
					}
					if (n == -1 || nt == -1)
					{
						// if (nt == -1)
						// {
						// 	printf("s %d	i %d\n", s, i);
						// 	printf("s0x %f	s1y %f\ns1x %f	s1y %f\n\n", sector->verts[i + 0]->x, sector->verts[i + 0]->y,
						// 		sector->verts[s + 0]->x, sector->verts[s + 0]->y);
						// }
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
							{
								printf("stop\n");
								stop = 1;
							}
					}
				}
				if (!stop)
				{
					// printf("calc\n");
					double hole_low = 9e9;
					double hole_high = -9e9;
					if (neighbor >= 0)
					{
						hole_low = ft_max(sector->floor, mlx->sect[neighbor]->floor);
						hole_high = ft_min(sector->ceiling, mlx->sect[neighbor]->ceiling);
					}
					if (hole_high < mlx->player->pos->z + 0 ||				//eye_h
						hole_low > mlx->player->pos->z - eye_h + STAIRS_H)
					{
						double xd = sector->verts[s + 1]->x - sector->verts[s + 0]->x;
						double yd = sector->verts[s + 1]->y - sector->verts[s + 0]->y;
						mlx->player->velocity->x = xd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
						mlx->player->velocity->y = yd * (dx * xd + yd * dy) / (xd * xd + yd * yd);
						mlx->moving = 0;
					}
				}
				
				// printf("px %f	py %f\ndx %f	dy %f\ns0x %f	s0y %f\ns1x %f	s1y %f\n\n", px, py, dx, dy, sector->verts[s]->x, sector->verts[s]->y, sector->verts[s + 1]->x, sector->verts[s + 1]->y);
			}
		}
		// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);
		if (!stop)
			ft_move_player(mlx, mlx->player->velocity->x, mlx->player->velocity->y);
		mlx->falling = 1;
	}
}

void	ft_move_calc(t_mlx *mlx)
{
	double move_vec[2] = { 0.0f, 0.0f };
	if (mlx->wsad[0])
	{
		move_vec[0] += mlx->player->cos_angle * 0.2f;
		move_vec[1] += mlx->player->sin_angle * 0.2f;
	}
	if (mlx->wsad[1])
	{
		move_vec[0] -= mlx->player->cos_angle * 0.2f;
		move_vec[1] -= mlx->player->sin_angle * 0.2f;
	}
	if (mlx->wsad[2])
	{
		move_vec[0] += mlx->player->sin_angle * 0.2f;
		move_vec[1] -= mlx->player->cos_angle * 0.2f;
	}
	if (mlx->wsad[3])
	{
		move_vec[0] -= mlx->player->sin_angle * 0.2f;
		move_vec[1] += mlx->player->cos_angle * 0.2f;
	}

	int pushing = mlx->wsad[0] || mlx->wsad[1] || mlx->wsad[2] || mlx->wsad[3];
	// double acceleration = (pushing) ? 0.35f : 0.35f;

	mlx->player->velocity->x = mlx->player->velocity->x * (1 - 0.35f) + move_vec[0] * 0.35f;
	mlx->player->velocity->y = mlx->player->velocity->y * (1 - 0.35f) + move_vec[1] * 0.35f;
	// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);

	if (pushing)
		mlx->moving = 1;
}
