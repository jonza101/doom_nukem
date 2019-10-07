/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_canvas_sec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:24 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void	sec_info_menu_lvls(t_core *cr, t_sec *sec, char *text, t_coord xy)
{
	ft_strcat(text, "Floor lvl: ");
	ft_strcat(text, cr->tms = ft_ftoa(sec->floor));
	free(cr->tms);
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + 4), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + 4));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, (xy.y + 4));
	ft_strclr(text);
	ft_strcat(text, "Ceiling lvl: ");
	ft_strcat(text, cr->tms = ft_ftoa(sec->ceiling));
	free(cr->tms);
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE + 8), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE + 8));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, (xy.y + ICON_SIZE + 8));
	ft_strclr(text);
}

static void	sec_info_menu_fctex(t_core *cr, t_sec *sec, char *text, t_coord xy)
{
	ft_strcat(text, "Floor tex: ");
	ft_strcat(text, cr->tms = ft_itoa(sec->ftex));
	free(cr->tms);
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE * 2 + 12), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE * 2 + 12));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, (xy.y + ICON_SIZE * 2 + 12));
	ft_strclr(text);
	ft_strcat(text, "Ceiling tex: ");
	if (sec->ctex == SKY)
		ft_strcat(text, "skybox");
	else
	{
		ft_strcat(text, cr->tms = ft_itoa(sec->ctex));
		free(cr->tms);
	}
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE * 3 + 16), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE * 3 + 16));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, (xy.y + ICON_SIZE * 3 + 16));
	ft_strclr(text);
}

static void	sec_info_menu_df(t_core *cr, t_sec *sec, char *text, t_coord xy)
{
	t_coord		ab;

	xy.x += I_MENU_XLEN / 3;
	xy.y = xy.y + ICON_SIZE * 5 + 24;
	ab.x = CHECKBOX_SIZE;
	ab.y = CHECKBOX_SIZE;
	draw_rectangle(cr, xy, ab, 0xffffff);
	ft_strcat(text, "Door");
	mlx_string_put(cr->mlx, cr->win, xy.x + CHECKBOX_SIZE + 10, \
	xy.y, 0, text);
	if (sec->isdoor == 1)
		checkbox_fill(cr, xy, ab);
	ft_strclr(text);
	xy.y += LINE_SIZE_Y;
	ab.x = CHECKBOX_SIZE;
	ab.y = CHECKBOX_SIZE;
	draw_rectangle(cr, xy, ab, 0xffffff);
	ft_strcat(text, "Finish");
	mlx_string_put(cr->mlx, cr->win, xy.x + CHECKBOX_SIZE + 10, \
	xy.y, 0, text);
	if (sec->isfinish == 1)
		checkbox_fill(cr, xy, ab);
	ft_strclr(text);
	free(text);
}

static void	sec_info_menu_illum(t_core *cr, t_sec *sec, char *text, t_coord xy)
{
	ft_strcat(text, "Illumination: ");
	ft_strcat(text, cr->tms = ft_ftoa(sec->illum));
	free(cr->tms);
	mlx_string_put(cr->mlx, cr->win, xy.x + 60, \
	(xy.y + ICON_SIZE * 4 + 20), 0, text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, (xy.y + ICON_SIZE * 4 + 20));
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, (xy.y + ICON_SIZE * 4 + 20));
	ft_strclr(text);
}

void		sec_info_menu(t_core *cr, int secid)
{
	t_coord	xy;
	t_coord	ab;
	char	*text;
	t_sec	*sec;

	if (!(sec = find_sec_list(cr, secid)))
		return ;
	cr->i_menu_is_open = 4;
	ab.x = I_MENU_XLEN;
	ab.y = I_SEC_MENU_YLEN;
	xy.x = WIN_WIDTH - ab.x - 4;
	xy.y = 0 + 4;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	strnew_nullcheck(&text, STR_MED);
	sec_info_menu_lvls(cr, sec, text, xy);
	sec_info_menu_fctex(cr, sec, text, xy);
	sec_info_menu_illum(cr, sec, text, xy);
	sec_info_menu_df(cr, sec, text, xy);
}
