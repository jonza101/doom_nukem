/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:24:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/28 19:23:11 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_revolver_fire(t_mlx *mlx)
{
	int fd;
	char *line;
	char *rev_fire[REV_FIRE] = { "textures/weapons/revolver/fire/rev_fire1.xpm", "textures/weapons/revolver/fire/rev_fire2.xpm",
							"textures/weapons/revolver/fire/rev_fire3.xpm", "textures/weapons/revolver/fire/rev_fire4.xpm",
							"textures/weapons/revolver/fire/rev_fire4.xpm", "textures/weapons/revolver/fire/rev_fire3.xpm" };
	mlx->player->revolver->fire = (t_img**)malloc(sizeof(t_img*) * REV_FIRE);
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
	// mlx->player->revolver->afte_fire_delay = 3;
	ft_init_revolver_idle(mlx);
	ft_init_revolver_fire(mlx);
}

void	ft_init_sky(t_mlx *mlx)
{
	int fd;
	char *line;
	char *sky[SKY] = { "textures/sky/skybox.xpm" };
	int i = -1;
	while (++i < SKY)
	{
		fd = open(sky[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->sky[i] = (t_img*)malloc(sizeof(t_img));
		mlx->sky[i]->w = ft_atoi(&tmp[0][1]);
		mlx->sky[i]->h = ft_atoi(tmp[1]);
		mlx->sky[i]->img = mlx_xpm_file_to_image(mlx->mlx, sky[i], &mlx->sky[i]->w, &mlx->sky[i]->h);
		mlx->sky[i]->data = (int*)mlx_get_data_addr(mlx->sky[i]->img, &mlx->sky[i]->bpp, &mlx->sky[i]->size_line, &mlx->sky[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_transparent(t_mlx *mlx)
{
	int fd;
	char *line;
	char *twall[TRANSPARENT] = { "textures/transparent/glass.xpm" };
	int i = -1;
	while (++i < TRANSPARENT)
	{
		fd = open(twall[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->transparent[i] = (t_img*)malloc(sizeof(t_img));
		mlx->transparent[i]->w = ft_atoi(&tmp[0][1]);
		mlx->transparent[i]->h = ft_atoi(tmp[1]);
		mlx->transparent[i]->img = mlx_xpm_file_to_image(mlx->mlx, twall[i], &mlx->transparent[i]->w, &mlx->transparent[i]->h);
		mlx->transparent[i]->data = (int*)mlx_get_data_addr(mlx->transparent[i]->img, &mlx->transparent[i]->bpp, &mlx->transparent[i]->size_line, &mlx->transparent[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_scaler(t_mlx *mlx)
{
	mlx->obj[0]->scaler = 1.0f;
	mlx->obj[1]->scaler = 3.5f;
	mlx->obj[2]->scaler = -5.0f;

	mlx->obj[0]->aspect_scaler = 1.0f;
	mlx->obj[1]->aspect_scaler = 0.95f;
	mlx->obj[2]->aspect_scaler = 1.25f;
}

void	ft_init_obj(t_mlx *mlx)
{
	int fd;
	char *line;
	char *objs[OBJ] = { "textures/obj/barrel.xpm", "textures/obj/backpack.xpm", "textures/obj/cacodemon.xpm" };
	int i = -1;
	while (++i < OBJ)
	{
		fd = open(objs[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->obj[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj[i]->h = ft_atoi(tmp[1]);
		mlx->obj[i]->img = mlx_xpm_file_to_image(mlx->mlx, objs[i], &mlx->obj[i]->w, &mlx->obj[i]->h);
		mlx->obj[i]->data = (int*)mlx_get_data_addr(mlx->obj[i]->img, &mlx->obj[i]->bpp, &mlx->obj[i]->size_line, &mlx->obj[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
	ft_init_scaler(mlx);
}

void	ft_init_textures(t_mlx *mlx)
{
	int fd;
	char *line;
	char *txts[TXT] = { "textures/walls/brick.xpm", "textures/walls/wall.xpm", "textures/walls/scifi_wall.xpm" };
	int i = -1;
	while (++i < TXT)
	{
		fd = open(txts[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->txt[i] = (t_img*)malloc(sizeof(t_img));
		mlx->txt[i]->w = ft_atoi(&tmp[0][1]);
		mlx->txt[i]->h = ft_atoi(tmp[1]);
		mlx->txt[i]->img = mlx_xpm_file_to_image(mlx->mlx, txts[i], &mlx->txt[i]->w, &mlx->txt[i]->h);
		mlx->txt[i]->data = (int*)mlx_get_data_addr(mlx->txt[i]->img, &mlx->txt[i]->bpp, &mlx->txt[i]->size_line, &mlx->txt[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}
