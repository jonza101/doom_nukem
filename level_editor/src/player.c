/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:12:14 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

void			draw_player(t_core *cr)
{
	t_coord		xy;
	t_coord		ab;

	ab.x = PLAYER_SIZE;
	ab.y = PLAYER_SIZE;
	xy.x = cr->player.fcoord.x - PLAYER_SIZE / 2;
	xy.y = cr->player.fcoord.y - PLAYER_SIZE / 2;
	draw_rectangle_img_pxl(cr, xy, ab, PLAYER_COLOR);
}

void			record_player(t_core *cr, int fd)
{
	char	*text;
	char	*tmp;

	ft_putstr_fd("\n", fd);
	strnew_nullcheck(&text, STR_MED);
	spot_sector_around(cr, &cr->player);
	ft_strcat(text, "p|");
	ft_strcat(text, tmp = ft_ftoa(cr->player.fcoord.x / cr->zoom * UNIT_SIZE));
	free(tmp);
	ft_strcat(text, " ");
	ft_strcat(text, tmp = ft_ftoa(cr->player.fcoord.y / cr->zoom * UNIT_SIZE));
	free(tmp);
	ft_strcat(text, "|");
	ft_strcat(text, tmp = ft_itoa(cr->player.sec));
	free(tmp);
	ft_strcat(text, "|");
	ft_strcat(text, tmp = ft_itoa(cr->player.angle));
	free(tmp);
	ft_strcat(text, "|\n");
	ft_putstr_fd(text, fd);
	free(text);
}

void			load_player(t_core *cr)
{
	char		**parr;
	int			fd;
	char		*line;

	open_gamesave(&fd);
	prepare_gnlstr(&cr->gnlstr[7]);
	while (gnl_struct(&cr->gnlstr[7], fd, &line) > 0)
	{
		if (line[0] == 'p')
		{
			parr = ft_strsplit(line, '|');
			cr->player.fcoord.x = ft_atof(parr[1]) * cr->zoom / UNIT_SIZE;
			cr->player.fcoord.y = ft_atof(ft_strchr(parr[1], ' ') + 1) * \
														cr->zoom / UNIT_SIZE;
			cr->player.sec = ft_atoi(parr[2]);
			cr->player.angle = ft_atof(parr[3]);
			cr->player.isplayer = 1;
			ft_arrfree(&parr, ft_arrlen(parr));
			end_reading(&line, fd);
			return ;
		}
		free(line);
	}
	end_reading(&line, fd);
	return ;
}
