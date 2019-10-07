/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:55:20 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/20 19:51:51 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void			prepare_gnlstr_init(t_core *cr)
{
	int	i;

	i = FD_STORAGE_NUM;
	while (--i > -1)
		cr->gnlstr[i] = NULL;
}

void				init(t_core *cr)
{
	if (!(cr->mlx = mlx_init()))
		err_ex(0);
	if (!(cr->win = mlx_new_window(cr->mlx, WIN_WIDTH, WIN_HIGHT, "Editor")))
		err_ex(0);
	cr->wlist = NULL;
	if (!(cr->olist = (t_obj **)malloc(sizeof(t_obj *))))
		err_ex(0);
	*cr->olist = NULL;
	if (!(cr->slist = (t_sec **)malloc(sizeof(t_sec *))))
		err_ex(0);
	*cr->slist = NULL;
	load_gui(cr);
	cr->inst_func = draw_wall;
	cr->highlight = 1;
	cr->offs.x = WIN_WIDTH / 2;
	cr->offs.y = WIN_HIGHT / 2;
	cr->test = -1;
	cr->zoom = 20;
	cr->searchtype = 1;
	cr->show_obj_num = 1;
	prepare_gnlstr_init(cr);
	img_new(cr);
	redraw(cr);
}
