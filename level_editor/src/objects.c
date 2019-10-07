/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/09/24 21:17:01 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static int		count_obj(t_core *cr)
{
	t_obj	*obj;
	int		i;

	i = 0;
	obj = *cr->olist;
	while (obj)
	{
		obj = obj->next;
		i++;
	}
	return (i);
}

void			add_object(t_core *cr, int x, int y)
{
	t_obj	*obj;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		err_ex(0);
	obj->next = *cr->olist;
	obj->sec = 0;
	obj->fcoord.x = x;
	obj->fcoord.y = y;
	obj->type = DEFAULT_OBJ_TYPE;
	obj->id = count_obj(cr);
	obj->color = OBJECT_COLOR;
	*cr->olist = obj;
}

static void		load_new_object(t_core *cr, char **oarr)
{
	t_obj		*obj;

	if (!(obj = (t_obj *)malloc(sizeof(t_obj))))
		err_ex(0);
	obj->sec = ft_atoi(oarr[1]);
	obj->fcoord.x = ft_atof(oarr[2]) * cr->zoom / UNIT_SIZE;
	obj->fcoord.y = ft_atof(ft_strchr(oarr[2], ' ') + 1) \
									* cr->zoom / UNIT_SIZE;
	obj->type = ft_atoi(oarr[3]);
	obj->id = count_obj(cr);
	obj->color = OBJECT_COLOR;
	obj->next = *cr->olist;
	*cr->olist = obj;
}

void			load_objects(t_core *cr)
{
	char		**oarr;
	int			fd;
	char		*line;

	open_gamesave(&fd);
	prepare_gnlstr(&cr->gnlstr[4]);
	while (gnl_struct(&cr->gnlstr[4], fd, &line) > 0)
	{
		if (line[0] == 'o')
		{
			oarr = ft_strsplit(line, '|');
			load_new_object(cr, oarr);
			ft_arrfree(&oarr, ft_arrlen(oarr));
		}
		free(line);
	}
	free(line);
	close(fd);
	return ;
}
