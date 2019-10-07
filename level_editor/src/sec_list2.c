/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_list2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:56 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

void		add_sec_list(t_core *cr)
{
	t_sec	*sec;

	if (!(sec = (t_sec *)malloc(sizeof(t_sec))))
		err_ex(0);
	sec->next = *cr->slist;
	sec->illum = ST_ILLUMINATION;
	sec->floor = ST_FLOOR_HIGHT;
	sec->ceiling = ST_CEIL_HIGHT;
	sec->ftex = ST_FTEX;
	sec->ctex = ST_CTEX;
	sec->id = cr->sec_num - 1;
	sec->isdoor = 0;
	sec->isfinish = 0;
	*cr->slist = sec;
}

void		sec_list_id_replace(t_core *cr, int new, int old)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec->next)
	{
		if (sec->id == old)
		{
			sec->id = new;
			return ;
		}
		sec = sec->next;
	}
}

static void	del_sec_list_p2(t_sec *pr, int idref)
{
	t_sec	*sec;

	while (pr)
	{
		if (!pr->next)
			return ;
		sec = pr->next;
		if (!sec)
			return ;
		if (sec->id == idref)
		{
			pr->next = sec->next;
			free(sec);
			return ;
		}
		pr = pr->next;
	}
}

void		del_sec_list(t_core *cr, int idref)
{
	t_sec	*pr;

	pr = *cr->slist;
	if (!pr)
		return ;
	if (pr->id == idref)
	{
		*cr->slist = pr->next;
		free(pr);
		return ;
	}
	del_sec_list_p2(pr, idref);
}

t_sec		*find_sec_list(t_core *cr, int idref)
{
	t_sec		*sec;

	sec = *cr->slist;
	while (sec)
	{
		if (sec->id == idref)
			break ;
		sec = sec->next;
	}
	return (sec);
}
