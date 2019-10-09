/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/09 16:39:23 by jsteuber         ###   ########.fr       */
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
	prepare_gnlstr(&cr->gnlstr[11]);
	while (gnl_struct(&cr->gnlstr[11], fd, &line) > 0)
	{
		if (ft_strstr(line, "||"))
		{
			ft_putstr("Error: invalid map\n");
			return (1);
		}
		free(line);
	}
	free(line);
	close(fd);
	return (0);
}
