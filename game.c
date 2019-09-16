/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:40:26 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/16 21:45:57 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <time.h>

void	ft_check_doors(t_mlx *mlx)
{
	int s = -1;
	while (++s < mlx->num_sec)
	{
		t_sector *sector = mlx->sect[s];
		if (sector->is_door)
		{
			printf("sect %d			dist %f\n", s, sector->door_dist);
			if (sector->open)
			{
				sector->ceiling += 0.75f;
				// Mix_PlayChannel(17, mlx->snd->chunks->door, 0);
				if (sector->ceiling >= sector->start_ceiling)
				{
					// Mix_PlayChannel(17, mlx->snd->chunks->door, 0);
					sector->open = 0;
					sector->up = 1;
					sector->ceiling = sector->start_ceiling;
				}
			}
			else if (!sector->open && !sector->close && sector->up)
			{
				double time_diff = difftime(time(NULL), sector->start_time);
				printf("%d time %f\n\n", s, time_diff);
				double h = sector->ceiling - sector->floor;
				double h2 = h / 15;
				if (time_diff >= DOOR_TIME - 0.85 / h2 && !(Mix_Playing(17)) && mlx->player->sector != s)
				{
					if (sector->door_dist <= MAX_DOOR_DIST_VOL)
					{
						Mix_Volume(17, VOLUME - (sector->door_dist / MAX_DOOR_DIST_VOL) * VOLUME);
						Mix_PlayChannel(17, mlx->snd->chunks->door, 0);
						// Mix_VolumeChunk(mlx->snd->chunks->door, VOLUME);
					}
				}
				if (time_diff >= DOOR_TIME)
				{
					if (mlx->player->sector != s)
					{
						sector->close = 1;
						sector->up = 0;
					}
				}
			}
			else if (sector->close && !sector->up)
			{
				sector->ceiling -= 0.75f;
				// Mix_PlayChannel(17, mlx->snd->chunks->door, 0);
				if (sector->ceiling <= sector->floor)
				{
					// Mix_PlayChannel(17, mlx->snd->chunks->door, 0);
					sector->close = 0;
					sector->open = 0;
					sector->ceiling = sector->floor;
					mlx->activated_doors--;
				}
			}
		}
	}
}

void	ft_draw_end(t_mlx *mlx)
{
	// int x = -1;
	// while (++x < W)
	// {
	// 	int y = -1;
	// 	while (++y < H)
	// 		mlx->data[y * W + x] = mlx->fire[0];
	// }

	int x = -1;
	while (++x < W)
	{
		int y = 0;
		mlx->data[x] = mlx->fire[0];
		while (++y < H)
		{
			int src = y * W + x;
			int pix = mlx->fire_buff[src];
			if (pix == 0)
				mlx->fire_buff[src - W] = 0;
			else
			{
				int random = (rand() % 3) & 3;
				int dst = src - random + 1;
				mlx->fire_buff[dst - W] = abs(mlx->fire_buff[src] - (random & 1));
			}
			mlx->data[src] = mlx->fire[mlx->fire_buff[src]];
		}
	}

	ft_draw_chr(mlx, mlx->end_font[0], 478, 362, 120);
	ft_draw_chr(mlx, mlx->end_font[1], 539, 360, 115);
	ft_draw_chr(mlx, mlx->end_font[2], 600, 362, 120);
	ft_draw_chr(mlx, mlx->end_font[2], 680, 362, 120);
	ft_draw_chr(mlx, mlx->end_font[3], 741, 359, 114);
	ft_draw_chr(mlx, mlx->end_font[4], 801, 360, 115);

	// int i = -1;
	// while (++i < H)
	// {
	// 	mlx->data[i * W + W / 2] = 0xFF0000;
	// 	mlx->data[i * W + 569] = 0xFF0000;
	// 	mlx->data[i * W + 508] = 0xFF0000;
	// 	mlx->data[i * W + 710] = 0xFF0000;
	// 	mlx->data[i * W + 770] = 0xFF0000;
	// }
	// i = -1;
	// while (++i < W)
	// {
	// 	mlx->data[H / 2 * W + i] = 0xFF0000;
	// 	mlx->data[300 * W + i] = 0xFF0000;
	// 	mlx->data[423 * W + i] = 0xFF0000;
	// }
}

