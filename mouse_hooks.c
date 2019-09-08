/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousePressAndReleasehooks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 22:36:29 by lsandor-          #+#    #+#             */
/*   Updated: 2019/08/29 22:39:48 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int ft_mouse_press(int keycode, int x, int y, t_mlx *mlx)
{
	if (keycode == LEFT_CLICK && mlx->player->weapon_state == 0 && mlx->player->weapon->mag_ammo > 0)
	{
		mlx->player->weapon_state = 1;
	}
	if (keycode == LEFT_CLICK && !mlx->player->weapon->mag_ammo && mlx->player->weapon->ammo_count)
		mlx->hud_r = 1;
	if (keycode == RIGHT_CLICK && mlx->player->weapon_state == 0 && mlx->player->weapon->has_altfire && mlx->player->weapon->mag_ammo > 0)
	{
		mlx->player->weapon_state = 2;
	}
	if (keycode == RIGHT_CLICK && mlx->player->weapon->has_altfire && !mlx->player->weapon->mag_ammo && mlx->player->weapon->ammo_count)
		mlx->hud_r = 1;
	return (0);
}

int ft_mouse_release(int keycode, int x, int y, t_mlx *mlx)
{
	if (keycode == LEFT_CLICK && mlx->player->weapon_state == 1 && mlx->player->weapon == mlx->player->a_rifle)
	{
		if (mlx->player->weapon == mlx->player->a_rifle)
			Mix_HaltChannel(15);
		mlx->player->weapon_state = 0;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;
	}
	if (keycode == RIGHT_CLICK && mlx->player->weapon_state == 2 && mlx->player->weapon == mlx->player->revolver)
	{
		mlx->player->weapon_state = 0;
		mlx->altfire = 0;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;
	}
	return (0);
}