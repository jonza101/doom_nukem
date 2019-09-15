/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 15:21:01 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/15 18:44:59 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_ival_check(char *val)
{
	int neg = 0;
	int i = -1;
	while (val[++i])
	{
		if (val[i] == '-')
			neg++;
		else if (val[i] < '0' || val[i] > '9')
			return (0);
	}
	if (neg > 1)
		return (0);
	return (1);
}

int		ft_fval_check(char *val)
{
	int dot = 0;
	int neg = 0;
	int i = -1;
	while (val[++i])
	{
		if (val[i] == '.')
			dot++;
		else if (val[i] == '-')
			neg++;
		else if (val[i] < '0' || val[i] > '9')
			return (0);
	}
	if (dot > 1 || neg > 1)
		return (0);
	return (1);
}

int		ft_sect_convex_check(t_sector *sect)
{
	double last_dot;
	double dot;
	int s = -1;
	while (++s < sect->verts_count)
	{
		int next = (s + 2 >= sect->verts_count) ? ((s + 1 < sect->verts_count) ? 0 : 1) : s + 2;

		double dx1 = sect->verts[s + 1]->x - sect->verts[s + 0]->x;
		double dy1 = sect->verts[s + 1]->y - sect->verts[s + 0]->y;
		double dx2 = sect->verts[next]->x - sect->verts[s + 1]->x;
		double dy2 = sect->verts[next]->y - sect->verts[s + 1]->y;

		dot = dx1 * dy2 - dy1 * dx2;

		if (s > 0)
		{
			if (!((dot < 0 && last_dot < 0) || (dot > 0 && last_dot > 0)))
				return (0);
		}
		last_dot = dot;
	}
	return (1);
}

int		ft_point_inside_check(t_sector *sect, t_vec2 *p0, t_vec2 *p1)
{
	int intersect = 0;
	int s = -1;
	while (++s < sect->verts_count)
	{
		if (ft_line_intersect_(p0, p1, sect->verts[s + 0], sect->verts[s + 1]))
			intersect++;
	}
	if (intersect % 2 == 1)
		return (1);
	return (0);
}

void	ft_validate_map(t_mlx *mlx)
{
	(!(mlx->p0 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	(!(mlx->p1 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	int s = -1;
	while (++s < mlx->num_sec)
	{
		if (!ft_sect_convex_check(mlx->sect[s]))
			ft_sect_error(s);

		int o = 0;
		t_obj *obj = mlx->sect[s]->obj_list;
		while (obj)
		{
			mlx->p0->x = obj->specs->x;
			mlx->p0->y = obj->specs->y;
			mlx->p1->x = mlx->p0->x + FIRE_RANGE * 10;
			mlx->p1->y = obj->specs->y;
			if (!ft_point_inside_check(mlx->sect[s], mlx->p0, mlx->p1))
				ft_obj_error(obj, o);
			obj = obj->next;
			o++;
		}
	}
	mlx->p0->x = mlx->player->pos->x;
	mlx->p0->y = mlx->player->pos->y;
	mlx->p1->x = mlx->p1->x + FIRE_RANGE * 10;
	mlx->p1->y = mlx->p1->y;
	if (!ft_point_inside_check(mlx->sect[mlx->player->sector], mlx->p0, mlx->p1))
		ft_player_sect_error();
}
