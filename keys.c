/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:41:19 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/28 19:04:37 by zjeyne-l         ###   ########.fr       */
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
		mlx->c1 += 32;
		printf("u1 %d\n", mlx->u1);
	}
	if (keycode == MAC_NUM_MINUS && mlx->u1 > 128)
	{
		mlx->u1 -= 32;
		mlx->c1 -= 32;
		printf("u1 %d\n", mlx->u1);
	}
	if (keycode == MAC_EQUAL)
	{
		mlx->u0 += 32;
		mlx->c0 += 32;
		printf("u0 %d\n", mlx->u0);
	}
	if (keycode == MAC_MINUS)
	{
		mlx->u0 -= 32;
		mlx->c0 -= 32;
		printf("u0 %d\n", mlx->u0);
	}

	if (keycode == MAC_DOT)
	{
		mlx->s = !mlx->s;
		printf("s %d\n", mlx->s);
	}

	if (keycode == MAC_NUM_ONE)
	{
		mlx->del--;
		printf("%d\n", mlx->del);
	}
	if (keycode == MAC_NUM_TWO)
	{
		mlx->del++;
		printf("%d\n", mlx->del);
	}

	if (keycode == MAC_TWO)
	{
		extern char **environ;
        int i;
        char *av[] = {"/bin/bash", "-c", "afplay click.mp3", NULL};
        i = fork();
        if (i == 0)
		{
			extern char **environ;
			char *av[] = {"/bin/bash", "-c", "afplay click.mp3", NULL};
            execve("/bin/bash", av, environ);
			exit(0);
		}
	}

	if (keycode == MAC_CTRL_R)
		mlx->player->weapon_state = 1;

	if (keycode == MAC_O)
	{
		mlx->sect[1]->ceiling -= 0.5f;
		printf("ceil %f\n", mlx->sect[1]->ceiling);
	}
	if (keycode == MAC_P)
	{
		mlx->sect[1]->ceiling += 0.5f;
		printf("ceil %f\n", mlx->sect[1]->ceiling);
	}
	if (keycode == MAC_L)
	{
		mlx->sect[1]->floor -= 0.5f;
		printf("floor %f\n", mlx->sect[1]->floor);
	}
	if (keycode == MAC_SEMICOLON)
	{
		mlx->sect[1]->floor += 0.5f;
		printf("floor %f\n", mlx->sect[1]->floor);
	}
	return (0);
}
