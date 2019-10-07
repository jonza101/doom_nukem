/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sec_list3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:15:59 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

static void	print_sec_num_part(int i, t_wall *wall, int *am, t_coord *summ)
{
	while (wall)
	{
		if (wall->sectors[0].s == i || wall->sectors[1].s == i)
		{
			*am += 2;
			summ->x += (wall->p1.x + wall->p2.x);
			summ->y += (wall->p1.y + wall->p2.y);
		}
		wall = wall->next;
	}
}

void		print_sec_num(t_core *cr)
{
	t_wall		*wall;
	int			am;
	int			i;
	t_coord		summ;
	char		*txt;

	strnew_nullcheck(&txt, STR_SMALL);
	i = 0;
	while (i < cr->sec_num)
	{
		am = 0;
		summ.x = 0;
		summ.y = 0;
		wall = cr->wlist;
		print_sec_num_part(i, wall, &am, &summ);
		summ.x = (float)summ.x / am;
		summ.y = (float)summ.y / am;
		ft_strcat(txt, cr->tms = ft_itoa(i));
		free(cr->tms);
		mlx_string_put(cr->mlx, cr->win, summ.x + cr->offs.x, \
		summ.y + cr->offs.y, 0x00ffb5, txt);
		ft_strclr(txt);
		i++;
	}
	free(txt);
}

void		set_textures(t_core *cr, t_wall *wall, int texture, int secid)
{
	if (wall->index != cr->idcurr)
		return ;
	if (wall->sectors[0].s == secid)
		wall->sectors[0].t = texture;
	else if (wall->sectors[1].s == secid)
		wall->sectors[1].t = texture;
}

void		find_wall_by_xy(t_core *cr, t_coord inp1, t_coord inp2)
{
	t_wall	*wall;

	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		if (((inp1.x == wall->p1.x && inp1.y == wall->p1.y) && \
		(inp2.x == wall->p2.x && inp2.y == wall->p2.y)) || \
		((inp1.x == wall->p2.x && inp1.y == wall->p2.y) && \
		(inp2.x == wall->p1.x && inp2.y == wall->p1.y)))
		{
			cr->idcurr = wall->index;
			return ;
		}
		wall = wall->next;
	}
}
