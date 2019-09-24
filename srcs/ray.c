/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:10:17 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/16 21:36:02 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_line_intersect(t_mlx *mlx, t_vec2 *p0, t_vec2 *p1, t_vec2 *v0, t_vec2 *v1)
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
	{
		mlx->shoot_p->x = p0->x + (t * s1_x * 1.0001f);
		mlx->shoot_p->y = p0->y + (t * s1_y * 1.0001f);
		return (1);
	}
	return (0);
}

int		ft_poly_intersect(t_mlx *mlx, t_sector *sector, t_vec2 *p0, t_vec2 *p1)
{
	int		i;
	t_vec2	*v0;
	t_vec2	*v1;

	i = -1;
	while (++i < sector->verts_count)
	{
		v0 = sector->verts[i + 0];
		v1 = sector->verts[i + 1];
		if (ft_line_intersect(mlx, p0, p1, v0, v1))
			return (i);
	}
	return (-1);
}

void	ft_interact(t_mlx *mlx)
{
	double px = mlx->player->pos->x;
	double py = mlx->player->pos->y;
	double pz = mlx->player->pos->z;
	double angle_xy = atan2f(mlx->player->sin_angle, mlx->player->cos_angle);
	double angle_z = atanf(-mlx->player->yaw);
	double dx = INTERACT_RANGE * cosf(angle_xy) + px;
	double dy = INTERACT_RANGE * sinf(angle_xy) + py;

	mlx->shoot_p->x = px;
	mlx->shoot_p->y = py;
	mlx->p1->x = dx;
	mlx->p1->y = dy;

	t_sector *sector = mlx->sect[mlx->player->sector];
	mlx->now->sector_n = mlx->player->sector;

	int hit = 0;
	while (!hit)
	{
		int s = ft_poly_intersect(mlx, sector, mlx->shoot_p, mlx->p1);
		if (s != -1)
		{
			int neighbor = (sector->neighbors[s]);

			double dxx = mlx->shoot_p->x - px;
			double dyy = mlx->shoot_p->y - py;
			double p_dist = sqrtf(dxx * dxx + dyy * dyy);
			double sz = p_dist * tanf(angle_z) + pz;

			double p_sect_f = mlx->sect[mlx->player->sector]->floor;
			double p_sect_c = mlx->sect[mlx->player->sector]->ceiling;

			mlx->pos->x = mlx->shoot_p->x;
			mlx->pos->y = mlx->shoot_p->y;
			mlx->pos->z = sz;

			if (neighbor >= 0)
			{
				double n_sect_f = mlx->sect[neighbor]->floor;
				double n_sect_c = mlx->sect[neighbor]->ceiling;

				if (mlx->sect[neighbor]->is_door && !mlx->sect[neighbor]->open && !mlx->sect[neighbor]->close && !mlx->sect[neighbor]->up)
				{
					mlx->sect[neighbor]->close = 0;
					mlx->sect[neighbor]->open = 1;
					mlx->sect[neighbor]->start_time = time(NULL);
					Mix_Volume(17, VOLUME);
					Mix_PlayChannel(17, mlx->snd->chunks->door, 0);
					mlx->activated_doors++;
					return;
				}

				if (n_sect_f != p_sect_f || n_sect_c != p_sect_c)
				{
					if (sz > p_sect_f && sz < n_sect_f)
					{
						ft_interact_check(mlx, mlx->now->sector_n, s, mlx->pos);
						return ;
					}
					else if (sz <= p_sect_c && sz >= n_sect_c)
					{
						ft_interact_check(mlx, mlx->now->sector_n, s, mlx->pos);
						return ;
					}
				}
				sector = mlx->sect[neighbor];
				mlx->now->sector_n = neighbor;
			}
			else
			{
				ft_interact_check(mlx, mlx->now->sector_n, s, mlx->pos);
				return ;
			}
		}
		else
			return;
	}
}

void	ft_shoot(t_mlx *mlx)
{
	double px = mlx->player->pos->x;
	double py = mlx->player->pos->y;
	double pz = mlx->player->pos->z;
	double angle_xy = atan2f(mlx->player->sin_angle, mlx->player->cos_angle);
	double angle_z = atanf(-mlx->player->yaw);
	double dx = mlx->fire_range * cosf(angle_xy) + px;
	double dy = mlx->fire_range * sinf(angle_xy) + py;

	mlx->shoot_p->x = px;
	mlx->shoot_p->y = py;
	mlx->p1->x = dx;
	mlx->p1->y = dy;

	t_sector *sector = mlx->sect[mlx->player->sector];
	mlx->now->sector_n = mlx->player->sector;

	int hit = 0;
	while (!hit)
	{
		int s = ft_poly_intersect(mlx, sector, mlx->shoot_p, mlx->p1);
		if (s != -1)
		{
			int neighbor = (sector->neighbors[s]);

			double dxx = mlx->shoot_p->x - px;
			double dyy = mlx->shoot_p->y - py;
			double p_dist = sqrtf(dxx * dxx + dyy * dyy);
			double sz = p_dist * tanf(angle_z) + pz;
			double p_sect_f = mlx->sect[mlx->player->sector]->floor;
			double p_sect_c = mlx->sect[mlx->player->sector]->ceiling;

			if (ft_shoot_obj(mlx, p_dist, mlx->now->sector_n))
				return ;
			if (sz < p_sect_f)
				return ;
			if (sz > p_sect_c)
				return ;

			mlx->pos->x = mlx->shoot_p->x;
			mlx->pos->y = mlx->shoot_p->y;
			mlx->pos->z = sz;

			if (neighbor >= 0)
			{
				double n_sect_f = mlx->sect[neighbor]->floor;
				double n_sect_c = mlx->sect[neighbor]->ceiling;

				if (n_sect_f != p_sect_f || n_sect_c != p_sect_c)
				{
					if (sz > p_sect_f && sz < n_sect_f)
					{
						ft_add_wobj(mlx, mlx->pos, mlx->now->sector_n, s);
						return ;
					}
					else if (sz <= p_sect_c && sz >= n_sect_c)
					{
						ft_add_wobj(mlx, mlx->pos, mlx->now->sector_n, s);
						return ;
					}
				}
				sector = mlx->sect[neighbor];
				mlx->now->sector_n = neighbor;
			}
			else
			{
				ft_add_wobj(mlx, mlx->pos, mlx->now->sector_n, s);
				return ;
			}
		}
		else
			return;
	}
}
