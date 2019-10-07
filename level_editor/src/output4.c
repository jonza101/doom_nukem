/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:42 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static int	find_vt_id_part(int fd, char *line, int ret)
{
	free(line);
	close(fd);
	return (ret);
}

int			find_vt_id(t_core *cr, float x, float y)
{
	int		fd;
	char	*line;
	int		i;

	open_gamesave(&fd);
	i = 0;
	prepare_gnlstr(&cr->gnlstr[5]);
	while (gnl_struct(&cr->gnlstr[5], fd, &line) > 0)
	{
		if (line[0] != 'v')
			return (find_vt_id_part(fd, line, 0));
		else if (ft_atof(line + 2) == y && \
		ft_atof(line + find_rep_symb(line, ' ', 2) + 1) == x)
			return (find_vt_id_part(fd, line, i));
		free(line);
		i++;
	}
	free(line);
	close(fd);
	return (0);
}

void		find_any_wall_in_sec(t_core *cr, t_wall *wall, int refid, int pr2)
{
	(void)pr2;
	if (wall->sectors[0].s == refid)
		cr->idcurr = wall->index;
	else if (wall->sectors[1].s == refid)
		cr->idcurr = wall->index;
}

void		record_sectors_partx(t_core *cr)
{
	cr->rs.sec = find_sec_list(cr, cr->rs.i);
	ft_strcat(cr->rs.txt, "\ns|");
	ft_strcat(cr->rs.txt, (cr->rs.tmp = ft_ftoa(cr->rs.sec->floor)));
	free(cr->rs.tmp);
	ft_strcat(cr->rs.txt, " ");
	ft_strcat(cr->rs.txt, (cr->rs.tmp = ft_ftoa(cr->rs.sec->ceiling)));
	free(cr->rs.tmp);
	ft_strcat(cr->rs.txt, "|");
	ft_strcat(cr->rs.wtx, "\nt|");
	ft_strcat(cr->rs.wtx, (cr->rs.tmp = ft_itoa(cr->rs.i)));
	free(cr->rs.tmp);
	ft_strcat(cr->rs.wtx, "|");
	ft_strcat(cr->rs.wtx, (cr->rs.tmp = \
	ft_itoa(find_sec_list(cr, cr->rs.i)->ftex)));
	free(cr->rs.tmp);
	ft_strcat(cr->rs.wtx, " ");
}

void		record_sectors_part3(t_core *cr)
{
	cr->rs.wtmp = find_by_index(cr, cr->rs.curr);
	ft_strcat(cr->rs.txt, \
	(cr->rs.tmp = ft_itoa(find_vt_id(cr, cr->rs.cw.x, cr->rs.cw.y))));
	if (cr->rs.wtmp->sectors[0].t != -1 || cr->rs.wtmp->sectors[1].t != -1 \
	|| cr->rs.sec->floor != ST_FLOOR_HIGHT || cr->rs.sec->ceiling \
	!= ST_CEIL_HIGHT || cr->rs.sec->illum != ST_ILLUMINATION || \
	cr->rs.sec->ftex != ST_FTEX || cr->rs.sec->ftex != ST_CTEX)
		cr->rs.doprint_wtx = 1;
	ft_strcat(cr->rs.wtx, cr->tms = ft_itoa(cr->rs.wtmp->sectors[0].s == \
	cr->rs.i ? cr->rs.wtmp->sectors[0].t : cr->rs.wtmp->sectors[1].t));
	free(cr->tms);
	free(cr->rs.tmp);
}
