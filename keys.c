/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:41:19 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/12 20:47:12 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_key_realese(int keycode, t_mlx *mlx)
{
	keycode == MAC_LEFT ? mlx->player->left = 0 : 0;
	keycode == MAC_RIGHT ? mlx->player->right = 0 : 0;
	keycode == MAC_UP ? mlx->player->up = 0 : 0;
	keycode == MAC_DOWN ? mlx->player->down = 0 : 0;
	if (keycode == MAC_SPACE && !mlx->player->jetpack)
		mlx->player->jump = 0;
	keycode == MAC_SHIFT_L ? mlx->player->shift = 0 : 0;
	if (keycode == MAC_SPACE && mlx->player->jetpack)
		mlx->player->j_up = 0;
	if (keycode == MAC_CTRL_L && mlx->player->jetpack)
		mlx->player->j_down = 0;
	keycode == MAC_W ? mlx->player->wsad[0] = 0 : 0;
	keycode == MAC_S ? mlx->player->wsad[1] = 0 : 0;
	keycode == MAC_A ? mlx->player->wsad[2] = 0 : 0;
	keycode == MAC_D ? mlx->player->wsad[3] = 0 : 0;
	if (keycode == MAC_CTRL_R && mlx->player->weapon_state == 1 && mlx->player->weapon == mlx->player->a_rifle)
	{
		mlx->player->weapon_state = 0;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;
	}
	if (keycode == MAC_SHIFT_R && mlx->player->weapon_state == 2 && mlx->player->weapon == mlx->player->revolver)
	{
		mlx->player->weapon_state = 0;
		mlx->altfire = 0;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;
	}

	if (keycode == MAC_E)
		ft_interact(mlx);
	return (0);
}

