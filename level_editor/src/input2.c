/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:14:57 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void			calc_inp(t_core *cr, int num, t_coord *inp)
{
	int			fd;
	char		*line;
	int			j;
	char		**v;

	open_gamesave(&fd);
	j = 0;
	prepare_gnlstr(&cr->gnlstr[1]);
	while (j++ <= num)
	{
		if (gnl_struct(&cr->gnlstr[1], fd, &line) <= 0)
			err_ex(1);
		if (j < num + 1)
			free(line);
	}
	v = ft_strsplit(line, ' ');
	free(line);
	inp->x = ft_atof(v[2]) * cr->zoom / UNIT_SIZE;
	inp->y = ft_atof(v[1]) * cr->zoom / UNIT_SIZE;
	ft_arrfree(&v, ft_arrlen(v));
	close(fd);
}

void				process_walls(t_core *cr, char **pts, char **prt, int snum)
{
	t_coord		inp1;
	t_coord		inp2;
	int			i;
	int			num;

	i = 0;
	while (pts[i + 1])
	{
		num = ft_atoi(pts[i]);
		calc_inp(cr, num, &inp1);
		num = ft_atoi(pts[i + 1]);
		calc_inp(cr, num, &inp2);
		if (check_dups(cr, inp1, inp2) == 0)
		{
			cr->vs.mem_x = inp1.x;
			cr->vs.mem_y = inp1.y;
			cr->vs.x1 = inp2.x;
			cr->vs.y1 = inp2.y;
			cr->mpsw = ft_atoi(prt[i + 1]) >= 0 ? 1 : cr->mpsw;
			add_wall(cr);
		}
		set_sectors(cr, inp1, inp2, snum);
		i++;
	}
}
