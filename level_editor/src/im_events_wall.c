/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_events_wall.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:38 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	check_wall_events(int x, int y, t_wall *wall)
{
	t_coord	xy;

	if (!wall)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > I_MENU_YLEN / 3 + 10 && y < I_MENU_YLEN / 3 + 10 + ICON_SIZE)
		wall->sectors[0].t--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > I_MENU_YLEN / 3 + 10 && y < I_MENU_YLEN / 3 + 10 + ICON_SIZE)
		wall->sectors[0].t++;
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > I_MENU_YLEN / 3 + 10 + ICON_SIZE && y < I_MENU_YLEN / 3 + 10 + \
	ICON_SIZE * 2)
		wall->sectors[1].t--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > I_MENU_YLEN / 3 + 10 + ICON_SIZE && y < I_MENU_YLEN / 3 + 10 + \
	ICON_SIZE * 2)
		wall->sectors[1].t++;
}

void	check_wall_events_mwheel(t_coord click, int button, t_wall *wall)
{
	t_coord	xy;

	if (!wall)
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > I_MENU_YLEN / 3 + 10 && click.y < I_MENU_YLEN / 3 + 10 + \
	ICON_SIZE)
	{
		if (button == 5)
			wall->sectors[0].t++;
		else if (button == 4)
			wall->sectors[0].t--;
	}
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > I_MENU_YLEN / 3 + 10 + ICON_SIZE && click.y < I_MENU_YLEN / 3 + \
	10 + ICON_SIZE * 2)
	{
		if (button == 5)
			wall->sectors[1].t++;
		else if (button == 4)
			wall->sectors[1].t--;
	}
}
