/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 20:53:21 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"
#include <fcntl.h>

void		err_ex(int pr)
{
	if (pr == 0)
		ft_putstr("Error: memory allocation failure\n");
	else if (pr == 1)
		ft_putstr("Error: unexpected GNL data\n");
	else if (pr == 2)
		ft_putstr("Error: can't open file\n");
	exit(1);
}

void		open_gamesave(int *fd)
{
	if (!(*fd = open(SAVEPATH, O_RDONLY)))
		err_ex(2);
}

int			check_bounds(int x, int y)
{
	if (x >= WIN_WIDTH || y >= WIN_HIGHT || \
		x < 0 || y < 0)
		return (1);
	return (0);
}

int			min(int a, int b)
{
	return (a < b ? a : b);
}

int			max(int a, int b)
{
	return (a > b ? a : b);
}
