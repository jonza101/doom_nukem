/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_anim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:12:17 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/11 20:08:09 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"


void	ft_obj_anim(t_mlx *mlx, t_obj *obj)
{
	obj->specs->del++;
	if (obj->specs->del >= mlx->obj_l[obj->specs->obj_i]->delay)
	{
		obj->specs->frame = mlx->obj_l[obj->specs->obj_i]->anim[obj->specs->anim_i];
		obj->specs->anim_i++;
		obj->specs->del = 0;
		if (obj->specs->anim_i >= mlx->obj_l[obj->specs->obj_i]->anim_n)
		{
			obj->specs->anim_i = 0;
			if (obj->specs->expl_f == 1)
			{
				obj->specs->obj_i = 7;
				obj->specs->expl_f = 0;
			}
		}
	}
}
