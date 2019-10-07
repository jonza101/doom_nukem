/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:59 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/20 20:33:23 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "editor.h"

int			red_button(t_core *pr)
{
	(void)pr;
	exit(0);
}

int			key_release(int keycode, t_core *cr)
{
	if (keycode == 257)
		cr->shift_button = 0;
	else if (keycode == 256)
		cr->ctrl_button = 0;
	return (0);
}

static void	key_action_p2(int keycode, t_core *cr)
{
	if (keycode == 67)
		cr->test *= -1;
	else if (keycode == 117)
		del_object(cr, 0);
	else if (keycode == 49)
	{
		cr->offs.x = WIN_WIDTH / 2;
		cr->offs.y = WIN_HIGHT / 2;
	}
	else if (keycode == 32)
		del_last_sector(cr);
	else if (keycode == 18)
		cr->show_obj_num *= -1;
}

int			key_action(int keycode, t_core *cr)
{
	if (keycode == 53)
		exit(0);
	else if (keycode == 16)
		new_sector(cr);
	else if (keycode == 257)
		cr->shift_button = 1;
	else if (keycode == 256)
		cr->ctrl_button = 1;
	else if (keycode == 1)
		save_map(cr);
	else if (keycode == 37)
		load_map(cr);
	else if (keycode == 123)
		cr->player.fcoord.x -= 20;
	else if (keycode == 124)
		cr->player.fcoord.x += 20;
	else if (keycode == 125)
		cr->player.fcoord.y += 20;
	else if (keycode == 126)
		cr->player.fcoord.y -= 20;
	else
		key_action_p2(keycode, cr);
	redraw(cr);
	return (0);
}
