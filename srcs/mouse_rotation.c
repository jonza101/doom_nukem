/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:17:43 by lsandor-          #+#    #+#             */
/*   Updated: 2019/09/24 21:00:42 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void ftLookRight(t_mlx *mlx)
{
	mlx->player->angle += 0.06f;
	mlx->player->sin_angle = sinf(mlx->player->angle);
	mlx->player->cos_angle = cosf(mlx->player->angle);
	mlx->sky_offset_x += 40;
}

void ftLookLeft(t_mlx *mlx)
{
	mlx->player->angle -= 0.06f;
	mlx->player->sin_angle = sinf(mlx->player->angle);
	mlx->player->cos_angle = cosf(mlx->player->angle);
	mlx->sky_offset_x -= 40;
}

void ftLookUp(t_mlx *mlx)
{
	mlx->player->yaw += 0.2f;
	if (mlx->player->yaw < 5.0f)
		mlx->sky_offset_y += 28;
	mlx->player->yaw = ft_clamp(mlx->player->yaw, -5, 5);
}

void ftLookDown(t_mlx *mlx)
{
	mlx->player->yaw -= 0.2f;
	if (mlx->player->yaw > -5.0f)
		mlx->sky_offset_y -= 28;
	mlx->player->yaw = ft_clamp(mlx->player->yaw, -5, 5);
}