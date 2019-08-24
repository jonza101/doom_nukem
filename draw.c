/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:56:20 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/24 16:48:30 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_gun_anim(t_mlx *mlx, t_weapon *gun, int delay, int cont_delay)
{
	if (mlx->player->weapon_state == 1)
	{
		if (mlx->gun_delay == 0 && mlx->gun_fire_i == 0)
			ft_shoot(mlx);
		mlx->gun_delay++;
		if (mlx->gun_delay >= delay)
		{
			mlx->player->frame = gun->fire[mlx->gun_fire_i];
			mlx->gun_fire_i++;
			mlx->gun_delay = 0;
		}
		if (mlx->gun_fire_i >= gun->fire_n)
		{
			if (mlx->player->weapon != mlx->player->a_rifle)
				mlx->player->weapon_state = 0;
			mlx->gun_fire_i = 0;
			mlx->gun_delay = 0;
			if (gun != mlx->player->shotgun)
				gun->mag_ammo--;
		}
	}
	else if (mlx->player->weapon_state == 2)
	{
		mlx->gun_delay++;
		int altfire_n = (!mlx->altfire) ? gun->altfire_n : gun->altfire_cont_n;
		int del = (!mlx->altfire) ? delay : cont_delay;
		if (mlx->gun_delay >= del)
		{
			t_img *frame = (!mlx->altfire) ? gun->altfire[mlx->gun_fire_i] : gun->altfire_cont[mlx->gun_fire_i];
			mlx->player->frame = frame;
			mlx->gun_fire_i++;
			mlx->gun_delay = 0;
		}
		if (mlx->gun_fire_i >= altfire_n)
		{
			mlx->gun_fire_i = 0;
			mlx->gun_delay = 0;
			if (!mlx->altfire)
				mlx->altfire = 1;
			gun->mag_ammo--;
			ft_shoot(mlx);
		}
	}
	else if (mlx->player->weapon_state == 3 || mlx->player->weapon_state == 4)
	{
		mlx->gun_delay++;
		int anim_n = (mlx->player->weapon_state == 3) ? gun->reloading_n : gun->reloading_ptt_n;
		if (mlx->gun_delay >= delay)
		{
			mlx->player->frame = (mlx->player->weapon_state == 3) ? gun->reloading[mlx->gun_fire_i] : gun->reloading_ptt[mlx->gun_fire_i];
			mlx->gun_fire_i++;
			mlx->gun_delay = 0;
		}
		if (mlx->gun_fire_i >= anim_n)
		{
			int need_ammo = (gun->mag_ammo_count - gun->mag_ammo);
			int check_ammo = ft_clamp(gun->ammo_count - need_ammo, 0, gun->ammo_count);
			int poss_ammo = gun->ammo_count - check_ammo;
			gun->mag_ammo += poss_ammo;
			gun->ammo_count -= poss_ammo;
			mlx->player->weapon_state = 0;
			mlx->gun_fire_i = 0;
			mlx->gun_delay = 0;
		}
	}
}

void	ft_weapon_state(t_mlx *mlx)
{
	if (mlx->player->weapon->mag_ammo == 0 && mlx->player->weapon_state != 3 && mlx->player->weapon_state != 4)
		mlx->player->weapon_state = 0;
	if (mlx->player->weapon_state == 0)
		mlx->player->frame = mlx->player->weapon->idle[0];
}

void	ft_draw_cross(t_mlx *mlx)
{
	int i = W / 2 - 3;
	while (++i <= W / 2 + 2)
		mlx->data[ i + (H / 2) * W] = 0xFFFFFF;
	i = H / 2 - 3;
	while (++i <= H / 2 + 2)
		mlx->data[ W / 2 + i * W] = 0xFFFFFF;
}

void	ft_draw_player(t_mlx *mlx)
{
	double w_aspect_ratio = (double)mlx->player->frame->h / (double)mlx->player->frame->w;
	double scaler = (mlx->player->weapon == mlx->player->revolver && mlx->player->weapon_state == 3) ? 0.25f : mlx->player->weapon->scaler;
	if (mlx->player->weapon == mlx->player->shotgun && mlx->player->weapon_state > 2)
	{
		if ((mlx->gun_fire_i >= 3 && mlx->gun_fire_i <= 7) || (mlx->gun_fire_i >= 17 && mlx->gun_delay <= 18))
			scaler = 1.5f;
		else
			scaler = 1.05f;
	}
	double w_ya = (double)(H / 2.0f) + (H / 4.0f * scaler);
	double w_yb = H;
	double w_h = w_yb - w_ya;
	double w_w = w_h / (double)w_aspect_ratio;
	double w_mid = W / 2 - mlx->player->weapon->x_offset;
	int x = -1;
	while (++x < w_w)
	{
		int y = -1;
		while (++y < w_h)
		{
			double sample_x = x / w_w;
			double sample_y = y / w_h;
			int color = ft_texture_sampling(mlx->player->frame, sample_x, sample_y);
			int xc = (int)(w_mid - (w_w / 2.0f) + x);
			int yc = (int)w_ya + (int)y;
			if (color != IGNORE_COLOR)
			{
				if (mlx->sect[mlx->player->sector]->light == 0)
					color = ft_color_convert(color, mlx->sect[mlx->player->sector]->lum);
				mlx->data[yc * W + xc] = color;
			}
		}
	}
	ft_draw_cross(mlx);
}
