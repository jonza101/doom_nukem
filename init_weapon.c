/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsandor- <lsandor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:49:39 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/16 21:30:50 by lsandor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_arifle_reload_ptt(t_mlx *mlx)
{
	int fd;
	char *line;
	char *arifle_reload_ptt[24] = { "textures/weapons/a_rifle/reloading/pt1/a_rifle_r01.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r02.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r03.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r04.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r05.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r06.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r07.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r08.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r09.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r10.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r11.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r12.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r13.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r14.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r15.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r16.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r17.xpm", "textures/weapons/a_rifle/reloading/pt2/a_rifle_rr01.xpm",
								"textures/weapons/a_rifle/reloading/pt2/a_rifle_rr02.xpm", "textures/weapons/a_rifle/reloading/pt2/a_rifle_rr03.xpm", "textures/weapons/a_rifle/reloading/pt2/a_rifle_rr04.xpm",
								"textures/weapons/a_rifle/reloading/pt2/a_rifle_rr05.xpm", "textures/weapons/a_rifle/reloading/pt2/a_rifle_rr06.xpm", "textures/weapons/a_rifle/reloading/pt2/a_rifle_rr01.xpm" };
	(!(mlx->player->a_rifle->reloading_ptt = (t_img**)malloc(sizeof(t_img*) * 24))) ? ft_mem_error() : 1;
	mlx->player->a_rifle->reloading_ptt_n = 24;
	int i = -1;
	while (++i < 24)
	{
		fd = open(arifle_reload_ptt[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->a_rifle->reloading_ptt[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->player->a_rifle->reloading_ptt[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->a_rifle->reloading_ptt[i]->h = ft_atoi(tmp[1]);
		mlx->player->a_rifle->reloading_ptt[i]->img = mlx_xpm_file_to_image(mlx->mlx, arifle_reload_ptt[i], &mlx->player->a_rifle->reloading_ptt[i]->w, &mlx->player->a_rifle->reloading_ptt[i]->h);
		mlx->player->a_rifle->reloading_ptt[i]->data = (int*)mlx_get_data_addr(mlx->player->a_rifle->reloading_ptt[i]->img, &mlx->player->a_rifle->reloading_ptt[i]->bpp, &mlx->player->a_rifle->reloading_ptt[i]->size_line, &mlx->player->a_rifle->reloading_ptt[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_arifle_reload(t_mlx *mlx)
{
	int fd;
	char *line;
	char *arifle_reload[17] = { "textures/weapons/a_rifle/reloading/pt1/a_rifle_r01.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r02.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r03.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r04.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r05.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r06.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r07.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r08.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r09.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r10.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r11.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r12.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r13.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r14.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r15.xpm",
								"textures/weapons/a_rifle/reloading/pt1/a_rifle_r16.xpm", "textures/weapons/a_rifle/reloading/pt1/a_rifle_r17.xpm" };
	(!(mlx->player->a_rifle->reloading = (t_img**)malloc(sizeof(t_img*) * 17))) ? ft_mem_error() : 1;
	mlx->player->a_rifle->reloading_n = 17;
	mlx->player->a_rifle->reloading_delay = 3;
	int i = -1;
	while (++i < 17)
	{
		fd = open(arifle_reload[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->a_rifle->reloading[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->player->a_rifle->reloading[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->a_rifle->reloading[i]->h = ft_atoi(tmp[1]);
		mlx->player->a_rifle->reloading[i]->img = mlx_xpm_file_to_image(mlx->mlx, arifle_reload[i], &mlx->player->a_rifle->reloading[i]->w, &mlx->player->a_rifle->reloading[i]->h);
		mlx->player->a_rifle->reloading[i]->data = (int*)mlx_get_data_addr(mlx->player->a_rifle->reloading[i]->img, &mlx->player->a_rifle->reloading[i]->bpp, &mlx->player->a_rifle->reloading[i]->size_line, &mlx->player->a_rifle->reloading[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_arifle_fire(t_mlx *mlx)
{
	int fd;
	char *line;
	char *arifle_fire[4] = { "textures/weapons/a_rifle/fire/a_rifle_fire1.xpm", "textures/weapons/a_rifle/fire/a_rifle_fire2.xpm", "textures/weapons/a_rifle/fire/a_rifle_fire3.xpm",
									"textures/weapons/a_rifle/fire/a_rifle_fire4.xpm" };
	(!(mlx->player->a_rifle->fire = (t_img**)malloc(sizeof(t_img*) * 4))) ? ft_mem_error() : 1;
	mlx->player->a_rifle->fire_n = 4;
	int i = -1;
	while (++i < 4)
	{
		fd = open(arifle_fire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->a_rifle->fire[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->player->a_rifle->fire[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->a_rifle->fire[i]->h = ft_atoi(tmp[1]);
		mlx->player->a_rifle->fire[i]->img = mlx_xpm_file_to_image(mlx->mlx, arifle_fire[i], &mlx->player->a_rifle->fire[i]->w, &mlx->player->a_rifle->fire[i]->h);
		mlx->player->a_rifle->fire[i]->data = (int*)mlx_get_data_addr(mlx->player->a_rifle->fire[i]->img, &mlx->player->a_rifle->fire[i]->bpp, &mlx->player->a_rifle->fire[i]->size_line, &mlx->player->a_rifle->fire[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_arifle_idle(t_mlx *mlx)
{
	int fd;
	char *line;
	char *arifle_idle[1] = { "textures/weapons/a_rifle/idle/a_rifle_idle.xpm" };

	fd = open(arifle_idle[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	(!(mlx->player->a_rifle->idle = (t_img**)malloc(sizeof(t_img) * 1))) ? ft_mem_error() : 1;
	(!(mlx->player->a_rifle->idle[0] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
	mlx->player->a_rifle->idle[0]->w = ft_atoi(&tmp[0][1]);
	mlx->player->a_rifle->idle[0]->h = ft_atoi(tmp[1]);
	mlx->player->a_rifle->idle[0]->img = mlx_xpm_file_to_image(mlx->mlx, arifle_idle[0], &mlx->player->a_rifle->idle[0]->w, &mlx->player->a_rifle->idle[0]->h);
	mlx->player->a_rifle->idle[0]->data = (int*)mlx_get_data_addr(mlx->player->a_rifle->idle[0]->img, &mlx->player->a_rifle->idle[0]->bpp, &mlx->player->a_rifle->idle[0]->size_line, &mlx->player->a_rifle->idle[0]->endian);
	ft_strsplit_free(tmp);
	close(fd);
	ft_strdel(&line);
}

void	ft_init_arifle(t_mlx *mlx)
{
	(!(mlx->player->a_rifle = (t_weapon*)malloc(sizeof(t_weapon)))) ? ft_mem_error() : 1;
	mlx->player->a_rifle->fire_delay = 2;
	mlx->player->a_rifle->has_altfire = 0;
	mlx->player->a_rifle->has_reload_ptt = 1;
	mlx->player->a_rifle->mag_ammo = ARIFLE_AMMO;
	mlx->player->a_rifle->ammo_count = ARIFLE_AMMO * 3;
	mlx->player->a_rifle->mag_ammo_count = ARIFLE_AMMO;
	mlx->player->a_rifle->scaler = -0.62f;
	mlx->player->a_rifle->x_offset = 0;
	ft_init_arifle_idle(mlx);
	ft_init_arifle_fire(mlx);
	ft_init_arifle_reload(mlx);
	ft_init_arifle_reload_ptt(mlx);
	mlx->player->a_rifle->shot = Mix_LoadWAV("/sound/rifle.wav");
	mlx->player->a_rifle->assreloadboost = Mix_LoadWAV("/sound/assschelk.wav");
	mlx->player->a_rifle->assreload = Mix_LoadWAV("/sound/export.wav");
	mlx->player->a_rifle->reload = Mix_LoadWAV("/sound/assreload.wav");
	mlx->player->a_rifle->assreloadshort = Mix_LoadWAV("/sound/relaodslow.wav");
}

void	ft_init_shotgun_fire(t_mlx *mlx)
{
	int fd;
	char *line;
	char *shotgun_fire[13] = { "textures/weapons/shotgun/fire/shotgun_fire1.xpm", "textures/weapons/shotgun/fire/shotgun_fire2.xpm", "textures/weapons/shotgun/fire/shotgun_fire3.xpm",
								"textures/weapons/shotgun/fire/shotgun_fire4.xpm", "textures/weapons/shotgun/fire/shotgun_fire5.xpm", "textures/weapons/shotgun/fire/shotgun_fire6.xpm",
								"textures/weapons/shotgun/fire/shotgun_fire7.xpm", "textures/weapons/shotgun/fire/shotgun_fire8.xpm", "textures/weapons/shotgun/fire/shotgun_fire9.xpm",
								"textures/weapons/shotgun/fire/shotgun_fire8.xpm", "textures/weapons/shotgun/fire/shotgun_fire7.xpm", "textures/weapons/shotgun/fire/shotgun_fire6.xpm",
								"textures/weapons/shotgun/fire/shotgun_fire5.xpm" };
	(!(mlx->player->shotgun->fire = (t_img**)malloc(sizeof(t_img*) * 13))) ? ft_mem_error() : 1;
	mlx->player->shotgun->fire_n = 13;
	int i = -1;
	while (++i < 13)
	{
		fd = open(shotgun_fire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->shotgun->fire[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->player->shotgun->fire[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->shotgun->fire[i]->h = ft_atoi(tmp[1]);
		mlx->player->shotgun->fire[i]->img = mlx_xpm_file_to_image(mlx->mlx, shotgun_fire[i], &mlx->player->shotgun->fire[i]->w, &mlx->player->shotgun->fire[i]->h);
		mlx->player->shotgun->fire[i]->data = (int*)mlx_get_data_addr(mlx->player->shotgun->fire[i]->img, &mlx->player->shotgun->fire[i]->bpp, &mlx->player->shotgun->fire[i]->size_line, &mlx->player->shotgun->fire[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_shotgun_idle(t_mlx *mlx)
{
	int fd;
	char *line;
	char *shotgun_idle[1] = { "textures/weapons/shotgun/idle/shotgun_idle.xpm" };

	fd = open(shotgun_idle[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	(!(mlx->player->shotgun->idle = (t_img**)malloc(sizeof(t_img*) * 1))) ? ft_mem_error() : 1;
	(!(mlx->player->shotgun->idle[0] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
	mlx->player->shotgun->idle[0]->w = ft_atoi(&tmp[0][1]);
	mlx->player->shotgun->idle[0]->h = ft_atoi(tmp[1]);
	mlx->player->shotgun->idle[0]->img = mlx_xpm_file_to_image(mlx->mlx, shotgun_idle[0], &mlx->player->shotgun->idle[0]->w, &mlx->player->shotgun->idle[0]->h);
	mlx->player->shotgun->idle[0]->data = (int*)mlx_get_data_addr(mlx->player->shotgun->idle[0]->img, &mlx->player->shotgun->idle[0]->bpp, &mlx->player->shotgun->idle[0]->size_line, &mlx->player->shotgun->idle[0]->endian);
	ft_strsplit_free(tmp);
	close(fd);
	ft_strdel(&line);
}

void	ft_init_shotgun(t_mlx *mlx)
{
	(!(mlx->player->shotgun = (t_weapon*)malloc(sizeof(t_weapon)))) ? ft_mem_error() : 1;
	mlx->player->shotgun->fire_delay = 4;
	mlx->player->shotgun->has_altfire = 0;
	mlx->player->shotgun->has_reload_ptt = 0;
	mlx->player->shotgun->mag_ammo = SHOTGUN_AMMO;
	mlx->player->shotgun->ammo_count = SHOTGUN_AMMO * 3;
	mlx->player->shotgun->mag_ammo_count = SHOTGUN_AMMO;
	mlx->player->shotgun->scaler = 0.80f;
	mlx->player->shotgun->x_offset = 18;
	ft_init_shotgun_idle(mlx);
	ft_init_shotgun_fire(mlx);
	mlx->player->shotgun->shot = Mix_LoadWAV("/sound/shotgun.wav");
}

void	ft_init_revolver_reload(t_mlx *mlx)
{
	int fd;
	char *line;
	char *rev_reload[19] = { "textures/weapons/revolver/reloading/rev_reload01.xpm", "textures/weapons/revolver/reloading/rev_reload02.xpm", "textures/weapons/revolver/reloading/rev_reload03.xpm",
								"textures/weapons/revolver/reloading/rev_reload04.xpm", "textures/weapons/revolver/reloading/rev_reload05.xpm", "textures/weapons/revolver/reloading/rev_reload06.xpm",
								"textures/weapons/revolver/reloading/rev_reload07.xpm", "textures/weapons/revolver/reloading/rev_reload08.xpm", "textures/weapons/revolver/reloading/rev_reload09.xpm",
								"textures/weapons/revolver/reloading/rev_reload10.xpm", "textures/weapons/revolver/reloading/rev_reload11.xpm", "textures/weapons/revolver/reloading/rev_reload12.xpm",
								"textures/weapons/revolver/reloading/rev_reload13.xpm", "textures/weapons/revolver/reloading/rev_reload06.xpm", "textures/weapons/revolver/reloading/rev_reload04.xpm",
								"textures/weapons/revolver/reloading/rev_reload03.xpm", "textures/weapons/revolver/reloading/rev_reload02.xpm", "textures/weapons/revolver/reloading/rev_reload01.xpm",
								"textures/weapons/revolver/reloading/rev_reload05.xpm" };
	(!(mlx->player->revolver->reloading = (t_img**)malloc(sizeof(t_img*) * 19))) ? ft_mem_error() : 1;
	mlx->player->revolver->reloading_n = 19;
	mlx->player->revolver->reloading_delay = 3;
	int i = -1;
	while (++i < 19)
	{
		fd = open(rev_reload[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->revolver->reloading[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->player->revolver->reloading[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->revolver->reloading[i]->h = ft_atoi(tmp[1]);
		mlx->player->revolver->reloading[i]->img = mlx_xpm_file_to_image(mlx->mlx, rev_reload[i], &mlx->player->revolver->reloading[i]->w, &mlx->player->revolver->reloading[i]->h);
		mlx->player->revolver->reloading[i]->data = (int*)mlx_get_data_addr(mlx->player->revolver->reloading[i]->img, &mlx->player->revolver->reloading[i]->bpp, &mlx->player->revolver->reloading[i]->size_line, &mlx->player->revolver->reloading[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_revolver_altfire_cont(t_mlx *mlx)
{
	int fd;
	char *line;
	char *rev_altfire_cont[6] = { "textures/weapons/revolver/altfire/rev_altfire9.xpm", "textures/weapons/revolver/altfire/rev_altfire8.xpm", "textures/weapons/revolver/altfire/rev_altfire5.xpm",
												"textures/weapons/revolver/altfire/rev_altfire6.xpm", "textures/weapons/revolver/altfire/rev_altfire7.xpm", "textures/weapons/revolver/altfire/rev_altfire8.xpm"};
	(!(mlx->player->revolver->altfire_cont = (t_img**)malloc(sizeof(t_img*) * 6))) ? ft_mem_error() : 1;
	mlx->player->revolver->altfire_cont_n = 6;
	int i = -1;
	while (++i < 6)
	{
		fd = open(rev_altfire_cont[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->revolver->altfire_cont[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->player->revolver->altfire_cont[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->revolver->altfire_cont[i]->h = ft_atoi(tmp[1]);
		mlx->player->revolver->altfire_cont[i]->img = mlx_xpm_file_to_image(mlx->mlx, rev_altfire_cont[i], &mlx->player->revolver->altfire_cont[i]->w, &mlx->player->revolver->altfire_cont[i]->h);
		mlx->player->revolver->altfire_cont[i]->data = (int*)mlx_get_data_addr(mlx->player->revolver->altfire_cont[i]->img, &mlx->player->revolver->altfire_cont[i]->bpp, &mlx->player->revolver->altfire_cont[i]->size_line, &mlx->player->revolver->altfire_cont[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_revolver_altfire(t_mlx *mlx)
{
	int fd;
	char *line;
	char *rev_altfire[9] = { "textures/weapons/revolver/altfire/rev_altfire1.xpm", "textures/weapons/revolver/altfire/rev_altfire2.xpm", "textures/weapons/revolver/altfire/rev_altfire3.xpm",
									"textures/weapons/revolver/altfire/rev_altfire4.xpm", "textures/weapons/revolver/altfire/rev_altfire5.xpm", "textures/weapons/revolver/altfire/rev_altfire6.xpm",
									"textures/weapons/revolver/altfire/rev_altfire7.xpm", "textures/weapons/revolver/altfire/rev_altfire8.xpm", "textures/weapons/revolver/altfire/rev_altfire9.xpm" };
	(!(mlx->player->revolver->altfire = (t_img**)malloc(sizeof(t_img*) * 9))) ? ft_mem_error() : 1;
	mlx->player->revolver->altfire_n = 9;
	int i = -1;
	while (++i < 9)
	{
		fd = open(rev_altfire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->revolver->altfire[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->player->revolver->altfire[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->revolver->altfire[i]->h = ft_atoi(tmp[1]);
		mlx->player->revolver->altfire[i]->img = mlx_xpm_file_to_image(mlx->mlx, rev_altfire[i], &mlx->player->revolver->altfire[i]->w, &mlx->player->revolver->altfire[i]->h);
		mlx->player->revolver->altfire[i]->data = (int*)mlx_get_data_addr(mlx->player->revolver->altfire[i]->img, &mlx->player->revolver->altfire[i]->bpp, &mlx->player->revolver->altfire[i]->size_line, &mlx->player->revolver->altfire[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_revolver_fire(t_mlx *mlx)
{
	int fd;
	char *line;
	char *rev_fire[6] = { "textures/weapons/revolver/fire/rev_fire1.xpm", "textures/weapons/revolver/fire/rev_fire2.xpm",
							"textures/weapons/revolver/fire/rev_fire3.xpm", "textures/weapons/revolver/fire/rev_fire4.xpm",
							"textures/weapons/revolver/fire/rev_fire4.xpm", "textures/weapons/revolver/fire/rev_fire3.xpm" };
	(!(mlx->player->revolver->fire = (t_img**)malloc(sizeof(t_img*) * 6))) ? ft_mem_error() : 1;
	mlx->player->revolver->fire_n = 6;
	int i = -1;
	while (++i < 6)
	{
		fd = open(rev_fire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->player->revolver->fire[i] = (t_img*)malloc(sizeof(t_img))) ? ft_mem_error() : 1);
		mlx->player->revolver->fire[i]->w = ft_atoi(&tmp[0][1]);
		mlx->player->revolver->fire[i]->h = ft_atoi(tmp[1]);
		mlx->player->revolver->fire[i]->img = mlx_xpm_file_to_image(mlx->mlx, rev_fire[i], &mlx->player->revolver->fire[i]->w, &mlx->player->revolver->fire[i]->h);
		mlx->player->revolver->fire[i]->data = (int*)mlx_get_data_addr(mlx->player->revolver->fire[i]->img, &mlx->player->revolver->fire[i]->bpp, &mlx->player->revolver->fire[i]->size_line, &mlx->player->revolver->fire[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_revolver_idle(t_mlx *mlx)
{
	int fd;
	char *line;
	char *rev_idle[1] = { "textures/weapons/revolver/idle/rev_idle.xpm" };

	fd = open(rev_idle[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	(!(mlx->player->revolver->idle = (t_img**)malloc(sizeof(t_img*) * 1))) ? ft_mem_error() : 1;
	(!(mlx->player->revolver->idle[0] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
	mlx->player->revolver->idle[0]->w = ft_atoi(&tmp[0][1]);
	mlx->player->revolver->idle[0]->h = ft_atoi(tmp[1]);
	mlx->player->revolver->idle[0]->img = mlx_xpm_file_to_image(mlx->mlx, rev_idle[0], &mlx->player->revolver->idle[0]->w, &mlx->player->revolver->idle[0]->h);
	mlx->player->revolver->idle[0]->data = (int*)mlx_get_data_addr(mlx->player->revolver->idle[0]->img, &mlx->player->revolver->idle[0]->bpp, &mlx->player->revolver->idle[0]->size_line, &mlx->player->revolver->idle[0]->endian);
	ft_strsplit_free(tmp);
	close(fd);
	ft_strdel(&line);
}

void	ft_init_revolver(t_mlx *mlx)
{
	(!(mlx->player->revolver = (t_weapon*)malloc(sizeof(t_weapon)))) ? ft_mem_error() : 1;
	mlx->player->revolver->fire_delay = 4;
	mlx->player->revolver->altfire_delay = 2;
	mlx->player->revolver->altfire_cont_delay = 2;
	mlx->player->revolver->has_reload_ptt = 0;
	mlx->player->revolver->mag_ammo = REVOLVER_AMMO;
	mlx->player->revolver->ammo_count = REVOLVER_AMMO * 3;
	mlx->player->revolver->mag_ammo_count = REVOLVER_AMMO;
	mlx->player->revolver->has_altfire = 1;
	mlx->player->revolver->scaler = 0.0f;
	mlx->player->revolver->x_offset = 0;
	ft_init_revolver_idle(mlx);
	ft_init_revolver_fire(mlx);
	ft_init_revolver_altfire(mlx);
	ft_init_revolver_altfire_cont(mlx);
	ft_init_revolver_reload(mlx);
	mlx->player->revolver->shot = Mix_LoadWAV("/sound/pistol.wav");
	mlx->player->revolver->reload = Mix_LoadWAV("/sound/reloadrev.wav");
}