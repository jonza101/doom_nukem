/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:13:43 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			find_multi_sel(t_core *cr)
{
	t_wall	*wall;
	int		cl_mem;

	cl_mem = 0;
	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		if (cl_mem > 1)
		{
			cr->multi_sel = 1;
			return ;
		}
		if (wall->color == SELECT_COLOR)
			cl_mem++;
		wall = wall->next;
	}
}

void			apply_sector(t_core *cr, t_wall *wall, int pr1, int pr2)
{
	(void)pr1;
	(void)pr2;
	if (wall->color != SEL_SEC_COLOR)
		return ;
	wall->color = APP_SEC_COLOR;
	if (wall->sectors[0].s < 0)
	{
		wall->sectors[0].s = cr->sec_num;
	}
	else if (wall->sectors[1].s < 0)
	{
		wall->sectors[1].s = cr->sec_num;
	}
}

void			turn_color(t_core *cr, t_wall *wall, int color1, int color2)
{
	(void)cr;
	if (wall->color == color1)
		wall->color = color2;
}

void			redraw_color(t_core *cr, t_wall *wall, int exc1, int exc2)
{
	if (wall->color == exc1 || wall->color == exc2)
		return ;
	if (wall->sectors[0].s < 0 && wall->sectors[1].s < 0)
		wall->color = wall->isportal == 0 ? WALL_COLOR : PORTAL_COLOR;
	else if (cr->multi_sel == 0)
		wall->color = wall->isportal == 0 ? APP_SEC_COLOR : APP_PORTAL_COLOR;
	cr->multi_sel = 0;
}

void			is_there_color(t_core *cr, t_wall *wall, int color, int pr2)
{
	(void)cr;
	(void)pr2;
	if (wall->color == color)
		cr->detect_cl = 1;
}
