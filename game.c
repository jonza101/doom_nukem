/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:40:26 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/28 19:12:54 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
	ft_gun_anim(mlx, mlx->player->weapon, mlx->player->weapon->fire_delay);
	ft_draw_player(mlx);
	// ft_transparent(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	// printf("state %d\n", mlx->player->weapon_state);
	// printf("s %d\n", mlx->s);
	// printf("p_sect %d\n", mlx->player->sector);
	// printf("px %f	py %f	pz %f\n", mlx->player->pos->x, mlx->player->pos->y, mlx->player->pos->z);
	// printf("angle %f	sin %f	cos %f\n", mlx->player->angle, mlx->player->sin_angle, mlx->player->cos_angle);
	// printf("dx %f	dy %f	dz %f\n\n", mlx->player->velocity->x, mlx->player->velocity->y, mlx->player->velocity->z);
	// printf("g %d\nf %d\nm %d\nc %d\n\n", mlx->ground, mlx->falling, mlx->moving, mlx->crouching);
	// printf("\n");

	// mlx->player->weapon_state = 0;
	return (0);
}
