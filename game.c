/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:40:26 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/24 19:18:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include <time.h>

int		ft_game_loop(t_mlx *mlx)
{
	clock_t start_time = clock();

	ft_drawseg_sort(mlx);

	ft_collision(mlx);
	ft_player_view(mlx);
	ft_move_calc(mlx);
	ft_reset_image(mlx);
	ft_draw(mlx);

	ft_weapon_state(mlx);

	if (mlx->player->weapon_state == 1)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->fire_delay, 0);
	else if (mlx->player->weapon_state == 2)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->altfire_delay, mlx->player->weapon->altfire_cont_delay);
	else if (mlx->player->weapon_state == 3 || mlx->player->weapon_state == 4)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->reloading_delay, 0);

	ft_draw_player(mlx);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	printf("%d / %d\n", mlx->player->weapon->mag_ammo, mlx->player->weapon->ammo_count);
	// printf("loop\n");
	// printf("state %d\n", mlx->player->weapon_state);
	// printf("altfire %d\n", mlx->altfire);
	// printf("s %d\n", mlx->s);
	// printf("p_sect %d\n", mlx->player->sector);
	// printf("px %f	py %f	pz %f\n", mlx->player->pos->x, mlx->player->pos->y, mlx->player->pos->z);
	// printf("angle %f	sin %f	cos %f\n", mlx->player->angle, mlx->player->sin_angle, mlx->player->cos_angle);
	// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);
	// printf("g %d\nf %d\nm %d\nc %d\n\n", mlx->ground, mlx->falling, mlx->moving, mlx->crouching);
	// printf("\n");

	// FPS COUNTER
	clock_t end_time = clock();
	double dif = ((double)(end_time - start_time) / CLOCKS_PER_SEC);
	double result = 1.0 / dif;
	double sleep_time = result - 60;
	// printf("%f\n", result);

	ft_drawseg_clear(mlx);
	ft_opening_clear(mlx);

	return (0);
}
