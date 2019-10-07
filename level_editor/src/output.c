/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/19 21:06:10 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include <fcntl.h>
#include "stdlib.h"

static void		record_walls_part(t_core *cr, char *line, int fd, t_coord *p)
{
	ft_strcat(line, "v ");
	ft_strcat(line, cr->tms = ft_ftoa((float)p->y / cr->zoom * UNIT_SIZE));
	free(cr->tms);
	ft_strcat(line, " ");
	ft_strcat(line, cr->tms = ft_ftoa((float)p->x / cr->zoom * UNIT_SIZE));
	free(cr->tms);
	ft_strcat(line, " \n");
	ft_putstr_fd(line, fd);
	ft_strclr(line);
}

static void		record_walls(t_core *cr, int fd)
{
	t_wall	*wall;
	char	*line;

	wall = cr->wlist;
	if (!wall)
		return ;
	strnew_nullcheck(&line, STR_MED);
	while (wall)
	{
		if (check_vt_dups(cr, wall->p1.x, wall->p1.y) == 0)
		{
			record_walls_part(cr, line, fd, &wall->p1);
		}
		if (check_vt_dups(cr, wall->p2.x, wall->p2.y) == 0)
		{
			record_walls_part(cr, line, fd, &wall->p2);
		}
		wall = wall->next;
	}
	free(line);
}

static void		record_doors(t_core *cr, int fd)
{
	t_sec	*sec;
	char	*text;
	char	*tmp;

	strnew_nullcheck(&text, STR_SMALL);
	sec = *cr->slist;
	while (sec)
	{
		if (sec->isdoor)
		{
			ft_strcat(text, "\nd|");
			ft_strcat(text, tmp = ft_itoa(sec->id));
			free(tmp);
			ft_strcat(text, "|\n");
			ft_putstr_fd(text, fd);
		}
		sec = sec->next;
	}
	free(text);
}

static void		record_finish(t_core *cr, int fd)
{
	t_sec	*sec;
	char	*text;
	char	*tmp;

	strnew_nullcheck(&text, STR_SMALL);
	sec = *cr->slist;
	while (sec)
	{
		if (sec->isfinish)
		{
			ft_strcat(text, "\nf|");
			ft_strcat(text, tmp = ft_itoa(sec->id));
			free(tmp);
			ft_strcat(text, "|\n");
			ft_putstr_fd(text, fd);
		}
		sec = sec->next;
	}
	free(text);
}

void			save_map(t_core *cr)
{
	int		fd;

	if (!(fd = open(SAVEPATH, O_WRONLY | O_CREAT | O_TRUNC, 0777)))
		err_ex(2);
	record_walls(cr, fd);
	record_sectors(cr, fd);
	record_objects(cr, fd);
	record_doors(cr, fd);
	record_finish(cr, fd);
	record_player(cr, fd);
	close(fd);
}
