/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:04 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void				highlight(t_core *cr)
{
	t_coord		pos;

	if (!cr->highlight)
		return ;
	pos.y = cr->inst_panel.y + (float)cr->inst_panel_size.y /
	INST_NUM * (cr->highlight - 1);
	pos.x = cr->inst_panel.x;
	mlx_put_image_to_window(cr->mlx, cr->win, cr->hl_trash, pos.x, pos.y);
}

void				find_sector(void *td, int x, int y)
{
	t_core		*cr;
	int			wall_id;

	cr = td;
	if ((wall_id = select_wall(cr, x, y)) >= 0)
	{
		cr->click.x = x;
		cr->click.y = y;
		cr->wpoint = 2;
		halfplane(cr, find_by_index(cr, wall_id));
	}
}

void				select_wall_wrap(void *td, int x, int y)
{
	t_core	*cr;
	t_wall	*wall;

	cr = td;
	if (select_wall(cr, x, y) >= 0)
	{
		wall = find_by_index(cr, select_wall(cr, x, y));
		wall->color = SELECT_COLOR;
		info_menu(cr, wall);
	}
}

void				draw_wall(void *td, int x, int y)
{
	t_core	*cr;

	cr = td;
	if (cr->menu_is_open == 1)
		return ;
	cr->lmb = 1;
	cr->vs.x0 = x;
	cr->vs.y0 = y;
	cr->vs.x1 = x;
	cr->vs.y1 = y;
	grid_magnet(cr, &cr->vs.x0, &cr->vs.y0, 0);
	cr->vs.mem_x = cr->vs.x0;
	cr->vs.mem_y = cr->vs.y0;
}
