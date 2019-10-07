/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_list4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:16:02 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void			find_w_id_part(t_core *cr, int *vt, t_coord *xy)
{
	int		fd;
	char	*line;
	int		i;

	open_gamesave(&fd);
	i = -1;
	prepare_gnlstr(&cr->gnlstr[10]);
	while (i < *vt)
	{
		if (gnl_struct(&cr->gnlstr[10], fd, &line) < 0)
			err_ex(1);
		if (i + 1 < *vt)
			free(line);
		i++;
	}
	xy->y = ft_atof(line + 2) * cr->zoom / UNIT_SIZE;
	xy->x = ft_atof(line + find_rep_symb(line, ' ', 2) + 1) * cr->zoom / \
															UNIT_SIZE;
	close(fd);
	free(line);
}

int					find_w_id(t_core *cr)
{
	t_coord	xy1;
	t_coord	xy2;

	find_w_id_part(cr, &cr->vt[0], &xy1);
	find_w_id_part(cr, &cr->vt[1], &xy2);
	find_wall_by_xy(cr, xy1, xy2);
	return (cr->idcurr);
}
