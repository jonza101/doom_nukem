/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/09 16:58:14 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

void	valid_illum_val(float *val)
{
	*val = *val < 0.25 ? 0.25 : *val;
	*val = *val > 1 ? 1 : *val;
}

int		validate_map(t_core *cr)
{
	int		fd;
	char	*line;

	open_gamesave(&fd);
	if (read(fd, NULL, 0) < 0)
	{
		ft_putstr("Error: can't read from file\n");
		close(fd);
		return (1);
	}
	prepare_gnlstr(&cr->gnlstr[11]);
	while (gnl_struct(&cr->gnlstr[11], fd, &line) > 0)
	{
		if (ft_strstr(line, "||"))
		{
			ft_putstr("Error: invalid map\n");
			end_reading(&line, fd);
			return (1);
		}
		free(line);
	}
	end_reading(&line, fd);
	return (0);
}
