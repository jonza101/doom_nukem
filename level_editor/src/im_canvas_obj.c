/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_canvas_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:19 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

void			obj_info_menu(t_core *cr, t_obj *obj)
{
	t_coord	xy;
	t_coord	ab;
	char	*text;

	if (!obj)
		return ;
	cr->i_menu_is_open = 2;
	ab.x = I_MENU_XLEN;
	ab.y = I_MENU_YLEN;
	xy.x = WIN_WIDTH - ab.x - 4;
	xy.y = 0 + 4;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	strnew_nullcheck(&text, STR_MED);
	ft_strcat(text, " Type: ");
	ft_strcat(text, cr->tms = ft_itoa(obj->type));
	free(cr->tms);
	mlx_string_put(cr->mlx, cr->win, xy.x + I_MENU_XLEN / 3, \
	I_MENU_YLEN / 9, 0, text);
	free(text);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowl_trash, \
		xy.x, I_MENU_YLEN / 10);
	mlx_put_image_to_window(cr->mlx, cr->win, cr->arrowr_trash, \
		xy.x + I_MENU_XLEN - ICON_SIZE, I_MENU_YLEN / 10);
}
