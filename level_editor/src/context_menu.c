/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context_menu.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:07:38 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

void		switch_isportal(t_core *cr, t_wall *wall, int switchval, int pr2)
{
	(void)pr2;
	(void)cr;
	if (wall->color != SELECT_COLOR)
		return ;
	wall->isportal = switchval;
	if (switchval == 1)
		wall->color = PORTAL_COLOR;
	else
		wall->color = wall->sectors[0].s < 0 && wall->sectors[1].s < 0 ? \
		WALL_COLOR : APP_SEC_COLOR;
}

static void	portal_switch(t_core *cr)
{
	if (cr->cmenu_elems.isportal == 1)
		iter_wall(cr, 0, 0, &switch_isportal);
	else
		iter_wall(cr, 1, 0, &switch_isportal);
	cr->cmenu_elems.isportal = cr->cmenu_elems.isportal > 0 ? 0 : 1;
}

void		check_menu_events(t_core *cr, int x, int y)
{
	if (x > cr->click.x && x < cr->click.x + MENU_XLEN && \
	y > cr->click.y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + LINE_SIZE_Y * 1 \
	&& y < cr->click.y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + \
	LINE_SIZE_Y * 1 + CHECKBOX_SIZE)
	{
		cr->player.fcoord.x = cr->click.x - cr->offs.x;
		cr->player.fcoord.y = cr->click.y - cr->offs.y;
	}
	else if (x > cr->click.x && x < cr->click.x + MENU_XLEN && \
	y > cr->click.y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + LINE_SIZE_Y * 2 \
	&& y < cr->click.y + (MENU_YLEN - LINE_SIZE_Y * 2) / 2 + \
	LINE_SIZE_Y * 2 + CHECKBOX_SIZE)
	{
		add_object(cr, cr->click.x - cr->offs.x, cr->click.y - cr->offs.y);
	}
	else if (cr->menu_is_open == 3)
		return ;
	else if (x > cr->click.x && x < cr->click.x + MENU_XLEN && \
	y > cr->click.y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + LINE_SIZE_Y * 0 \
	&& y < cr->click.y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + \
	LINE_SIZE_Y * 0 + CHECKBOX_SIZE)
		portal_switch(cr);
}

void		rmb_menu_p2(t_core *cr, t_wall *wall, int x, int y)
{
	t_coord	xy;
	t_coord	ab;
	char	*text;

	if (!wall)
		return ;
	strnew_nullcheck(&text, STR_SMALL);
	xy.x = x + (MENU_XLEN - LINE_SIZE_X) / 2;
	xy.y = y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + LINE_SIZE_Y * 0;
	ab.x = CHECKBOX_SIZE;
	ab.y = CHECKBOX_SIZE;
	draw_rectangle(cr, xy, ab, 0xffffff);
	ft_strcpy(text, "Portal");
	mlx_string_put(cr->mlx, cr->win, \
	x + (MENU_XLEN - LINE_SIZE_X) / 2 + ab.x * 2, \
	y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + LINE_SIZE_Y * 0, 0, text);
	if (wall->isportal == 1)
	{
		checkbox_fill(cr, xy, ab);
		cr->cmenu_elems.isportal = 1;
	}
	else
		cr->cmenu_elems.isportal = 0;
	free(text);
}

void		rmb_menu(t_core *cr, t_wall *wall, int x, int y)
{
	t_coord	xy;
	t_coord	ab;
	char	*text;

	cr->menu_is_open = 1;
	cr->click.x = x;
	cr->click.y = y;
	xy.x = x;
	xy.y = y;
	ab.x = MENU_XLEN;
	ab.y = MENU_YLEN;
	draw_rectangle(cr, xy, ab, MENU_COLOR);
	strnew_nullcheck(&text, STR_SMALL);
	ft_strcpy(text, "Place player");
	mlx_string_put(cr->mlx, cr->win, x + (MENU_XLEN - LINE_SIZE_X) / 2, \
	y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + LINE_SIZE_Y * 1, 0, text);
	ft_strcpy(text, "Place object");
	mlx_string_put(cr->mlx, cr->win, x + (MENU_XLEN - LINE_SIZE_X) / 2, \
	y + (MENU_YLEN - LINE_SIZE_Y * 3) / 2 + LINE_SIZE_Y * 2, 0, text);
	free(text);
	rmb_menu_p2(cr, wall, x, y);
}
