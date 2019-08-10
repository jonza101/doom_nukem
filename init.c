/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:24:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/10 19:14:04 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
	mlx->obj[0]->scaler = 2.5f;
	mlx->obj[1]->scaler = 4.5f;
	mlx->obj[2]->scaler = -4.5f;

	mlx->obj[0]->aspect_scaler = 1.0f;
	mlx->obj[1]->aspect_scaler = 0.95f;
	mlx->obj[2]->aspect_scaler = 1.25f;
}

void	ft_init_firepot(t_mlx *mlx)
{
	int fd;
	char *line;
	char *pot[4] = { "textures/obj/firepot/firepot1.xpm", "textures/obj/firepot/firepot2.xpm", "textures/obj/firepot/firepot3.xpm", "textures/obj/firepot/firepot4.xpm" };
	mlx->obj_t[0] = (t_obj_temp*)malloc(sizeof(t_obj_temp));
	mlx->obj_t[0]->anim = (t_img**)malloc(sizeof(t_img*) * 4);
	mlx->obj_t[0]->anim_n = 4;
	mlx->obj_t[0]->anim_i = 0;
	mlx->obj_t[0]->delay = 3;
	mlx->obj_t[0]->del = 0;
	int i = -1;
	while (++i < 4)
	{
		fd = open(pot[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->obj_t[0]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_t[0]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_t[0]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->obj_t[0]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, pot[i], &mlx->obj_t[0]->anim[i]->w, &mlx->obj_t[0]->anim[i]->h);
		mlx->obj_t[0]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_t[0]->anim[i]->img, &mlx->obj_t[0]->anim[i]->bpp, &mlx->obj_t[0]->anim[i]->size_line, &mlx->obj_t[0]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_anim_obj(t_mlx *mlx)
{
	mlx->obj_t = (t_obj_temp**)malloc(sizeof(t_obj_temp*) * 1);
	ft_init_firepot(mlx);
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
