/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_anim.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 19:12:17 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/20 15:13:42 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_wobj_anim(t_mlx *mlx, t_wobj *wobj)
{
	wobj->del++;
	if (wobj->del >= mlx->wobj_l[wobj->wobj_i]->delay)
	{
		wobj->frame = mlx->wobj_l[wobj->wobj_i]->anim[wobj->anim_i];
		wobj->anim_i++;
		wobj->del = 0;
		if (wobj->anim_i >= mlx->wobj_l[wobj->wobj_i]->anim_n)
		{
			wobj->anim_i = 0;
		}
	}
}

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
				if (obj->specs->obj_i == 6)
					obj->specs->obj_i = 8;
				else if (obj->specs->obj_i == 8)
				{
					obj->specs->obj_i = 7;
					obj->specs->expl_f = 0;
				}
			}
		}
	}
}
