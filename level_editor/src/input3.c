/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:01 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

int					find_rep_symb(char *line, char symb, int num)
{
	char	*p;

	p = line;
	while (num--)
	{
		p = ft_strchr(p + 1, symb);
	}
	return (p - line);
}

int					check_dups(t_core *cr, t_coord inp1, t_coord inp2)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return (0);
	while (wall)
	{
		if (((inp1.x == wall->p1.x && inp1.y == wall->p1.y) && \
		(inp2.x == wall->p2.x && inp2.y == wall->p2.y)) || \
		((inp1.x == wall->p2.x && inp1.y == wall->p2.y) && \
		(inp2.x == wall->p1.x && inp2.y == wall->p1.y)))
			return (1);
		wall = wall->next;
	}
	return (0);
}

void				set_sectors(t_core *cr, t_coord inp1, t_coord inp2, int sn)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		if (((inp1.x == wall->p1.x && inp1.y == wall->p1.y) && \
		(inp2.x == wall->p2.x && inp2.y == wall->p2.y)) || \
		((inp1.x == wall->p2.x && inp1.y == wall->p2.y) && \
		(inp2.x == wall->p1.x && inp2.y == wall->p1.y)))
		{
			if (wall->sectors[0].s == -1)
				wall->sectors[0].s = sn;
			else if (wall->sectors[1].s == -1)
				wall->sectors[1].s = sn;
		}
		wall = wall->next;
	}
}

void				load_doors(t_core *cr)
{
	int			fd;
	char		*line;

	open_gamesave(&fd);
	prepare_gnlstr(&cr->gnlstr[2]);
	while (gnl_struct(&cr->gnlstr[2], fd, &line) > 0)
	{
		if (line[0] == 'd')
			find_sec_list(cr, ft_atoi(line + 2))->isdoor = 1;
		free(line);
	}
	close(fd);
	free(line);
}

void				load_finish(t_core *cr)
{
	int			fd;
	char		*line;

	open_gamesave(&fd);
	prepare_gnlstr(&cr->gnlstr[3]);
	while (gnl_struct(&cr->gnlstr[3], fd, &line) > 0)
	{
		if (line[0] == 'f')
			find_sec_list(cr, ft_atoi(line + 2))->isfinish = 1;
		free(line);
	}
	close(fd);
	free(line);
}
