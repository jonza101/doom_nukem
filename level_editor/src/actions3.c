/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:13:28 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	check_i_menu_bounds(t_core *cr, int x, int y)
{
	if ((cr->i_menu_is_open == 2 || \
	cr->i_menu_is_open == 4 || cr->i_menu_is_open == 1) && \
	x > WIN_WIDTH - I_MENU_XLEN - 4 && x < WIN_WIDTH && y > 4)
	{
		if ((y < 4 + I_SEC_MENU_YLEN && cr->i_menu_is_open == 4) || \
		y < 4 + I_MENU_YLEN)
			return (1);
	}
	cr->i_menu_is_open = 0;
	return (0);
}

static void	mouse_press_button1(int x, int y, t_core *cr)
{
	if (!choose_instrument(cr, x, y))
	{
		if (cr->menu_is_open == 1 || cr->menu_is_open == 3)
		{
			check_menu_events(cr, x, y);
		}
		else if (check_i_menu_bounds(cr, x, y) == 1)
		{
			if (cr->i_menu_is_open == 2)
			{
				check_obj_events(x, y, cr->closest_obj);
			}
			else if (cr->i_menu_is_open == 1)
			{
				check_wall_events(x, y, cr->i_menu_wall);
			}
			else if (cr->i_menu_is_open == 4)
			{
				check_sec_events(cr, x, y, cr->sel_sec_id);
			}
		}
		else
			(*cr->inst_func)(cr, x, y);
	}
}

static void	mouse_press_button2(int x, int y, t_core *cr)
{
	int		wall_id;

	cr->rmb = 1;
	find_multi_sel(cr);
	if ((wall_id = select_wall(cr, x, y)) >= 0)
	{
		find_by_index(cr, wall_id)->color = SELECT_COLOR;
		redraw(cr);
		rmb_menu(cr, find_by_index(cr, wall_id), x, y);
	}
	else
	{
		redraw(cr);
		rmb_menu(cr, NULL, x, y);
	}
	cr->multi_sel = 0;
}

static void	mouse_press_button5(t_coord click, int button, t_core *cr)
{
	if (cr->i_menu_is_open == 2)
	{
		check_obj_events_mwheel(click, button, cr->closest_obj);
		redraw(cr);
	}
	else if (cr->i_menu_is_open == 1)
	{
		check_wall_events_mwheel(click, button, cr->i_menu_wall);
		redraw(cr);
	}
	else if (cr->i_menu_is_open == 4)
	{
		check_sec_events_mwheel(cr, click, button, cr->sel_sec_id);
		redraw(cr);
	}
}

int			mouse_press(int button, int x, int y, t_core *cr)
{
	t_coord	click;

	click.x = x;
	click.y = y;
	if (button == 1 && !check_bounds(x, y))
		mouse_press_button1(x, y, cr);
	else if (button == 2 && !check_bounds(x, y))
		mouse_press_button2(x, y, cr);
	else if (button == 3)
	{
		cr->test = 1;
		cr->msmem.x = x;
		cr->msmem.y = y;
		cr->dragm = 1;
	}
	else if ((button == 5 || button == 4) && !check_bounds(x, y))
		mouse_press_button5(click, button, cr);
	return (0);
}
