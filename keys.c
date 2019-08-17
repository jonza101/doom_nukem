/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:41:19 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/17 19:33:50 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_key_realese(int keycode, t_mlx *mlx)
{
	if (keycode == MAC_LEFT)
		mlx->player->left = 0;
	if (keycode == MAC_RIGHT)
		mlx->player->right = 0;
	if (keycode == MAC_UP)
		mlx->player->up = 0;
	if (keycode == MAC_DOWN)
		mlx->player->down = 0;

	if (keycode == MAC_SPACE)
		mlx->player->jump = 0;

	if (keycode == MAC_W)
		mlx->player->wsad[0] = 0;
	if (keycode == MAC_S)
		mlx->player->wsad[1] = 0;
	if (keycode == MAC_A)
		mlx->player->wsad[2] = 0;
	if (keycode == MAC_D)
		mlx->player->wsad[3] = 0;

	if (keycode == MAC_CTRL_R && mlx->player->weapon_state == 1 && mlx->player->weapon == mlx->player->a_rifle)
	{
		mlx->player->weapon_state = 0;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
	}
	if (keycode == MAC_SHIFT_R && mlx->player->weapon_state == 2 && mlx->player->weapon == mlx->player->revolver)
	{
		mlx->player->weapon_state = 0;
		mlx->altfire = 0;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
	}
	return (0);
}

int		ft_key_press(int keycode, t_mlx *mlx)
{
	// printf("%d\n", keycode);
	(keycode == MAC_ESC) ? exit(0) : 1;
	if (keycode == MAC_LEFT)
		mlx->player->left = 1;
	if (keycode == MAC_RIGHT)
		mlx->player->right = 1;
	if (keycode == MAC_UP)
		mlx->player->up = 1;
	if (keycode == MAC_DOWN)
		mlx->player->down = 1;
	if (keycode == MAC_CTRL_L)
	{
		if (mlx->crouching)
		{
			if (mlx->sect[mlx->player->sector]->ceiling >= mlx->player->pos->z + (EYE_H - CROUCH_H))
			{
				mlx->crouching = 0;
				mlx->falling = 1;
			}
		}
		else
		{
			mlx->crouching = 1;
			mlx->falling = 1;
		}
		
	}
	if (keycode == MAC_SPACE && mlx->ground && !mlx->crouching)
		mlx->player->jump = 1;

	if (keycode == MAC_W)
		mlx->player->wsad[0] = 1;
	if (keycode == MAC_S)
		mlx->player->wsad[1] = 1;
	if (keycode == MAC_A)
		mlx->player->wsad[2] = 1;
	if (keycode == MAC_D)
		mlx->player->wsad[3] = 1;

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

	if (keycode == MAC_DOT)
	{
		mlx->s = !mlx->s;
		printf("s %d\n", mlx->s);
	}

	// if (keycode == MAC_FIVE)
	// {
	// 	extern char **environ;
    //     int i;
    //     char *av[] = {"/bin/bash", "-c", "afplay click.mp3", NULL};
    //     i = fork();
    //     if (i == 0)
	// 	{
	// 		extern char **environ;
	// 		char *av[] = {"/bin/bash", "-c", "afplay click.mp3", NULL};
    //         execve("/bin/bash", av, environ);
	// 		exit(0);
	// 	}
	// }

	if (keycode == MAC_CTRL_R && mlx->player->weapon_state == 0)
	{
		mlx->player->weapon_state = 1;
		ft_shoot(mlx);
	}
	if (keycode == MAC_SHIFT_R && mlx->player->weapon_state == 0 && mlx->player->weapon->has_altfire)
		mlx->player->weapon_state = 2;

	if (keycode == MAC_ONE && mlx->player->weapon_state == 0)
	{
		mlx->player->weapon = mlx->player->revolver;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
	}
	if (keycode == MAC_TWO && mlx->player->weapon_state == 0)
	{
		mlx->player->weapon = mlx->player->shotgun;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
	}
	if (keycode == MAC_THREE && mlx->player->weapon_state == 0)
	{
		mlx->player->weapon = mlx->player->a_rifle;
		mlx->gun_fire_i = 0;
		mlx->gun_delay = 0;
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
	return (0);
}
