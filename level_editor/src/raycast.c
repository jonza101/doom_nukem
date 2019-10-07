/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:49 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "math.h"

static void		vert_line_case(t_core *cr, t_wall *wall, t_coord ray, \
															t_obj *obj)
{
	float dist;

	dist = cr->dist;
	if (obj->fcoord.y > min(wall->p1.y, wall->p2.y) && \
	obj->fcoord.y < max(wall->p1.y, wall->p2.y) && \
	((ray.x > obj->fcoord.x && obj->fcoord.x <= wall->p1.x) || \
	(ray.x < obj->fcoord.x && obj->fcoord.x >= wall->p1.x)))
	{
		cr->hit.x = wall->p1.x;
		cr->hit.y = obj->fcoord.y;
		dist = cr->hit.x > obj->fcoord.x ? cr->hit.x - obj->fcoord.x : \
		obj->fcoord.x - cr->hit.x;
		if (dist < cr->dist)
		{
			cr->dist = dist;
			cr->secmem[0] = wall->sectors[0].s;
			cr->secmem[1] = wall->sectors[1].s;
			cr->debug = cr->hit;
		}
	}
}

static void		calc_p2(t_core *cr, t_wall *wall, float m1, t_obj *obj)
{
	float dist;

	dist = cr->dist;
	if (cr->hit.x < min(wall->p1.x, wall->p2.x) || \
	cr->hit.x > max(wall->p1.x, wall->p2.x))
		return ;
	if ((cr->hit.x - obj->fcoord.x < 0 && cr->dir.x > 0) || \
	(cr->hit.x - obj->fcoord.x > 0 && cr->dir.x < 0))
		return ;
	cr->hit.y = wall->p1.y + (cr->hit.x - wall->p1.x) * m1;
	dist = sqrt(pow(cr->hit.x - obj->fcoord.x, 2) + \
	pow(cr->hit.y - obj->fcoord.y, 2));
	if (dist < cr->dist)
	{
		cr->dist = dist;
		cr->secmem[0] = wall->sectors[0].s;
		cr->secmem[1] = wall->sectors[1].s;
		cr->debug = cr->hit;
	}
}

static void		calc(t_core *cr, t_wall *wall, t_coord ray, t_obj *obj)
{
	float	m1;
	float	m2;
	float	b1;
	float	b2;
	float	dist;

	dist = cr->dist;
	if (wall->p1.x - wall->p2.x == 0)
	{
		vert_line_case(cr, wall, ray, obj);
		return ;
	}
	m1 = (float)(wall->p1.y - wall->p2.y) / (wall->p1.x - wall->p2.x != 0 ? \
	wall->p1.x - wall->p2.x : 0.01);
	m2 = (float)(ray.y - obj->fcoord.y) / (ray.x - obj->fcoord.x != 0 ? \
	ray.x - obj->fcoord.x : 0.01);
	b1 = wall->p1.y - m1 * wall->p1.x;
	b2 = ray.y - m2 * ray.x;
	if (m1 == m2)
		return ;
	cr->hit.x = (b2 - b1) / (m1 - m2);
	calc_p2(cr, wall, m1, obj);
}

static void		raycast(t_core *cr, t_obj *obj)
{
	t_wall		*wall;
	t_coord		ray;

	cr->dist = 1000;
	ray.x = obj->fcoord.x + cr->dir.x;
	ray.y = obj->fcoord.y + cr->dir.y;
	wall = cr->wlist;
	while (wall)
	{
		calc(cr, wall, ray, obj);
		wall = wall->next;
	}
	if (obj->isplayer && (cr->secmem[0] != -1 || cr->secmem[1] != -1))
	{
		cr->vs.x0 = obj->fcoord.x + cr->offs.x;
		cr->vs.y0 = obj->fcoord.y + cr->offs.y;
		cr->vs.x1 = cr->debug.x + cr->offs.x;
		cr->vs.y1 = cr->debug.y + cr->offs.y;
		cr->vs.color = 0xff0000;
		bresenham(cr, &pxl_put_wrap);
	}
}

void			spot_sector_around(t_core *cr, t_obj *obj)
{
	int			mem[2];

	if (!obj)
		return ;
	cr->secmem[0] = -1;
	cr->secmem[1] = -1;
	mem[0] = -1;
	mem[1] = -1;
	cr->dir.x = 10;
	cr->dir.y = 0;
	raycast(cr, obj);
	mem[0] = cr->secmem[0];
	mem[1] = cr->secmem[1];
	cr->dir.x = -10;
	cr->dir.y = 0;
	raycast(cr, obj);
	if ((mem[0] == cr->secmem[0] || mem[0] == cr->secmem[1]) && mem[0] != -1)
		obj->sec = mem[0];
	else if ((mem[1] == cr->secmem[0] || mem[1] == cr->secmem[1]) && \
	mem[1] != -1)
		obj->sec = mem[1];
}
