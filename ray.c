/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 17:10:17 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/12 18:47:49 by zjeyne-l         ###   ########.fr       */
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
		mlx->shoot_p->x = p0->x + (t * s1_x * 1.01f);
		mlx->shoot_p->y = p0->y + (t * s1_y * 1.01f);
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

void	ft_shoot(t_mlx *mlx)
{
	double px = mlx->player->pos->x;
	double py = mlx->player->pos->y;
	double angle = atan2f(mlx->player->sin_angle, mlx->player->cos_angle);
	double dx = FIRE_RANGE * cosf(angle) + px;
	double dy = FIRE_RANGE * sinf(angle) + py;

	printf("px %f		py %f\n", px, py);
	printf("dx %f		dy %f\n", dx, dy);

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
			if (neighbor >= 0)
			{
				sector = mlx->sect[neighbor];
				mlx->now->sector_n = neighbor;
				// printf("sx %f		sy %f\n\n", mlx->shoot_p->x, mlx->shoot_p->y);
			}
			else
			{
				printf("hit\n");
				printf("sect %d			s %d\n\n", mlx->now->sector_n, s);
				hit = 1;
			}
		}
	}
	free(p1);
}
