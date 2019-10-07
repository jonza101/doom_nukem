/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   im_events_sec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:35 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	change_vals(void *vval, char type, float snum, int button)
{
	int		*ival;
	float	*fval;

	if (type == 'i')
	{
		ival = (int *)vval;
		if (button == 5)
			*ival += (int)snum;
		else if (button == 4)
			*ival -= (int)snum;
	}
	else if (type == 'f')
	{
		fval = (float *)vval;
		if (button == 5)
			*fval += snum;
		else if (button == 4)
			*fval -= snum;
	}
}

void		check_sec_events_mwheel(t_core *cr, t_coord click, \
int button, int secid)
{
	t_coord		xy;
	t_sec		*sec;

	if (!(sec = find_sec_list(cr, secid)))
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + 4 && click.y < xy.y + 4 + ICON_SIZE)
		change_vals(&sec->floor, 'f', 1, button);
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE + 8 && click.y < xy.y + 8 + ICON_SIZE * 2)
		change_vals(&sec->ceiling, 'f', 1, button);
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE * 2 + 12 && click.y < xy.y + 12 + ICON_SIZE * 3)
		change_vals(&sec->ftex, 'i', 1, button);
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE * 3 + 16 && click.y < xy.y + 16 + ICON_SIZE * 4)
		change_vals(&sec->ctex, 'i', 1, button);
	else if (click.x > xy.x && click.x < xy.x + I_MENU_XLEN && \
	click.y > xy.y + ICON_SIZE * 4 + 20 && click.y < xy.y + 20 + ICON_SIZE * 5)
		change_vals(&sec->illum, 'f', 0.1f, button);
	valid_illum_val(&sec->illum);
}

static void	check_sec_events_p3(t_coord xy, int x, int y, t_sec *sec)
{
	if (x > xy.x + I_MENU_XLEN / 3 && \
	x < xy.x + I_MENU_XLEN / 3 + CHECKBOX_SIZE && \
	y > xy.y + ICON_SIZE * 5 + 24 && \
	y < xy.y + ICON_SIZE * 5 + 24 + CHECKBOX_SIZE)
		sec->isdoor = sec->isdoor == 0 ? 1 : 0;
	else if (x > xy.x + I_MENU_XLEN / 3 && \
	x < xy.x + I_MENU_XLEN / 3 + CHECKBOX_SIZE && \
	y > xy.y + ICON_SIZE * 5 + 24 + LINE_SIZE_Y && \
	y < xy.y + ICON_SIZE * 5 + 24 + CHECKBOX_SIZE + LINE_SIZE_Y)
		sec->isfinish = sec->isfinish == 0 ? 1 : 0;
	valid_illum_val(&sec->illum);
}

static void	check_sec_events_p2(t_coord xy, int x, int y, t_sec *sec)
{
	if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 12 + ICON_SIZE * 2 && y < xy.y + 12 + ICON_SIZE * 3)
		sec->ftex--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 12 + ICON_SIZE * 2 && y < xy.y + 12 + ICON_SIZE * 3)
		sec->ftex++;
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 16 + ICON_SIZE * 3 && y < xy.y + 16 + ICON_SIZE * 4)
		sec->ctex--;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 16 + ICON_SIZE * 3 && y < xy.y + 16 + ICON_SIZE * 4)
		sec->ctex++;
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 20 + ICON_SIZE * 4 && y < xy.y + 20 + ICON_SIZE * 5)
		sec->illum -= 0.1;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 20 + ICON_SIZE * 4 && y < xy.y + 20 + ICON_SIZE * 5)
		sec->illum += 0.1;
	else
		check_sec_events_p3(xy, x, y, sec);
}

void		check_sec_events(t_core *cr, int x, int y, int secid)
{
	t_coord	xy;
	t_sec	*sec;

	if (!(sec = find_sec_list(cr, secid)))
		return ;
	xy.x = WIN_WIDTH - I_MENU_XLEN - 4;
	xy.y = 0 + 4;
	if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 4 && y < xy.y + 4 + ICON_SIZE)
		sec->floor -= 0.1;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 4 && y < xy.y + 4 + ICON_SIZE)
		sec->floor += 0.1;
	else if (x > xy.x && x < xy.x + ICON_SIZE && \
	y > xy.y + 8 + ICON_SIZE && y < xy.y + 8 + ICON_SIZE * 2)
		sec->ceiling -= 0.1;
	else if (x > xy.x + I_MENU_XLEN - ICON_SIZE && x < xy.x + I_MENU_XLEN && \
	y > xy.y + 8 + ICON_SIZE && y < xy.y + 8 + ICON_SIZE * 2)
		sec->ceiling += 0.1;
	else
		check_sec_events_p2(xy, x, y, sec);
}