int		ft_key_press(int keycode, t_mlx *mlx)
{
	 //printf("%d\n", keycode);
	keycode == MAC_ESC ? exit(0) : 1;
	keycode == MAC_LEFT ? mlx->player->left = 1 : 0;
	keycode == MAC_RIGHT ? mlx->player->right = 1 : 0;
	keycode == (MAC_UP) ? mlx->player->up = 1 : 0;
	keycode == (MAC_DOWN) ? mlx->player->down = 1 : 0;
	if (keycode == MAC_CTRL_L)
	{
		if (mlx->crouching && !mlx->player->jetpack)
		{
			if (mlx->sect[mlx->player->sector]->ceiling >= mlx->player->pos->z + (EYE_H - CROUCH_H))
			{
				mlx->crouching = 0;
				mlx->falling = 1;
			}
		}
		else if (!mlx->crouching && !mlx->player->jetpack)
		{
			mlx->crouching = 1;
			mlx->falling = 1;
		}
	}
	if (keycode == MAC_SPACE && mlx->ground && !mlx->crouching)
		mlx->player->jump = 1;

	if (keycode == MAC_SHIFT_L && !mlx->crouching)
		mlx->player->shift = 1;

	keycode == MAC_W ? mlx->player->wsad[0] = 1 : 0;
	keycode == MAC_S ? mlx->player->wsad[1] = 1 : 0;
	keycode == MAC_A ? mlx->player->wsad[2] = 1 : 0;
	keycode == MAC_D ? mlx->player->wsad[3] = 1 : 0;

	if (keycode == MAC_NUM_PLUS)
	{
		mlx->u1 += 32;
		printf("u1 %d\n", mlx->u1);
	}
	if (keycode == MAC_NUM_MINUS)
	{
		mlx->u1 -= 32;
		printf("u1 %d\n", mlx->u1);
	}
	if (keycode == MAC_PLUS)
	{
		mlx->u0 += 32;
		printf("u0 %d\n", mlx->u0);
	}
	if (keycode == MAC_MINUS)
	{
		mlx->u0 -= 32;
		printf("u0 %d\n", mlx->u0);
	}

	if (keycode == MAC_CTRL_R && mlx->player->weapon_state == 0 && mlx->player->weapon->mag_ammo > 0)
		mlx->player->weapon_state = 1;

	if (keycode == MAC_SHIFT_R && mlx->player->weapon_state == 0 && mlx->player->weapon->has_altfire && mlx->player->weapon->mag_ammo > 0)
		mlx->player->weapon_state = 2;

	if (keycode == MAC_R && mlx->player->weapon_state == 0 && mlx->player->weapon->mag_ammo < mlx->player->weapon->mag_ammo_count && mlx->player->weapon->ammo_count > 0 && mlx->player->weapon != mlx->player->shotgun)
	{
		if (mlx->player->weapon->mag_ammo == 0 && mlx->player->weapon->has_reload_ptt)
			mlx->player->weapon_state = 4;
		else if (mlx->player->weapon->mag_ammo < mlx->player->weapon->mag_ammo_count && mlx->player->weapon->mag_ammo >= 0)
			mlx->player->weapon_state = 3;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;
	}

	if (keycode == MAC_CTRL_R && !mlx->player->weapon->mag_ammo && mlx->player->weapon->ammo_count && !mlx->menu)
		mlx->hud_r = 1;
	if (keycode == MAC_SHIFT_R && mlx->player->weapon->has_altfire && !mlx->player->weapon->mag_ammo && mlx->player->weapon->ammo_count && !mlx->menu)
		mlx->hud_r = 1;

	if (keycode == MAC_ONE && mlx->player->weapon != mlx->player->revolver && mlx->player->weapon_state == 0)
	{
		mlx->player->weapon = mlx->player->revolver;
		mlx->fire_range = FIRE_RANGE;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;

		mlx->hud_r = 0;
		mlx->r_i = 0;
		mlx->r_i_d = 0;
	}
	if (keycode == MAC_TWO && mlx->player->weapon != mlx->player->shotgun && mlx->player->weapon_state == 0)
	{
		mlx->player->weapon = mlx->player->shotgun;
		mlx->fire_range = FIRE_RANGE;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;

		mlx->hud_r = 0;
		mlx->r_i = 0;
		mlx->r_i_d = 0;
	}
	if (keycode == MAC_THREE && mlx->player->weapon != mlx->player->a_rifle && mlx->player->weapon_state == 0)
	{
		mlx->player->weapon = mlx->player->a_rifle;
		mlx->fire_range = FIRE_RANGE;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
		mlx->altfire = 0;

		mlx->hud_r = 0;
		mlx->r_i = 0;
		mlx->r_i_d = 0;
	}

	if (keycode == MAC_O)
	{
		mlx->sect[mlx->player->sector]->ceiling -= 0.5f;
		printf("ceil %f\n", mlx->sect[mlx->player->sector]->ceiling);
	}
	if (keycode == MAC_P)
	{
		mlx->sect[mlx->player->sector]->ceiling += 0.5f;
		printf("ceil %f\n", mlx->sect[mlx->player->sector]->ceiling);
	}
	if (keycode == MAC_L)
	{
		mlx->sect[mlx->player->sector]->floor -= 0.5f;
		printf("floor %f\n", mlx->sect[mlx->player->sector]->floor);
	}
	if (keycode == MAC_SEMICOLON)
	{
		mlx->sect[mlx->player->sector]->floor += 0.5f;
		printf("floor %f\n", mlx->sect[mlx->player->sector]->floor);
	}

	if (keycode == MAC_NUM_ONE && mlx->player->hp > 1)
		mlx->player->hp--;
	if (keycode == MAC_NUM_TWO && mlx->player->hp < mlx->player->max_hp)
		mlx->player->hp++;

	if (keycode == MAC_J)
	{
		mlx->player->jetpack = !mlx->player->jetpack;
		mlx->falling = 1;
	}
	if (keycode == MAC_SPACE && mlx->player->jetpack)
		mlx->player->j_up = 1;
	if (keycode == MAC_CTRL_L && mlx->player->jetpack)
		mlx->player->j_down = 1;

	if (keycode == MAC_DOT)
		mlx->s = !mlx->s;

	if (keycode == MAC_UP && mlx->menu)
		mlx->button_i = (mlx->button_i - 1 < 0) ? 1 : 0;
	if (keycode == MAC_DOWN && mlx->menu)
		mlx->button_i = (mlx->button_i + 1 > 1) ? 0 : 1;
	if (keycode == MAC_ENTER && mlx->menu)
		(mlx->button_i == 0) ? ft_play(mlx) : ft_close(1);

	return (0);
}
