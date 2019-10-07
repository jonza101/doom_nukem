/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:13:18 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			mouse_move(int x, int y, t_core *cr)
{
	if (cr->dragm == 1)
	{
		cr->offs.x += x - cr->msmem.x;
		cr->offs.y += y - cr->msmem.y;
		cr->msmem.x = x;
		cr->msmem.y = y;
		redraw(cr);
	}
	else if (cr->lmb == 1)
	{
		if (cr->shift_button == 1)
			straight_line(cr, &x, &y);
		redraw(cr);
		cr->vs.x1 = x;
		cr->vs.y1 = y;
		cr->vs.x0 = cr->vs.mem_x;
		cr->vs.y0 = cr->vs.mem_y;
		cr->vs.color = WALL_COLOR;
		grid_magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
		bresenham(cr, &pxl_put_wrap);
	}
	return (0);
}

static int	mouse_release_button1(int x, int y, t_core *cr)
{
	if (cr->menu_is_open == 1 || cr->menu_is_open == 3)
	{
		cr->menu_is_open = 0;
		redraw(cr);
		return (0);
	}
	if (cr->lmb == 1)
	{
		cr->lmb = 0;
		if (cr->shift_button == 1)
			straight_line(cr, &x, &y);
		cr->vs.x1 = x;
		cr->vs.y1 = y;
		grid_magnet(cr, &cr->vs.x1, &cr->vs.y1, 1);
		cr->vs.x1 -= cr->offs.x;
		cr->vs.y1 -= cr->offs.y;
		cr->vs.mem_x -= cr->offs.x;
		cr->vs.mem_y -= cr->offs.y;
		add_wall(cr);
	}
	return (1);
}

int			mouse_release(int button, int x, int y, t_core *cr)
{
	if (button == 1)
	{
		if (mouse_release_button1(x, y, cr) == 0)
			return (0);
	}
	else if (button == 2)
	{
		cr->rmb = 0;
		return (0);
	}
	else if (button == 3)
	{
		cr->test = 0;
		cr->dragm = 0;
	}
	else
		return (0);
	redraw(cr);
	return (0);
}
