/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:39 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void	record_sectors_part3_p2(t_core *cr)
{
	if (cr->rs.wtmp->sectors[0].s == cr->rs.i)
	{
		cr->rs.tmp = ft_itoa(cr->rs.wtmp->sectors[1].s);
		cr->rs.conn = ft_strcat(cr->rs.conn, cr->rs.tmp);
		free(cr->rs.tmp);
	}
	else if (cr->rs.wtmp->sectors[1].s == cr->rs.i)
	{
		cr->rs.tmp = ft_itoa(cr->rs.wtmp->sectors[0].s);
		cr->rs.conn = ft_strcat(cr->rs.conn, cr->rs.tmp);
		free(cr->rs.tmp);
	}
}

static void	record_sectors_part2(t_core *cr)
{
	choose_direction(cr, &cr->rs.cw, find_by_index(cr, cr->idcurr), cr->rs.i);
	while ((cr->rs.curr = \
			find_next_wall(cr, &cr->rs.cw, cr->rs.curr, cr->rs.i)) >= 0)
	{
		record_sectors_part3(cr);
		if (cr->rs.wtmp->isportal == 1)
			record_sectors_part3_p2(cr);
		else
			cr->rs.conn = ft_strcat(cr->rs.conn, "-1");
		if (cr->rs.curr == cr->idcurr)
			break ;
		else
		{
			ft_strcat(cr->rs.txt, " ");
			ft_strcat(cr->rs.conn, " ");
			ft_strcat(cr->rs.wtx, " ");
		}
	}
}

static void	record_sectors_part_p2(t_core *cr, int fd)
{
	ft_putstr_fd(cr->rs.conn, fd);
	ft_strclr(cr->rs.txt);
	ft_strclr(cr->rs.conn);
	ft_strcat(cr->rs.wtx, "|");
	cr->rs.i++;
}

static void	record_sectors_part(t_core *cr, int fd)
{
	record_sectors_partx(cr);
	if (find_sec_list(cr, cr->rs.i)->ctex == SKY)
		ft_strcat(cr->rs.wtx, "sky");
	else
	{
		ft_strcat(cr->rs.wtx, (cr->rs.tmp = \
		ft_itoa(find_sec_list(cr, cr->rs.i)->ctex)));
		free(cr->rs.tmp);
	}
	ft_strcat(cr->rs.wtx, "|");
	cr->idcurr = -1;
	iter_wall(cr, cr->rs.i, -1, &find_any_wall_in_sec);
	cr->rs.curr = cr->idcurr;
	if (cr->idcurr != -1)
		record_sectors_part2(cr);
	ft_strcat(cr->rs.txt, "|");
	ft_putstr_fd(cr->rs.txt, fd);
	if (cr->rs.sec->illum > 0)
	{
		ft_strcat(cr->rs.conn, "|");
		ft_strcat(cr->rs.conn, (cr->rs.tmp = ft_ftoa(cr->rs.sec->illum)));
		free(cr->rs.tmp);
		ft_strcat(cr->rs.conn, "|");
	}
	record_sectors_part_p2(cr, fd);
}

void		record_sectors(t_core *cr, int fd)
{
	cr->rs.i = 0;
	cr->rs.doprint_wtx = 0;
	strnew_nullcheck(&cr->rs.txt, STR_LARGE);
	strnew_nullcheck(&cr->rs.conn, STR_LARGE);
	strnew_nullcheck(&cr->rs.wtx, STR_LARGE * cr->sec_num);
	iter_wall(cr, 0, -1, &find_any_wall_in_sec);
	while (cr->rs.i < cr->sec_num && cr->idcurr != -1)
		record_sectors_part(cr, fd);
	free(cr->rs.txt);
	free(cr->rs.conn);
	ft_putstr_fd("\n", fd);
	if (cr->rs.i == cr->sec_num)
	{
		ft_putstr_fd(cr->rs.wtx, fd);
		ft_putstr_fd("\n", fd);
	}
	free(cr->rs.wtx);
}
