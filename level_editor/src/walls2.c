/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 15:54:47 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:16:35 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_wall			*get_last_wall(t_core *cr)
{
	t_wall		*wall;

	wall = cr->wlist;
	while (wall->next)
		wall = wall->next;
	return (wall);
}

void			iter_wall(t_core *cr, int pr1, int pr2, \
void (*f)(t_core *, t_wall *, int, int))
{
	t_wall		*wall;

	wall = cr->wlist;
	if (!wall)
		return ;
	while (wall)
	{
		(*f)(cr, wall, pr1, pr2);
		wall = wall->next;
	}
}

t_wall			*find_by_index(t_core *cr, int index)
{
	t_wall		*wall;

	wall = cr->wlist;
	while (wall && index--)
		wall = wall->next;
	return (wall);
}
