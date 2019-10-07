/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:21 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

void		draw_objects_text(t_core *cr)
{
	t_obj		*obj;
	t_coord		xy;
	char		*txt;

	if (cr->show_obj_num < 0)
		return ;
	obj = *cr->olist;
	while (obj)
	{
		xy.x = obj->fcoord.x - OBJECT_SIZE / 2 + cr->offs.x;
		xy.y = obj->fcoord.y - OBJECT_SIZE / 2 + cr->offs.y;
		strnew_nullcheck(&txt, STR_SMALL);
		ft_strcpy(txt, (cr->tms = ft_itoa(obj->type)));
		free(cr->tms);
		mlx_string_put(cr->mlx, cr->win, xy.x, xy.y, 0xffffff, txt);
		free(txt);
		obj = obj->next;
	}
}

void		draw_objects(t_core *cr)
{
	t_obj		*obj;
	t_coord		xy;
	t_coord		ab;

	obj = *cr->olist;
	ab.x = OBJECT_SIZE;
	ab.y = OBJECT_SIZE;
	while (obj)
	{
		xy.x = obj->fcoord.x - OBJECT_SIZE / 2;
		xy.y = obj->fcoord.y - OBJECT_SIZE / 2;
		draw_rectangle_img_pxl(cr, xy, ab, obj->color);
		obj = obj->next;
	}
}

static void	record_new_object(t_core *cr, int fd, char *text, t_obj *obj)
{
	ft_strcat(text, "o|");
	ft_strcat(text, cr->tms = ft_itoa(obj->sec));
	free(cr->tms);
	ft_strcat(text, "|");
	ft_strcat(text, cr->tms = ft_ftoa(obj->fcoord.x / cr->zoom * UNIT_SIZE));
	free(cr->tms);
	ft_strcat(text, " ");
	ft_strcat(text, cr->tms = ft_ftoa(obj->fcoord.y / cr->zoom * UNIT_SIZE));
	free(cr->tms);
	ft_strcat(text, "|");
	ft_strcat(text, cr->tms = ft_itoa(obj->type));
	free(cr->tms);
	ft_strcat(text, "|\n");
	ft_putstr_fd(text, fd);
	ft_strclr(text);
}

void		record_objects(t_core *cr, int fd)
{
	char	*text;
	t_obj	*obj;

	obj = *cr->olist;
	strnew_nullcheck(&text, STR_MED);
	ft_putstr_fd("\n", fd);
	while (obj)
	{
		spot_sector_around(cr, obj);
		record_new_object(cr, fd, text, obj);
		obj = obj->next;
	}
	free(text);
}

void		restore_obj_color(t_core *cr)
{
	t_obj	*obj;

	obj = *cr->olist;
	while (obj)
	{
		obj->color = OBJECT_COLOR;
		obj = obj->next;
	}
}
