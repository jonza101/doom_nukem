/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   soundeff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/08 14:06:17 by adoyle            #+#    #+#             */
/*   Updated: 2019/09/08 15:01:42 by adoyle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// void 	sound_eff(t_mlx *mlx)
// {
// 	t_bup *bup;
// 	t_obj *tmp;
// 	int rast;
// 	int i;

// 	bup = mlx->snd->chunks;
// 	tmp = mlx->obj;
// 	while (mlx->obj->next)
// 	{
// 		rast = mlx->obj->dist;
// 		if (rast < 0)
// 			rast = rast * (-1);
// 		if (rast <= 5)
// 		{
// 			if (mlx->obj->chan == -1)
// 				mlx->obj->chan = Mix_PlayChannel(-1, bup->fire, -1);
// 			else
// 			{
// 				if (rast <= 0)
// 					rast = 1;
// 				Mix_Volume(mlx->obj->chan, 128 / rast);
// 			}
// 		}
// 		else if (mlx->obj->chan >= 0)
// 		{
// 			Mix_HaltChannel(mlx->obj->chan);
// 			mlx->obj->chan = -1;
// 		}
// 		mlx->obj = mlx->obj->next;
// 	}
// 	mlx->obj = tmp;
// }