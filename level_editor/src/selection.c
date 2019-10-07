/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:16:14 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "math.h"

int					is_near_wall(t_core *cr, t_wall *wall, int x, int y)
{
	if (x < min(wall->p1.x + cr->offs.x, wall->p2.x + cr->offs.x) \
											- SELECT_PADDING || \
	x > max(wall->p1.x + cr->offs.x, wall->p2.x + cr->offs.x) \
											+ SELECT_PADDING || \
	y < min(wall->p1.y + cr->offs.y, wall->p2.y + cr->offs.y) \
											- SELECT_PADDING || \
	y > max(wall->p1.y + cr->offs.y, wall->p2.y + cr->offs.y) + SELECT_PADDING)
		return (0);
	return (1);
}

static void			select_sector_part(t_wall **wall, t_wall **prev, \
int *secmem)
{
	if ((*wall)->color == SELECT_COLOR)
	{
		if (!*prev)
		{
			if ((*wall)->sectors[0].s != -1)
				*prev = *wall;
			else if ((*wall)->sectors[1].s != -1)
				*prev = *wall;
		}
		else
		{
			if ((*wall)->sectors[0].s == (*prev)->sectors[0].s || \
			(*wall)->sectors[0].s == (*prev)->sectors[1].s)
				*secmem = (*wall)->sectors[0].s;
			else if ((*wall)->sectors[1].s == (*prev)->sectors[1].s || \
			(*wall)->sectors[1].s == (*prev)->sectors[0].s)
				*secmem = (*wall)->sectors[1].s;
			*prev = *wall;
		}
	}
	*wall = (*wall)->next;
}

void				select_sector(void *td, int x, int y)
{
	t_core	*cr;
	t_wall	*wall;
	int		secmem;
	t_wall	*prev;

	prev = NULL;
	secmem = -1;
	cr = (t_core *)td;
	cr->find_sec_color = SELECT_COLOR;
	cr->searchtype = 0;
	find_sector(td, x, y);
	cr->searchtype = 1;
	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
		select_sector_part(&wall, &prev, &secmem);
	cr->sel_sec_id = secmem;
	cr->i_menu_is_open = 4;
}

static void			select_wall_part(t_core *cr, int x, int y)
{
	if (is_near_wall(cr, cr->sl.wall, x, y))
	{
		cr->sl.a = calc_dist(x, y, cr->sl.wall->p1.x + cr->offs.x, \
		cr->sl.wall->p1.y + cr->offs.y);
		cr->sl.b = calc_dist(x, y, cr->sl.wall->p2.x + cr->offs.x, \
		cr->sl.wall->p2.y + cr->offs.y);
		cr->sl.p = (cr->sl.a + cr->sl.b + cr->sl.wall->len) / 2;
		cr->sl.dist = 2 * sqrt(cr->sl.p * (cr->sl.p - cr->sl.a) * \
		(cr->sl.p - cr->sl.b) * (cr->sl.p - cr->sl.wall->len)) / \
		cr->sl.wall->len;
		if (cr->sl.dist <= cr->sl.min_dist)
		{
			cr->sl.min_dist = cr->sl.dist;
			cr->sl.closest_wall = cr->sl.wall->index;
		}
	}
	cr->sl.wall = cr->sl.wall->next;
}

int					select_wall(t_core *cr, int x, int y)
{
	cr->sl.closest_wall = -2;
	cr->sl.min_dist = SELECT_RADIUS;
	cr->sl.wall = cr->wlist;
	while (cr->sl.wall)
		select_wall_part(cr, x, y);
	if (sel_object(cr, x, y) < cr->sl.min_dist && cr->searchtype == 1)
	{
		iter_wall(cr, -1, -1, &redraw_color);
		cr->closest_obj->color = SELECT_COLOR;
		obj_info_menu(cr, cr->closest_obj);
		return (-1);
	}
	if (cr->sl.min_dist == SELECT_RADIUS)
	{
		iter_wall(cr, -1, -1, &redraw_color);
		return (-2);
	}
	if (!cr->ctrl_button && !cr->multi_sel)
	{
		if (!cr->multi_sel)
			iter_wall(cr, -1, -1, &redraw_color);
		else
			iter_wall(cr, SELECT_COLOR, -1, &redraw_color);
	}
	return (cr->sl.closest_wall);
}
