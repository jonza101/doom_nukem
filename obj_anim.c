/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_anim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:12:17 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/10 19:18:12 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void	ft_obj_anim(t_obj_temp *obj)
{
	obj->del++;
	if (obj->del >= obj->delay)
	{
		obj->frame = obj->anim[obj->anim_i];
		obj->anim_i++;
		obj->del = 0;
		if (obj->anim_i >= obj->anim_n)
		{
			obj->anim_i = 0;
		}
	}
}
