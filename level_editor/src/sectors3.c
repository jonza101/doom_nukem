/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:16:11 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		restore_sec_id_v2(t_core *cr)
{
	int				i;
	int				scount;
	int				sw;

	i = 0;
	scount = -1;
	sw = 0;
	iter_wall(cr, i, -1, &get_last_sec);
	while (i <= cr->idcurr)
	{
		if ((does_sec_id_exist(cr, i) == 1))
		{
			scount++;
			iter_wall(cr, i, scount, &sec_id_replace);
			sec_list_id_replace(cr, scount, i);
			sw = 1;
		}
		i++;
	}
	cr->sec_num = sw == 1 ? scount + 1 : 0;
}

static void	remove_sectors_ag(t_core *cr, t_wall *wall, int pr1, int pr2)
{
	(void)pr1;
	(void)pr2;
	if (wall->sectors[0].s == cr->idsec.x || wall->sectors[0].s == cr->idsec.y)
	{
		wall->sectors[0].s = -1;
		wall->sectors[0].t = -1;
	}
	if (wall->sectors[1].s == cr->idsec.x || wall->sectors[1].s == cr->idsec.y)
	{
		wall->sectors[1].s = -1;
		wall->sectors[1].t = -1;
	}
}

void		remove_sectors(t_core *cr, t_wall *wall)
{
	cr->idsec.x = wall->sectors[0].s;
	cr->idsec.y = wall->sectors[1].s;
	iter_wall(cr, wall->index, 0, &remove_sectors_ag);
	del_sec_list(cr, cr->idsec.x);
	del_sec_list(cr, cr->idsec.y);
	iter_wall(cr, 0, 0, &redraw_color);
}

void		del_last_sector(t_core *cr)
{
	t_wall	*wall;

	if (cr->sec_num <= 0)
		return ;
	wall = cr->wlist;
	while (wall)
	{
		if (wall->sectors[0].s == cr->sec_num - 1)
			wall->sectors[0].s = -1;
		else if (wall->sectors[1].s == cr->sec_num - 1)
			wall->sectors[1].s = -1;
		wall = wall->next;
	}
	del_sec_list(cr, cr->sec_num-- - 1);
	iter_wall(cr, -1, -1, &redraw_color);
}
