/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:08 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void			restore_id(t_core *cr)
{
	t_wall		*wall;
	int			i;

	i = 0;
	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		wall->index = i;
		i++;
		wall = wall->next;
	}
}

static void			erase_wall(t_core *cr, t_wall *wall, int mod)
{
	t_wall	*rm;

	rm = mod == 0 ? wall : wall->next;
	remove_sectors(cr, rm);
	if (mod == 0)
		cr->wlist = wall->next;
	else
		wall->next = ((t_wall *)wall->next)->next;
	free(rm);
	restore_id(cr);
	restore_sec_id_v2(cr);
}

void				erase_by_id(t_core *cr, int id)
{
	t_wall	*wall;

	if (!(wall = cr->wlist))
		return ;
	if (!wall->next)
	{
		free(wall);
		cr->wlist = NULL;
		return ;
	}
	if (id == 0)
	{
		erase_wall(cr, wall, 0);
		return ;
	}
	while (wall->next)
	{
		if (((t_wall *)wall->next)->index == id)
		{
			erase_wall(cr, wall, 1);
			return ;
		}
		wall = wall->next;
	}
}

void				eraser(void *td, int x, int y)
{
	t_core	*cr;
	int		id;

	cr = td;
	id = select_wall(cr, x, y);
	if (id == -1)
		del_object(cr, cr->closest_obj->id);
	else if (id != -2)
	{
		erase_by_id(cr, id);
		redraw(cr);
	}
}
