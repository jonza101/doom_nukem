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
// new game coords x 500 - 775 y 196 - 242
// color #ee9918
// outline 75 black 80 px opensans
// options coords x 540 - 745 y - 262 - 306
// quit coords x 587 - 700 y - 500 - 542

#define NONE_SELECTED 0
#define NEW_GAME_SELECTED 1
#define OPTIONS_SELECTED 2
#define QUIT_SELECTED 3

void ft_clean_array(t_mlx *mlx){
	int i = -1;
	while (++i < sizeof(mlx->whichMenuIsSelected)/4){
		mlx->whichMenuIsSelected[i] = 0;
	}
}

int ft_mouse_move(int x, int y, t_mlx *mlx){
	ft_clean_array(mlx);
	if ( (x > 500 && x < 775) && (y > 196 && y < 242) ){
		mlx->whichMenuIsSelected[NEW_GAME_SELECTED] = 1;
		mlx->menuIsDrawn[NEW_GAME_SELECTED] = 1;
		return 0;
	}
	if ( (x > 540 && x < 745) && (y > 262 && y < 306)){
		mlx->whichMenuIsSelected[OPTIONS_SELECTED] = 1;
		mlx->menuIsDrawn[OPTIONS_SELECTED] = 1;
		return 0;
	}
	if ( (x > 587 && x < 700) && (y > 500 && y < 542)){
		mlx->whichMenuIsSelected[QUIT_SELECTED] = 1;
		mlx->menuIsDrawn[QUIT_SELECTED] = 1;
		return 0;
	}
	// если ничего не подошло отображаем стандартное меню
	mlx->menuIsDrawn[NONE_SELECTED] = 1;
	mlx->whichMenuIsSelected[NONE_SELECTED] = 1;
	return 0;
}


int ft_mouse_press(int keycode, int x, int y, t_mlx *mlx)
{
	printf("MOUSE AT X: %d Y: %d\n",x , y);
	if (mlx->menuNeeded){
		if ( (x > 500 && x < 775) && (y > 196 && y < 242) ){
			mlx->menuNeeded = 0;
			return 0;
		}
		if ( (x > 587 && x < 700) && (y > 500 && y < 542))
			exit(0);
	}
	if (keycode == LEFT_CLICK && mlx->player->weapon_state == 0 && mlx->player->weapon->mag_ammo > 0)
		mlx->player->weapon_state = 1;
	if (keycode == LEFT_CLICK && !mlx->player->weapon->mag_ammo && mlx->player->weapon->ammo_count)
		mlx->hud_r = 1;
	if (keycode == RIGHT_CLICK && mlx->player->weapon_state == 0 && mlx->player->weapon->has_altfire && mlx->player->weapon->mag_ammo > 0)
		mlx->player->weapon_state = 2;
	if (keycode == RIGHT_CLICK && mlx->player->weapon->has_altfire && !mlx->player->weapon->mag_ammo && mlx->player->weapon->ammo_count)
		mlx->hud_r = 1;
	return (0);
}

int ft_mouse_release(int keycode, int x, int y, t_mlx *mlx)
{
	if (keycode == LEFT_CLICK && mlx->player->weapon_state == 1 && mlx->player->weapon == mlx->player->a_rifle)
	{
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