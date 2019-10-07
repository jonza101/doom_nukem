/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:08 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

int		hooks(t_core *cr)
{
	mlx_hook(cr->win, 4, 1, mouse_press, cr);
	mlx_hook(cr->win, 5, 1, mouse_release, cr);
	mlx_hook(cr->win, 6, 1, mouse_move, cr);
	mlx_hook(cr->win, 2, 1, key_action, cr);
	mlx_hook(cr->win, 3, 0, key_release, cr);
	mlx_hook(cr->win, 17, 1, red_button, cr);
	mlx_loop(cr->mlx);
	return (0);
}

int		main(int argc, char **argv)
{
	t_core		*cr;

	if (!(cr = (t_core *)malloc(sizeof(t_core))))
		err_ex(0);
	ft_memset(cr, 0, sizeof(t_core));
	init(cr);
	hooks(cr);
	(void)argc;
	(void)argv;
	return (0);
}
