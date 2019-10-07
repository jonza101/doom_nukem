/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 19:51:07 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void			find_sec_in_save_part(t_core *cr, char ***pts, \
char *line)
{
	char	**tmp;

	tmp = ft_strsplit(line, '|');
	cr->tms = ft_strjoin(" ", tmp[2]);
	free(tmp[2]);
	tmp[2] = ft_strdup(cr->tms);
	free(cr->tms);
	cr->tms = ft_strjoin(ft_strrchr(tmp[2], ' '), tmp[2]);
	free(tmp[2]);
	tmp[2] = ft_strdup(cr->tms);
	free(cr->tms);
	*pts = ft_strsplit(tmp[2], ' ');
	ft_arrfree(&tmp, ft_arrlen(tmp));
	free(line);
}

static char			**find_sec_in_save(t_core *cr, int secid)
{
	int		fd;
	char	*line;
	char	**pts;
	int		i;

	i = -1;
	open_gamesave(&fd);
	prepare_gnlstr(&cr->gnlstr[8]);
	while (gnl_struct(&cr->gnlstr[8], fd, &line) > 0)
	{
		if (line[0] == 's')
		{
			i++;
			if (i == secid)
			{
				find_sec_in_save_part(cr, &pts, line);
				close(fd);
				return (pts);
			}
		}
		free(line);
	}
	free(line);
	close(fd);
	return (NULL);
}

static void			load_textures(t_core *cr, char *str, int secid)
{
	char	**pts;
	char	**sts;
	int		i;

	i = 0;
	pts = ft_strsplit(str, ' ');
	sts = find_sec_in_save(cr, secid);
	while (pts[i])
	{
		cr->vt[0] = ft_atoi(sts[i]);
		cr->vt[1] = ft_atoi(sts[i + 1]);
		find_w_id(cr);
		iter_wall(cr, ft_atoi(pts[i]), secid, &set_textures);
		i++;
	}
	ft_arrfree(&sts, ft_arrlen(sts));
	ft_arrfree(&pts, ft_arrlen(pts));
}

static void			load_sec_info_part(t_core *cr, \
char *line)
{
	char	**pts;
	t_sec	*sec;

	pts = ft_strsplit(line, '|');
	sec = find_sec_list(cr, ft_atoi(pts[1]));
	sec->ftex = ft_atoi(pts[2]);
	if (ft_strncmp(ft_strchr(pts[2], ' ') + 1, "sky", 3) == 0)
		sec->ctex = SKY;
	else
		sec->ctex = ft_atoi(ft_strchr(pts[2], ' '));
	load_textures(cr, pts[3], ft_atoi(pts[1]));
	ft_arrfree(&pts, ft_arrlen(pts));
}

void				load_sec_info(t_core *cr)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	open_gamesave(&fd);
	prepare_gnlstr(&cr->gnlstr[9]);
	while (gnl_struct(&cr->gnlstr[9], fd, &line) > 0)
	{
		if (line[0] == 't')
			load_sec_info_part(cr, line);
		free(line);
	}
	close(fd);
	free(line);
}
