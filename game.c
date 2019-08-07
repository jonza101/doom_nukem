/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:40:26 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/07 19:08:32 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

#define LOCK_FPS 1000 / 60

int		ft_game_loop(t_mlx *mlx)
{
	ft_collision(mlx);
	ft_player_view(mlx);
	ft_move_calc(mlx);
	if (mlx->player->jump && mlx->ground && !mlx->crouching)
	{
		mlx->player->velocity->z += JUMP_H;
		mlx->falling = 1;
	}
	ft_reset_image(mlx);
	ft_draw(mlx);
	ft_obj(mlx);
	ft_weapon_state(mlx);
	if (mlx->player->weapon_state == 1)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->fire_delay, 0);
	else if (mlx->player->weapon_state == 2)
		ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->altfire_delay, mlx->player->weapon->altfire_cont_delay);
	ft_draw_player(mlx);
	// ft_transparent(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// printf("state %d\n", mlx->player->weapon_state);
	// printf("altfire %d\n", mlx->altfire);
	// printf("s %d\n", mlx->s);
	// printf("p_sect %d\n", mlx->player->sector);
	// printf("px %f	py %f	pz %f\n", mlx->player->pos->x, mlx->player->pos->y, mlx->player->pos->z);
	// printf("angle %f	sin %f	cos %f\n", mlx->player->angle, mlx->player->sin_angle, mlx->player->cos_angle);
	// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);
	// printf("g %d\nf %d\nm %d\nc %d\n\n", mlx->ground, mlx->falling, mlx->moving, mlx->crouching);
	// printf("\n");
	return (0);
}
