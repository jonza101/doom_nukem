/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_canvas_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:28 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void		display_coords(t_core *cr, char *text, t_wall *wall, t_coord xy)
{
	char	*tmp;

	ft_strcat(text, "P1(y, x):    ");
	ft_strcat(text, tmp = ft_itoa(wall->p1.y));
	free(tmp);
	ft_strcat(text, " ");
	ft_strcat(text, tmp = ft_itoa(wall->p1.x));
	free(tmp);
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 10, \
	I_MENU_YLEN / 10, 0, text);
	ft_strclr(text);
	ft_strcat(text, "P2(y, x):    ");
	ft_strcat(text, tmp = ft_itoa(wall->p2.y));
	free(tmp);
	ft_strcat(text, " ");
	ft_strcat(text, tmp = ft_itoa(wall->p2.x));
	free(tmp);
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 10, \
	I_MENU_YLEN / 10 * 2, 0, text);
	ft_strclr(text);
}

static void		display_texture(t_core *cr, char *text, t_st *scn)
{
	ft_strcat(text, " [ ");
	ft_strcat(text, cr->tms = ft_itoa(scn->s));
	free(cr->tms);
	ft_strcat(text, " ]");
	ft_strcat(text, " texture: ");
	ft_strcat(text, cr->tms = ft_itoa(scn->t));
	free(cr->tms);
}

static void		display_arrows(t_core *cr, int x, int y)
{
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		x, y);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		x + I_MENU_XLEN - ICON_SIZE, y);
}

void			info_menu(t_core *cr, t_wall *wall)
{
	t_coord	xy;
	t_coord	ab;
	char	*text;

	if (!wall)
		return ;
	strnew_nullcheck(&text, STR_MED);
	cr->i_menu_is_open = 1;
	cr->i_menu_wall = wall;
	ab.x = I_MENU_XLEN;
	ab.y = I_MENU_YLEN;
	xy.x = WIN_WIDTH - ab.x - 4;
	xy.y = 0 + 4;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	display_coords(cr, text, wall, xy);
	display_arrows(cr, xy.x, I_MENU_YLEN / 3 + 10);
	display_texture(cr, text, &wall->sectors[0]);
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 5, \
	I_MENU_YLEN / 3 + 10, 0, text);
	ft_strclr(text);
	display_arrows(cr, xy.x, I_MENU_YLEN / 3 + 10 + ICON_SIZE);
	display_texture(cr, text, &wall->sectors[1]);
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 5, \
	I_MENU_YLEN / 3 + 10 + ICON_SIZE, 0, text);
	free(text);
}
