/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:13:34 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "math.h"

static int		legal_abs(int x)
{
	return (x >= 0 ? x : -x);
}

void			straight_line(t_core *cr, int *x, int *y)
{
	int		dx;
	int		dy;
	float	m;

	dx = legal_abs(*x - cr->vs.mem_x);
	dy = legal_abs(*y - cr->vs.mem_y);
	if (dx == 0 || dy == 0)
		return ;
	m = atan2(legal_abs(dy), legal_abs(dx));
	if (m > 0 && m < (PI_4 / 2) / 3)
		*y = cr->vs.mem_y;
	else if (m > (PI_4 / 2) / 3 * 2 && m < (PI_4 / 2))
		*x = cr->vs.mem_x;
	else
	{
		*x = *x - cr->vs.mem_x > 0 ? cr->vs.mem_x + \
		(dx + dy) / 2 : cr->vs.mem_x - (dx + dy) / 2;
		*y = *y - cr->vs.mem_y > 0 ? cr->vs.mem_y + \
		(dx + dy) / 2 : cr->vs.mem_y - (dx + dy) / 2;
	}
}

static void		copy_vals(t_core *cr)
{
	cr->vs.x0_copy = cr->vs.x0;
	cr->vs.y0_copy = cr->vs.y0;
}

void			bresenham(t_core *cr, void (*print_func)(void *, int, int, int))
{
	int	sx;
	int	sy;
	int	e2;

	copy_vals(cr);
	cr->vs.dx = legal_abs(cr->vs.x1 - cr->vs.x0_copy);
	cr->vs.dy = legal_abs(cr->vs.y1 - cr->vs.y0_copy);
	sx = cr->vs.x0_copy < cr->vs.x1 ? 1 : -1;
	sy = cr->vs.y0_copy < cr->vs.y1 ? 1 : -1;
	cr->vs.err = (cr->vs.dx > cr->vs.dy ? cr->vs.dx : -cr->vs.dy) / 2;
	while (cr->vs.x0_copy != cr->vs.x1 || cr->vs.y0_copy != cr->vs.y1)
	{
		(*print_func)((void *)cr, cr->vs.x0_copy, cr->vs.y0_copy, cr->vs.color);
		e2 = cr->vs.err;
		if (e2 > -cr->vs.dx)
		{
			cr->vs.err -= cr->vs.dy;
			cr->vs.x0_copy += sx;
		}
		if (e2 < cr->vs.dy)
		{
			cr->vs.err += cr->vs.dx;
			cr->vs.y0_copy += sy;
		}
	}
}
