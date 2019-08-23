/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:10:17 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/23 20:20:07 by zjeyne-l         ###   ########.fr       */
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
	v0 = (t_vec2*)malloc(sizeof(t_vec2));
	v1 = (t_vec2*)malloc(sizeof(t_vec2));
	while (++i < sector->verts_count)
	{
		v0->x = sector->verts[i + 0]->x;
		v0->y = sector->verts[i + 0]->y;
		v1->x = sector->verts[i + 1]->x;
		v1->y = sector->verts[i + 1]->y;
		if (ft_line_intersect(mlx, p0, p1, v0, v1))
		{
			ft_memdel((void**)&v0);
			ft_memdel((void**)&v1);
			return (i);
		}
	}
	ft_memdel((void**)&v0);
	ft_memdel((void**)&v1);
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

	// printf("\npx %f		py %f		pz %f\n", px, py, pz);
	// printf("dx %f		dy %f\n", dx, dy);

	t_vec2 *p1 = (t_vec2*)malloc(sizeof(t_vec2));

	mlx->shoot_p->x = px;
	mlx->shoot_p->y = py;
	p1->x = dx;
	p1->y = dy;

	t_sector *sector = mlx->sect[mlx->player->sector];
	mlx->now->sector_n = mlx->player->sector;

	int hit = 0;
	while (!hit)
	{
		int s = ft_poly_intersect(mlx, sector, mlx->shoot_p, p1);
		if (s != -1)
		{
			int neighbor = ft_atoi(sector->neighbors[s]);

			double dxx = mlx->shoot_p->x - px;
			double dyy = mlx->shoot_p->y - py;
			double p_dist = sqrtf(dxx * dxx + dyy * dyy);
			double sz = p_dist * tanf(angle_z) + pz;

			double p_sect_f = mlx->sect[mlx->player->sector]->floor;
			double p_sect_c = mlx->sect[mlx->player->sector]->ceiling;

			t_vec3 *pos = (t_vec3*)malloc(sizeof(t_vec3));
			pos->x = mlx->shoot_p->x;
			pos->y = mlx->shoot_p->y;
			pos->z = sz;

			if (neighbor >= 0)
			{
				double n_sect_f = mlx->sect[neighbor]->floor;
				double n_sect_c = mlx->sect[neighbor]->ceiling;

				if (n_sect_f != p_sect_f || n_sect_c != p_sect_c)
				{
					if (sz > p_sect_f && sz < n_sect_f)
					{
						ft_interact_check(mlx, mlx->now->sector_n, s, pos);

						free(p1);
						free(pos);
						return ;
					}
					else if (sz <= p_sect_c && sz >= n_sect_c)
					{
						ft_interact_check(mlx, mlx->now->sector_n, s, pos);

						free(p1);
						free(pos);
						return ;
					}
				}
				free(pos);
				sector = mlx->sect[neighbor];
				mlx->now->sector_n = neighbor;
			}
			else
			{
				ft_interact_check(mlx, mlx->now->sector_n, s, pos);

				free(p1);
				free(pos);
				return ;
			}
		}
		else
		{
			free(p1);
			return;
		}
	}
}

void	ft_shoot(t_mlx *mlx)
{
	double px = mlx->player->pos->x;
	double py = mlx->player->pos->y;
	double pz = mlx->player->pos->z;// + mlx->sect[mlx->player->sector]->floor;
	double angle_xy = atan2f(mlx->player->sin_angle, mlx->player->cos_angle);
	double angle_z = atanf(-mlx->player->yaw);
	double dx = mlx->fire_range * cosf(angle_xy) + px;
	double dy = mlx->fire_range * sinf(angle_xy) + py;

	// printf("\npx %f		py %f		pz %f\n", px, py, pz);
	// printf("dx %f		dy %f\n", dx, dy);

	t_vec2 *p1 = (t_vec2*)malloc(sizeof(t_vec2));

	mlx->shoot_p->x = px;
	mlx->shoot_p->y = py;
	p1->x = dx;
	p1->y = dy;

	t_sector *sector = mlx->sect[mlx->player->sector];
	mlx->now->sector_n = mlx->player->sector;

	int hit = 0;
	while (!hit)
	{
		int s = ft_poly_intersect(mlx, sector, mlx->shoot_p, p1);
		if (s != -1)
		{
			int neighbor = ft_atoi(sector->neighbors[s]);

			double dxx = mlx->shoot_p->x - px;
			double dyy = mlx->shoot_p->y - py;
			double p_dist = sqrtf(dxx * dxx + dyy * dyy);
			double sz = p_dist * tanf(angle_z) + pz;
			// printf("angle_z %f\n", angle_z);
			// printf("sx %f		sy %f		sz %f\n\n", mlx->shoot_p->x, mlx->shoot_p->y, sz);
			double p_sect_f = mlx->sect[mlx->player->sector]->floor;
			double p_sect_c = mlx->sect[mlx->player->sector]->ceiling;

			if (ft_explosive_obj(mlx, p_dist, mlx->now->sector_n))
			{
				// printf("hit canister\n");
				// printf("----------------------------------------------------\n");
				free(p1);
				return ;
			}

			if (sz < p_sect_f)
			{
				// printf("hit floor\n");
				// printf("sect %d\n", mlx->now->sector_n);
				// printf("----------------------------------------------------\n");
				free(p1);
				return ;
			}
			if (sz > p_sect_c)
			{
				// printf("hit ceiling\n");
				// printf("sect %d\n", mlx->now->sector_n);
				// printf("----------------------------------------------------\n");
				free(p1);
				return ;
			}

			t_vec3 *pos = (t_vec3*)malloc(sizeof(t_vec3));
			pos->x = mlx->shoot_p->x;
			pos->y = mlx->shoot_p->y;
			pos->z = sz;

			if (neighbor >= 0)
			{
				double n_sect_f = mlx->sect[neighbor]->floor;
				double n_sect_c = mlx->sect[neighbor]->ceiling;

				if (n_sect_f != p_sect_f || n_sect_c != p_sect_c)
				{
					if (sz > p_sect_f && sz < n_sect_f)
					{
						ft_add_wobj(mlx, pos, mlx->now->sector_n, s);

						// printf("hit lower wall\n");
						// printf("sect %d			s %d\n", mlx->now->sector_n, s);
						// printf("----------------------------------------------------\n");
						free(p1);
						free(pos);
						return ;
					}
					else if (sz <= p_sect_c && sz >= n_sect_c)
					{
						ft_add_wobj(mlx, pos, mlx->now->sector_n, s);

						// printf("hit upper wall\n");
						// printf("sect %d			s %d\n", mlx->now->sector_n, s);
						// printf("----------------------------------------------------\n");
						free(p1);
						free(pos);
						return ;
					}
				}
				free(pos);
				sector = mlx->sect[neighbor];
				mlx->now->sector_n = neighbor;
			}
			else
			{
				ft_add_wobj(mlx, pos, mlx->now->sector_n, s);

				// printf("hit solid wall\n");
				// printf("sect %d			s %d\n", mlx->now->sector_n, s);
				// printf("----------------------------------------------------\n");
				free(p1);
				free(pos);
				return ;
			}
		}
		else
		{
			free(p1);
			return;
		}
	}
}
