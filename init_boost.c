/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_boost.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/26 19:02:51 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/13 21:03:30 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_boost(t_mlx *mlx)
{
	(!(mlx->boost[0] = (t_boost*)malloc(sizeof(t_boost)))) ? ft_mem_error() : 1;
	mlx->boost[0]->boost_i = 16;
	mlx->boost[0]->frame = mlx->obj_l[16]->anim[0];
	mlx->boost[0]->del = 0;
	mlx->boost[0]->anim_i = 0;

	(!(mlx->boost[1] = (t_boost*)malloc(sizeof(t_boost)))) ? ft_mem_error() : 1;
	mlx->boost[1]->boost_i = 17;
	mlx->boost[1]->frame = mlx->obj_l[17]->anim[0];
	mlx->boost[1]->del = 0;
	mlx->boost[1]->anim_i = 0;
}
