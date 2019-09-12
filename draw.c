/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 13:56:20 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/11 19:05:39 by zjeyne-l         ###   ########.fr       */
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

			mlx->hud_r = 0;
			mlx->r_i = 0;
			mlx->r_i_d = 0;
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

void	ft_draw_chr(t_mlx *mlx, t_img *chr, int x, int y, int d_h)
{
	double aspect_ratio = (double)chr->h / (double)chr->w;
	int ya = y - (d_h / 2.0f);
	double h = (y + d_h / 2.0f) - ya;
	double w = (double)h / (double)aspect_ratio;
	int _x = -1;
	while (++_x < w)
	{
		int _y = -1;
		while (++_y < h)
		{
			double sample_x = (double)_x / (double)w;
			double sample_y = (double)_y / (double)h;
			int color = ft_texture_sampling(chr, sample_x, sample_y);
			int xc = (int)(x - (w / 2.0f) + _x);
			int yc = (int)ya + (int)_y;
			if (color != IGNORE_COLOR)
				mlx->data[yc * W + xc] = color;
		}
	}
}

void	ft_hud_ammo(t_mlx *mlx, int ammo, int x, int d_h, int x_offset, int y_offset)
{
	if (!ammo)
	{
		ft_draw_chr(mlx, mlx->font[0], x, 660 + y_offset, d_h);
		mlx->hud_x = x;
		return;
	}
	int i = 0;
	while (ammo)
	{
		int digit = ammo % 10;
		ft_draw_chr(mlx, mlx->font[digit], x - i * x_offset, 660 + y_offset, d_h);
		mlx->hud_x = x - i * x_offset;
		ammo /= 10;
		i++;
	}
}

void	ft_r(t_mlx *mlx)
{
	if (mlx->hud_r && mlx->r_i < 25)
	{
		ft_draw_chr(mlx, mlx->font[10], mlx->hud_x - 60, 665, 30);
		mlx->r_i++;
	}
	if (mlx->r_i >= 25)
	{
		mlx->r_i_d++;
		mlx->hud_r = 0;
	}
	if (mlx->r_i_d >= 45)
	{
		mlx->r_i = 0;
		mlx->hud_r = 1;
		mlx->r_i_d = 0;
	}
}

void	ft_hud_hp(t_mlx *mlx, int hp)
{
	int i = -1;
	while (++i < 3)
	{
		int digit = hp % 10;
		ft_draw_chr(mlx, mlx->font[digit], 190 - i * 35, 660, 45);
		hp /= 10;
	}
	ft_draw_chr(mlx, mlx->font[11], 70, 653, 65);
}

void	ft_boost_time(t_mlx *mlx, int time, int y_offset)
{
	if (time <= 0)
		return ;
	int i = -1;
	while (++i < 2)
	{
		int digit = abs(time % 10);
		ft_draw_chr(mlx, mlx->font[digit], 115 - i * 14, 570 - y_offset, 15);
		time /= 10;
	}
}

void	ft_boost_anim(t_mlx *mlx, t_boost *boost)
{
	boost->del++;
	if (boost->del >= mlx->obj_l[boost->boost_i]->delay)
	{
		boost->frame = mlx->obj_l[boost->boost_i]->anim[boost->anim_i];
		boost->anim_i++;
		boost->del = 0;
	}
	if (boost->anim_i >= mlx->obj_l[boost->boost_i]->anim_n)
	{
		boost->del = 0;
		boost->anim_i = 0;
	}
}

void	ft_draw_weapon(t_mlx *mlx)
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
	ft_hud_hp(mlx, mlx->player->hp);
	ft_hud_ammo(mlx, mlx->player->weapon->ammo_count, 1200, 25, 20, 9);
	ft_hud_ammo(mlx, mlx->player->weapon->mag_ammo, mlx->hud_x - 40, 45, 35, 0);
	ft_r(mlx);
	if (mlx->player->jetpack)
	{
		if (mlx->hud_r || (mlx->r_i || mlx->r_i_d))
			ft_draw_chr(mlx, mlx->font[12], mlx->hud_x - 114, 665, 30);
		else
			ft_draw_chr(mlx, mlx->font[12], mlx->hud_x - 60, 665, 30);
	}

	if (mlx->player->speed_boost)
	{
		ft_boost_anim(mlx, mlx->boost[0]);
		ft_draw_chr(mlx, mlx->boost[0]->frame, 70, 517, 55);
		ft_boost_time(mlx, (int)mlx->player->speed_diff, 50);
	}
	if (mlx->player->hp_boost)
	{
		ft_boost_anim(mlx, mlx->boost[1]);
		ft_draw_chr(mlx, mlx->boost[1]->frame, 70, 570, 35);
		ft_boost_time(mlx, (int)mlx->player->hp_diff, 0);
	}
	// int i = -1;
	// while (++i < W)
	// {
	// 	mlx->data[682 * W + i] = 0xFFFF00;
	// 	mlx->data[637 * W + i] = 0xFFFF00;
	// }
}