void	ft_draw_menu_back(t_mlx *mlx)
{
	int x = -1;
	while (++x < W)
	{
		int y = 0;
		mlx->data[x] = mlx->fire[0];
		while (++y < H)
		{
			int src = y * W + x;
			int pix = mlx->fire_buff[src];
			if (pix == 0)
				mlx->fire_buff[src - W] = 0;
			else
			{
				int random = (rand() % 3) & 3;
				int dst = src - random + 1;
				mlx->fire_buff[dst - W] = abs(mlx->fire_buff[src] - (random & 1));
			}
			mlx->data[src] = mlx->fire[mlx->fire_buff[src]];
		}
	}

	ft_draw_chr(mlx, mlx->menu_font[0], 573, 86, 127);
	ft_draw_chr(mlx, mlx->menu_font[1], 619, 75, 105);
	ft_draw_chr(mlx, mlx->menu_font[1], 661, 75, 105);
	ft_draw_chr(mlx, mlx->menu_font[2], 712, 88, 132);

	ft_draw_chr(mlx, mlx->menu_play[0], 599, 230, 50);
	ft_draw_chr(mlx, mlx->menu_play[1], 628, 230, 50);
	ft_draw_chr(mlx, mlx->menu_play[2], 655, 230, 50);
	ft_draw_chr(mlx, mlx->menu_play[3], 683, 230, 50);

	ft_draw_chr(mlx, mlx->menu_quit[0], 607, 325, 50);
	ft_draw_chr(mlx, mlx->menu_quit[1], 635, 325, 50);
	ft_draw_chr(mlx, mlx->menu_quit[2], 655, 325, 51);
	ft_draw_chr(mlx, mlx->menu_quit[3], 675, 325, 50);

	ft_draw_chr(mlx, mlx->menu_pointer[1], 540, 230 + mlx->button_i * 95, 25);
	ft_draw_chr(mlx, mlx->menu_pointer[0], 741, 230 + mlx->button_i * 95, 25);

	// int i = -1;
	// while (++i < H)
	// {
	// 	mlx->data[i * W + W / 2] = 0xFF0000;
	// 	mlx->data[i * W + W / 2 - 42] = 0xFF0000;
	// 	mlx->data[i * W + W / 2 + 42] = 0xFF0000;
	// 	mlx->data[i * W + W / 2 - 104] = 0xFF0000;
	// 	mlx->data[i * W + W / 2 + 104] = 0xFF0000;
	// }
	// i = -1;
	// while (++i < W)
	// {
	// 	mlx->data[H / 2 * W + i] = 0xFF0000;
	// 	mlx->data[(H / 2 + H / 4) * W + i] = 0xFF0000;
	// 	mlx->data[H / 4 * W + i] = 0xFF0000;
	// 	mlx->data[H / 4 * W + i] = 0xFF0000;
	// 	mlx->data[22 * W + i] = 0xFF0000;
	// 	mlx->data[698 * W + i] = 0xFF0000;
	// }
}

void	ft_play(t_mlx *mlx)
{
	int y = -1;
	while (++y < H * 2)
	{
		int x = -1;
		while (++x < W)
		{
			if (y == H - 1)
				mlx->fire_buff[y * W + x] = 35;
			else
				mlx->fire_buff[y * W + x] = 0;
		}
	}
	mlx->menu = 0;
}

int		ft_game_loop(t_mlx *mlx)
{
	ft_bzero(mlx->data, W * H * 4);
	if (mlx->menu)
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		ft_draw_menu_back(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		return (0);
	}
	if (mlx->end)
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		ft_draw_end(mlx);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		return (0);
	}

	// clock_t start_time = clock();

	ft_drawseg_sort(mlx);

	(mlx->activated_doors) ? ft_check_doors(mlx) : 1;

	ft_collision(mlx);
	ft_player_view(mlx);
	ft_move_calc(mlx);
	ft_draw(mlx);

	ft_weapon_state(mlx);

	if (mlx->player->weapon_state == 1)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->fire_delay, 0);
	else if (mlx->player->weapon_state == 2)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->altfire_delay, mlx->player->weapon->altfire_cont_delay);
	else if (mlx->player->weapon_state == 3 || mlx->player->weapon_state == 4)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->reloading_delay, 0);

	ft_draw_weapon(mlx);
	ft_boost_check(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// printf("%f\n", mlx->player->yaw);
	// printf("%d / %d\n", mlx->player->weapon->mag_ammo, mlx->player->weapon->ammo_count);
	// printf("loop\n");
	// printf("state %d\n", mlx->player->weapon_state);
	// printf("altfire %d\n", mlx->altfire);
	// printf("s %d\n", mlx->s);
	// printf("p_sect %d\n", mlx->player->sector);
	// printf("eye_h %f\n", mlx->player->eye_h);
	// printf("jetpack %d\n", mlx->player->jetpack);
	// printf("px %f	py %f	pz %f\n", mlx->player->pos->x, mlx->player->pos->y, mlx->player->pos->z);
	// printf("e_angle %f\n", mlx->e_angle);
	// printf("angle %f	sin %f	cos %f\n", mlx->player->angle, mlx->player->sin_angle, mlx->player->cos_angle);
	// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);
	// printf("g %d\nf %d\nm %d\nc %d\n\n", mlx->ground, mlx->falling, mlx->moving, mlx->crouching);
	// printf("\n");

	// FPS COUNTER
	// clock_t end_time = clock();
	// double dif = ((double)(end_time - start_time) / CLOCKS_PER_SEC);
	// double result = 1.0 / dif;
	// double sleep_time = result - 60;
	// // printf("%f\n", result);

	ft_drawseg_clear(mlx);
	ft_opening_clear(mlx);

	return (0);
}
