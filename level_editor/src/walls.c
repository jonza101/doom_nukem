/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/16 20:37:06 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void				add_first_wall(t_core *cr, int *i, t_wall **wall)
{
	if (!(cr->wlist = (t_wall *)malloc(sizeof(t_wall))))
		err_ex(0);
	*wall = cr->wlist;
	cr->wlist->next = NULL;
	*i = 0;
}

static void				add_wall_attributes(t_core *cr, int i, t_wall *wall)
{
	wall->p1.x = cr->vs.mem_x;
	wall->p1.y = cr->vs.mem_y;
	wall->p2.x = cr->vs.x1;
	wall->p2.y = cr->vs.y1;
	wall->color = WALL_COLOR;
	wall->index = i;
	wall->len = calc_dist(wall->p1.x, wall->p1.y, wall->p2.x, wall->p2.y);
	wall->sectors[0].s = -1;
	wall->sectors[1].s = -1;
	wall->sectors[0].t = ST_TEXTURE;
	wall->sectors[1].t = ST_TEXTURE;
	wall->isportal = cr->mpsw;
}

void					add_wall(t_core *cr)
{
	t_wall		*wall;
	int			i;

	if (cr->vs.x1 == cr->vs.mem_x && cr->vs.y1 == cr->vs.mem_y)
		return ;
	i = 1;
	wall = cr->wlist;
	if (!wall)
		add_first_wall(cr, &i, &wall);
	else
	{
		while (wall->next)
		{
			wall = wall->next;
			i++;
		}
		if (!(wall->next = (t_wall *)malloc(sizeof(t_wall))))
			err_ex(0);
		wall = wall->next;
		wall->next = NULL;
	}
	add_wall_attributes(cr, i, wall);
	cr->mpsw = 0;
	iter_wall(cr, 0, 0, &redraw_color);
}
