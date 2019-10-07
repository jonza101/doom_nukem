/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 20:01:46 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void				process_pts(t_core *cr, char *tmp, char **pts, int i)
{
	find_sec_list(cr, i)->floor = ft_atof(pts[1]);
	find_sec_list(cr, i)->ceiling = ft_atof(ft_strchr(pts[1], ' ') + 1);
	if (pts[4])
		find_sec_list(cr, i)->illum = ft_atof(pts[4]);
	ft_strcat(tmp, pts[2]);
	ft_strcat(tmp, " ");
	cr->tms = ft_strsub(tmp, 0, ft_strchr(tmp, ' ') - tmp);
	ft_strcat(tmp, cr->tms);
	free(cr->tms);
}

static void				process_pts2(t_core *cr, char *tmp, char **pts)
{
	ft_strclr(tmp);
	ft_strcat(tmp, pts[3]);
	ft_strcat(tmp, " ");
	cr->tms = ft_strsub(tmp, 0, ft_strchr(tmp, ' ') - tmp);
	ft_strcat(tmp, cr->tms);
	free(cr->tms);
}

static void				str_parcing(t_core *cr, int *i, char *tmp, char *line)
{
	char	**pts;
	char	**vtx;
	char	**por;

	pts = ft_strsplit(line, '|');
	process_pts(cr, tmp, pts, *i);
	vtx = ft_strsplit(tmp, ' ');
	process_pts2(cr, tmp, pts);
	por = ft_strsplit(tmp, ' ');
	ft_strclr(tmp);
	process_walls(cr, vtx, por, *i);
	ft_arrfree(&vtx, ft_arrlen(vtx));
	ft_arrfree(&por, ft_arrlen(por));
	ft_arrfree(&pts, ft_arrlen(pts));
}

static void				load_sectors(t_core *cr, int *i)
{
	char	*line;
	char	*tmp;
	int		fd;

	open_gamesave(&fd);
	strnew_nullcheck(&tmp, STR_LARGE);
	prepare_gnlstr(&cr->gnlstr[0]);
	while (gnl_struct(&cr->gnlstr[0], fd, &line) > 0)
	{
		if (line[0] == 's')
		{
			cr->sec_num++;
			if (*i == -1)
				*i = 0;
			add_sec_list(cr);
			str_parcing(cr, i, tmp, line);
			(*i)++;
		}
		free(line);
	}
	free(line);
	free(tmp);
	close(fd);
}

void					load_map(t_core *cr)
{
	int		i;

	i = -1;
	cr->sec_num = 0;
	while (cr->wlist)
		erase_by_id(cr, 0);
	load_sectors(cr, &i);
	load_sec_info(cr);
	while (*cr->olist)
		del_object(cr, 0);
	load_objects(cr);
	load_player(cr);
	iter_wall(cr, -1, -1, &count_sectors);
	iter_wall(cr, -1, -1, &redraw_color);
	load_doors(cr);
	load_finish(cr);
}
