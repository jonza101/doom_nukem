/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:17:36 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			draw_nodes(t_core *cr, t_wall *wall, int pr1, int pr2)
{
	t_coord		xy;
	t_coord		ab;

	(void)pr1;
	(void)pr2;
	ab.x = POINT_SIZE;
	ab.y = POINT_SIZE;
	xy.x = wall->p1.x - POINT_SIZE / 2;
	xy.y = wall->p1.y - POINT_SIZE / 2;
	draw_rectangle_img_pxl(cr, xy, ab, POINT_COLOR);
	xy.x = wall->p2.x - POINT_SIZE / 2;
	xy.y = wall->p2.y - POINT_SIZE / 2;
	draw_rectangle_img_pxl(cr, xy, ab, POINT_COLOR);
}

static void		draw_walls(t_core *cr)
{
	t_wall	*wall;

	wall = cr->wlist;
	while (wall)
	{
		cr->vs.x0 = wall->p1.x;
		cr->vs.y0 = wall->p1.y;
		cr->vs.x1 = wall->p2.x;
		cr->vs.y1 = wall->p2.y;
		cr->vs.color = wall->color;
		bresenham(cr, &img_pxl);
		wall = wall->next;
	}
}

void			redraw(t_core *cr)
{
	mlx_clear_window(cr->mlx, cr->win);
	img_fill(cr->idata, 0x000000);
	grid(cr);
	draw_walls(cr);
	iter_wall(cr, 0, 0, &draw_nodes);
	draw_objects(cr);
	draw_player(cr);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->image, 0, 0);
	print_sec_num(cr);
	draw_objects_text(cr);
	display_instruments(cr);
	highlight(cr);
	spot_sector_around(cr, &cr->player);
	if (cr->i_menu_is_open == 1)
		info_menu(cr, cr->i_menu_wall);
	else if (cr->i_menu_is_open == 2)
		obj_info_menu(cr, cr->closest_obj);
	else if (cr->i_menu_is_open == 4)
		sec_info_menu(cr, cr->sel_sec_id);
}
