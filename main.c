/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:24:10 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/13 21:29:03 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_image(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
		mlx->data[y * W + x] = mlx_get_color_value(mlx->mlx, color);
}

void	ft_reset_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx_clear_window(mlx->mlx, mlx->win);
}

// int x,y;
//         SDL_GetRelativeMouseState(&x,&y);
//         player.angle += x * 0.03f;
//         yaw          = clamp(yaw - y*0.05f, -5, 5);
//         player.yaw   = yaw - player.velocity.z*0.5f;
//         MovePlayer(0,0);

// int		mouse_move(int x, int y, t_mlx *mlx)
// {
	// printf("x %d	y %d\n", x, y);
		// if (x > mlx->mouse_pos_x)
		// 	mlx->player->angle += x * 0.00001f;
		// if (x < mlx->mouse_pos_x)
		// 	mlx->player->angle -= x * 0.00001f;
// 		printf("yaww %f\n", mlx->yaw + y * 0.05f);
// 		mlx->yaw = ft_clamp(mlx->yaw - y * 0.05f, -0.5, 0.5);
// 		mlx->player->yaw = mlx->yaw - mlx->player->velocity->z * 0.5;
// 		printf("pyaw %f\n\n", mlx->player->yaw);
// 		mlx->mouse_pos_x = x;
// 		mlx->mouse_pos_y = y;
// 		ft_move_player(mlx, 0, 0);
// 	return (0);
// }

int		ft_key_press(int keycode, t_mlx *mlx)
{
	// printf("%d\n", keycode);
	(keycode == 65307) ? exit(0) : 1;

	if (keycode == 65361)	//	LOOK LEFT
	{
		mlx->player->angle -= 0.09f;
		ft_move_player(mlx, 0, 0);
	}
	if (keycode == 65363)	//	LOOK RIGHT
	{
		mlx->player->angle += 0.09f;
		ft_move_player(mlx, 0, 0);
	}
	if (keycode == 65362)	//	LOOK UP
	{
		mlx->player->yaw -= 0.25f - mlx->player->velocity->z * 0.5;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -10, 10);
	}
	if (keycode == 65364)	//	LOOK DOWN
	{
		mlx->player->yaw += 0.25f - mlx->player->velocity->z * 0.5;
		mlx->player->yaw = ft_clamp(mlx->player->yaw, -10, 10);
	}

	if (keycode == 1731)
	{
		mlx->wsad[0] = 1;
		return (0);
	}
	if (keycode == 1753)
	{
		mlx->wsad[1] = 1;
		return (0);
	}
	if (keycode == 1734)
	{
		mlx->wsad[2] = 1;
		return (0);
	}
	if (keycode == 1751)
	{
		mlx->wsad[3] = 1;
		return (0);
	}
	return (0);
}

int		ft_game_loop(t_mlx *mlx)
{
	ft_collision(mlx);
	mlx->ground = 0;
	mlx->falling = 1;
	mlx->moving = 0;
	mlx->crouching = 0;
	ft_collision(mlx);
	ft_move_calc(mlx);
	ft_reset_image(mlx);
	ft_draw(mlx);
	int i = -1;
	while (++i < 4)
		mlx->wsad[i] = 0;
	return (0);
}

int		main()
{
	t_mlx	*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Doom-Nukem");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_load_map(mlx, "map");
	
	// printf("yaw %f\n", mlx->player->yaw);
	mlx->player->cos_angle = cosf(mlx->player->angle);
	mlx->player->sin_angle = sinf(mlx->player->angle);
	mlx->player->yaw = 0.0f;
	mlx->yaw = 0.0;
	// printf("yaw %f\n", mlx->player->yaw);

	mlx_hook(mlx->win, 2, 1L << 0, ft_key_press, mlx);
	// mlx_hook(mlx->win, 6, 1L<<6, mouse_move, mlx);
	mlx_loop_hook(mlx->mlx, ft_game_loop, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
