/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:16:08 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	new_sector(t_core *cr)
{
	cr->detect_cl = 0;
	iter_wall(cr, SEL_SEC_COLOR, -1, &is_there_color);
	if (!cr->detect_cl)
		return ;
	iter_wall(cr, -1, -1, &apply_sector);
	cr->sec_num++;
	iter_wall(cr, -1, -1, &redraw_color);
	add_sec_list(cr);
}

void	count_sectors(t_core *cr, t_wall *wall, int pr1, int pr2)
{
	(void)pr1;
	(void)pr2;
	if (wall->sectors[0].s >= 0 && wall->sectors[0].s > cr->sec_num - 1)
		cr->sec_num = wall->sectors[0].s + 1;
	else if (wall->sectors[1].s >= 0 && wall->sectors[1].s > cr->sec_num - 1)
		cr->sec_num = wall->sectors[1].s + 1;
}

void	sec_id_replace(t_core *cr, t_wall *wall, int idold, int idnew)
{
	(void)cr;
	if (wall->sectors[0].s == idold)
	{
		wall->sectors[0].s = idnew;
	}
	else if (wall->sectors[1].s == idold)
	{
		wall->sectors[1].s = idnew;
	}
}

int		does_sec_id_exist(t_core *cr, int idref)
{
	t_wall	*wall;

	wall = cr->wlist;
	while (wall)
	{
		if (wall->sectors[0].s == idref || wall->sectors[1].s == idref)
			return (1);
		wall = wall->next;
	}
	return (0);
}

void	get_last_sec(t_core *cr, t_wall *wall, int idref, int pr2)
{
	(void)pr2;
	if (wall->sectors[0].s > idref)
		cr->idcurr = wall->sectors[0].s;
	else if (wall->sectors[1].s > idref)
		cr->idcurr = wall->sectors[1].s;
}
