/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:35 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void	choose_direction_p2(t_core *cr, t_fcoord *cw, t_wall *start)
{
	int			side;

	if ((side = (start->p1.x - start->p2.x) * (cr->p3.y - start->p2.y) - \
	(start->p1.y - start->p2.y) * (cr->p3.x - start->p2.x)) > 0)
	{
		cw->x = start->p1.x / cr->zoom * UNIT_SIZE;
		cw->y = start->p1.y / cr->zoom * UNIT_SIZE;
	}
	else if (side < 0)
	{
		cw->x = start->p2.x / cr->zoom * UNIT_SIZE;
		cw->y = start->p2.y / cr->zoom * UNIT_SIZE;
	}
}

void		choose_direction(t_core *cr, t_fcoord *cw, t_wall *start, \
int secid)
{
	t_wall		*wall;

	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		if (wall->p1.x == start->p1.x && wall->p1.y == start->p1.y && \
		wall->index != start->index && (wall->sectors[0].s == secid || \
		wall->sectors[1].s == secid))
		{
			cr->p3 = wall->p2;
			break ;
		}
		else if (wall->p2.x == start->p1.x && wall->p2.y == start->p1.y && \
		wall->index != start->index && (wall->sectors[0].s == secid || \
		wall->sectors[1].s == secid))
		{
			cr->p3 = wall->p1;
			break ;
		}
		wall = wall->next;
	}
	choose_direction_p2(cr, cw, start);
}

static void	find_next_wall_part(t_core *cr, t_fcoord *cw, t_coord *p)
{
	cw->x = p->x / cr->zoom * UNIT_SIZE;
	cw->y = p->y / cr->zoom * UNIT_SIZE;
}

int			find_next_wall(t_core *cr, t_fcoord *cw, int prev, int secid)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return (-1);
	while (wall)
	{
		if (wall->p1.x == cw->x * cr->zoom / UNIT_SIZE && \
		wall->p1.y == cw->y * cr->zoom / UNIT_SIZE && wall->index != prev && \
			(wall->sectors[0].s == secid || wall->sectors[1].s == secid))
		{
			find_next_wall_part(cr, cw, &wall->p2);
			return (wall->index);
		}
		else if (wall->p2.x == cw->x * cr->zoom / UNIT_SIZE && \
		wall->p2.y == cw->y * cr->zoom / UNIT_SIZE && wall->index != prev && \
			(wall->sectors[0].s == secid || wall->sectors[1].s == secid))
		{
			find_next_wall_part(cr, cw, &wall->p1);
			return (wall->index);
		}
		wall = wall->next;
	}
	return (-1);
}

int			check_vt_dups(t_core *cr, float x, float y)
{
	int		fd;
	char	*line;

	open_gamesave(&fd);
	prepare_gnlstr(&cr->gnlstr[6]);
	while (gnl_struct(&cr->gnlstr[6], fd, &line) > 0)
	{
		if ((int)(ft_atof(line + 2) * cr->zoom / UNIT_SIZE) == y && \
		(int)(ft_atof(line + find_rep_symb(line, ' ', 2) + 1) * \
		cr->zoom / UNIT_SIZE) == x)
		{
			free(line);
			close(fd);
			return (1);
		}
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
