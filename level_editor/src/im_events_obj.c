/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_events_obj.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:31 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void			check_obj_events(int x, int y, t_obj *obj)
{
	t_coord	xy;

	if (!obj)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > I_MENU_YLEN / 10 && y < I_MENU_YLEN / 10 + ICON_SIZE)
		obj->type--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > I_MENU_YLEN / 10 && y < I_MENU_YLEN / 10 + ICON_SIZE)
		obj->type++;
}

void			check_obj_events_mwheel(t_coord click, int button, t_obj *obj)
{
	t_coord	xy;

	if (!obj)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > I_MENU_YLEN / 10 && click.y < I_MENU_YLEN / 10 + LINE_SIZE_Y)
	{
		if (button == 5)
			obj->type++;
		else if (button == 4)
			obj->type--;
	}
}
