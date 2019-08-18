/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 12:49:39 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/18 18:06:43 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_arifle_fire(t_mlx *mlx)
{
	int fd;
	char *line;
	char *arifle_fire[ARIFLE_FIRE] = { "textures/weapons/a_rifle/fire/a_rifle_fire1.xpm", "textures/weapons/a_rifle/fire/a_rifle_fire2.xpm", "textures/weapons/a_rifle/fire/a_rifle_fire3.xpm",
									"textures/weapons/a_rifle/fire/a_rifle_fire4.xpm" };
	mlx->player->a_rifle->fire = (t_img**)malloc(sizeof(t_img*) * ARIFLE_FIRE);
	mlx->player->a_rifle->fire_n = ARIFLE_FIRE;
	int i = -1;
	while (++i < ARIFLE_FIRE)
	{
		fd = open(arifle_fire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->player->a_rifle->fire[i] = (t_img*)malloc(sizeof(t_img));
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
	char *arifle_idle[ARIFLE_IDLE] = { "textures/weapons/a_rifle/idle/a_rifle_idle.xpm" };

	fd = open(arifle_idle[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	mlx->player->a_rifle->idle = (t_img**)malloc(sizeof(t_img) * ARIFLE_IDLE);
	mlx->player->a_rifle->idle[0] = (t_img*)malloc(sizeof(t_img));
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
	mlx->player->a_rifle = (t_weapon*)malloc(sizeof(t_weapon));
	mlx->player->a_rifle->fire_delay = 2;
	mlx->player->a_rifle->has_altfire = 0;
	mlx->player->a_rifle->scaler = -0.62f;
	mlx->player->a_rifle->x_offset = 0;
	ft_init_arifle_idle(mlx);
	ft_init_arifle_fire(mlx);
}

void	ft_init_shotgun_fire(t_mlx *mlx)
{
	int fd;
	char *line;
	char *shotgun_fire[SHOTGUN_FIRE] = { "textures/weapons/shotgun/fire/shotgun_fire1.xpm", "textures/weapons/shotgun/fire/shotgun_fire2.xpm", "textures/weapons/shotgun/fire/shotgun_fire3.xpm",
									"textures/weapons/shotgun/fire/shotgun_fire4.xpm", "textures/weapons/shotgun/fire/shotgun_fire5.xpm", "textures/weapons/shotgun/fire/shotgun_fire6.xpm",
									"textures/weapons/shotgun/fire/shotgun_fire7.xpm", "textures/weapons/shotgun/fire/shotgun_fire8.xpm", "textures/weapons/shotgun/fire/shotgun_fire9.xpm",
									"textures/weapons/shotgun/fire/shotgun_fire8.xpm", "textures/weapons/shotgun/fire/shotgun_fire7.xpm", "textures/weapons/shotgun/fire/shotgun_fire6.xpm",
									"textures/weapons/shotgun/fire/shotgun_fire5.xpm" };
	mlx->player->shotgun->fire = (t_img**)malloc(sizeof(t_img*) * SHOTGUN_FIRE);
	mlx->player->shotgun->fire_n = SHOTGUN_FIRE;
	int i = -1;
	while (++i < SHOTGUN_FIRE)
	{
		fd = open(shotgun_fire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->player->shotgun->fire[i] = (t_img*)malloc(sizeof(t_img));
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
	char *shotgun_idle[SHOTGUN_IDLE] = { "textures/weapons/shotgun/idle/shotgun_idle.xpm" };

	fd = open(shotgun_idle[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	mlx->player->shotgun->idle = (t_img**)malloc(sizeof(t_img*) * SHOTGUN_IDLE);
	mlx->player->shotgun->idle[0] = (t_img*)malloc(sizeof(t_img));
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
	mlx->player->shotgun = (t_weapon*)malloc(sizeof(t_weapon));
	mlx->player->shotgun->fire_delay = 4;
	mlx->player->shotgun->has_altfire = 0;
	mlx->player->shotgun->scaler = 0.80f;
	mlx->player->shotgun->x_offset = 18;
	ft_init_shotgun_idle(mlx);
	ft_init_shotgun_fire(mlx);
}

void	ft_init_revolver_altfire_cont(t_mlx *mlx)
{
	int fd;
	char *line;
	char *rev_altfire_cont[REV_ALTFIRE_CONTINUE] = { "textures/weapons/revolver/altfire/rev_altfire9.xpm", "textures/weapons/revolver/altfire/rev_altfire8.xpm", "textures/weapons/revolver/altfire/rev_altfire5.xpm",
												"textures/weapons/revolver/altfire/rev_altfire6.xpm", "textures/weapons/revolver/altfire/rev_altfire7.xpm", "textures/weapons/revolver/altfire/rev_altfire8.xpm"};
	mlx->player->revolver->altfire_cont = (t_img**)malloc(sizeof(t_img*) * REV_ALTFIRE_CONTINUE);
	mlx->player->revolver->altfire_cont_n = REV_ALTFIRE_CONTINUE;
	int i = -1;
	while (++i < REV_ALTFIRE_CONTINUE)
	{
		fd = open(rev_altfire_cont[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->player->revolver->altfire_cont[i] = (t_img*)malloc(sizeof(t_img));
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
	char *rev_altfire[REV_ALTFIRE] = { "textures/weapons/revolver/altfire/rev_altfire1.xpm", "textures/weapons/revolver/altfire/rev_altfire2.xpm", "textures/weapons/revolver/altfire/rev_altfire3.xpm",
									"textures/weapons/revolver/altfire/rev_altfire4.xpm", "textures/weapons/revolver/altfire/rev_altfire5.xpm", "textures/weapons/revolver/altfire/rev_altfire6.xpm",
									"textures/weapons/revolver/altfire/rev_altfire7.xpm", "textures/weapons/revolver/altfire/rev_altfire8.xpm", "textures/weapons/revolver/altfire/rev_altfire9.xpm" };
	mlx->player->revolver->altfire = (t_img**)malloc(sizeof(t_img*) * REV_ALTFIRE);
	mlx->player->revolver->altfire_n = REV_ALTFIRE;
	int i = -1;
	while (++i < REV_ALTFIRE)
	{
		fd = open(rev_altfire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->player->revolver->altfire[i] = (t_img*)malloc(sizeof(t_img));
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
	char *rev_fire[REV_FIRE] = { "textures/weapons/revolver/fire/rev_fire1.xpm", "textures/weapons/revolver/fire/rev_fire2.xpm",
							"textures/weapons/revolver/fire/rev_fire3.xpm", "textures/weapons/revolver/fire/rev_fire4.xpm",
							"textures/weapons/revolver/fire/rev_fire4.xpm", "textures/weapons/revolver/fire/rev_fire3.xpm" };
	mlx->player->revolver->fire = (t_img**)malloc(sizeof(t_img*) * REV_FIRE);
	mlx->player->revolver->fire_n = REV_FIRE;
	int i = -1;
	while (++i < REV_FIRE)
	{
		fd = open(rev_fire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->player->revolver->fire[i] = (t_img*)malloc(sizeof(t_img));
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
	char *rev_idle[REV_IDLE] = { "textures/weapons/revolver/idle/rev_idle.xpm" };

	fd = open(rev_idle[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	mlx->player->revolver->idle = (t_img**)malloc(sizeof(t_img*) * REV_IDLE);
	mlx->player->revolver->idle[0] = (t_img*)malloc(sizeof(t_img));
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
	mlx->player->revolver = (t_weapon*)malloc(sizeof(t_weapon));
	mlx->player->revolver->fire_delay = 3;
	mlx->player->revolver->altfire_delay = 3;
	mlx->player->revolver->altfire_cont_delay = 3;
	mlx->player->revolver->has_altfire = 1;
	mlx->player->revolver->scaler = 0.0f;
	mlx->player->revolver->x_offset = 0;
	ft_init_revolver_idle(mlx);
	ft_init_revolver_fire(mlx);
	ft_init_revolver_altfire(mlx);
	ft_init_revolver_altfire_cont(mlx);
}