/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 18:10:09 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void			choose_instrument_p2(t_core *cr, int x, int y)
{
	(void)x;
	if (y > cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 2 && \
	y < cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 3)
	{
		cr->inst_func = select_wall_wrap;
		cr->highlight = 3;
	}
	else if (y > cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 3 && \
	y < cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 4)
	{
		cr->find_sec_color = SEL_SEC_COLOR;
		cr->inst_func = find_sector;
		cr->highlight = 4;
	}
	else if (y > cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 4 && \
	y < cr->inst_panel.y + cr->inst_panel_size.y)
	{
		cr->inst_func = select_sector;
		cr->highlight = 5;
	}
}

int					choose_instrument(t_core *cr, int x, int y)
{
	if (!(x > cr->inst_panel.x && x < cr->inst_panel_size.x && \
		y > cr->inst_panel.y && y < cr->inst_panel.y + cr->inst_panel_size.y))
		return (0);
	else if (y > cr->inst_panel.y && y < cr->inst_panel.y + \
	cr->inst_panel_size.y / INST_NUM)
	{
		cr->inst_func = draw_wall;
		cr->highlight = 1;
	}
	else if (y > cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM && y < \
		cr->inst_panel.y + cr->inst_panel_size.y / INST_NUM * 2)
	{
		cr->inst_func = eraser;
		cr->highlight = 2;
	}
	else
		choose_instrument_p2(cr, x, y);
	return (1);
}

void				display_instruments(t_core *cr)
{
	mlx_put_image_to_window(cr->mlx, cr->win, cr->icons_trash, \
		cr->inst_panel.x, cr->inst_panel.y);
}

static void			load_gui_p2(t_core *cr)
{
	cr->arrowl_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/arrow_left.xpm", \
	&cr->tr, &cr->tr);
	cr->arrowr_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/arrow_right.xpm", \
	&cr->tr, &cr->tr);
	cr->arrowl_data = (int *)mlx_get_data_addr(cr->arrowl_trash, \
	&cr->bpp, &(cr->linesize), &(cr->endian));
	cr->arrowr_data = (int *)mlx_get_data_addr(cr->arrowr_trash, \
	&cr->bpp, &(cr->linesize), &(cr->endian));
}

void				load_gui(t_core *cr)
{
	int	i;

	i = 1;
	cr->icons_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/instruments.xpm", \
	&cr->inst_panel_size.x, &cr->inst_panel_size.y);
	cr->icons_data = (int *)mlx_get_data_addr(cr->icons_trash, \
		&cr->bpp, &(cr->linesize), &(cr->endian));
	cr->inst_panel.x = INST_PANEL_X;
	cr->inst_panel.y = INST_PANEL_Y;
	cr->hl_trash = mlx_xpm_file_to_image(cr->mlx, "./gui/highlight.xpm", \
	&cr->tr, &cr->tr);
	cr->hl_data = (int *)mlx_get_data_addr(cr->hl_trash, \
	&cr->bpp, &(cr->linesize), &(cr->endian));
	load_gui_p2(cr);
}
