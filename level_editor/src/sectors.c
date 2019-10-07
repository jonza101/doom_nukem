/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 18:04:31 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "math.h"

static int		calc_angle(t_core *cr, t_wall *ref, t_coord *wp, int id)
{
	float	c;
	float	b;
	float	a;
	float	angle;

	c = ref->len;
	a = calc_dist(cr->rstart.x, cr->rstart.y, wp->x, wp->y);
	b = calc_dist(cr->rpoint.x, cr->rpoint.y, wp->x, wp->y);
	angle = acos((b * b + c * c - a * a) / (2 * b * c));
	if (angle < cr->angle_mem)
	{
		cr->angle_mem = angle;
		cr->idcurr = id;
		cr->wpoint = cr->wpoint_tmp;
	}
	if (angle != angle)
	{
		cr->angle_mem = 0;
		cr->idcurr = id;
		cr->wpoint = cr->wpoint_tmp;
	}
	if (cr->angle_mem == PI_CEIL)
		return (0);
	return (1);
}

static int		compare_walls(t_core *cr, t_wall *ref, t_wall *wall)
{
	t_coord		wallpoint;
	float		d;

	if (wall->index == ref->index)
		return (0);
	if ((wall->p1.x == cr->rpoint.x) && (wall->p1.y == cr->rpoint.y))
	{
		wallpoint.x = wall->p2.x;
		wallpoint.y = wall->p2.y;
		cr->wpoint_tmp = 2;
	}
	else if ((wall->p2.x == cr->rpoint.x) && (wall->p2.y == cr->rpoint.y))
	{
		wallpoint.x = wall->p1.x;
		wallpoint.y = wall->p1.y;
		cr->wpoint_tmp = 1;
	}
	else
		return (0);
	d = (cr->rpoint.x - cr->rstart.x) * (wallpoint.y - cr->rstart.y) - \
	(cr->rpoint.y - cr->rstart.y) * (wallpoint.x - cr->rstart.x);
	if ((d < 0 && cr->wside == 0) || (d > 0 && cr->wside == 1) || d == 0)
		calc_angle(cr, ref, &wallpoint, wall->index);
	return (0);
}

static void		halfplane_part(t_core *cr, t_wall *ref)
{
	if (cr->wpoint == 2)
	{
		cr->rpoint.x = ref->p2.x;
		cr->rpoint.y = ref->p2.y;
		cr->rstart.x = ref->p1.x;
		cr->rstart.y = ref->p1.y;
	}
	else
	{
		cr->rpoint.x = ref->p1.x;
		cr->rpoint.y = ref->p1.y;
		cr->rstart.x = ref->p2.x;
		cr->rstart.y = ref->p2.y;
	}
}

/*
**(bx-ax)*(py-ay)-(by-ay)*(px-ax)
*/

void			halfplane(t_core *cr, t_wall *ref)
{
	t_wall	*wall;

	cr->angle_mem = PI_CEIL;
	cr->idcurr = 0;
	if (ref->color == cr->find_sec_color)
		return ;
	halfplane_part(cr, ref);
	cr->wside = (cr->rpoint.x - cr->rstart.x) * \
	(cr->click.y - (cr->rstart.y + cr->offs.y)) - \
	(cr->rpoint.y - cr->rstart.y) * (cr->click.x - \
	(cr->rstart.x + cr->offs.x)) > 0 ? 1 : 0;
	wall = cr->wlist;
	if (!wall || !ref)
		return ;
	while (wall)
	{
		compare_walls(cr, ref, wall);
		wall = wall->next;
	}
	ref->color = cr->find_sec_color;
	halfplane(cr, find_by_index(cr, cr->idcurr));
}
