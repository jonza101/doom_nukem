/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:43:09 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/11 20:12:25 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_fire_a(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 7;
	char *fire[13] = { "textures/obj/fire_a/fire_a01.xpm", 
						"textures/obj/fire_a/fire_a03.xpm", "textures/obj/fire_a/fire_a04.xpm",
						"textures/obj/fire_a/fire_a05.xpm", "textures/obj/fire_a/fire_a06.xpm",
						"textures/obj/fire_a/fire_a07.xpm", "textures/obj/fire_a/fire_a08.xpm",
						"textures/obj/fire_a/fire_a09.xpm", "textures/obj/fire_a/fire_a10.xpm",
						"textures/obj/fire_a/fire_a11.xpm", "textures/obj/fire_a/fire_a12.xpm",
						"textures/obj/fire_a/fire_a13.xpm", "textures/obj/fire_a/fire_a14.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 13);
	mlx->obj_l[id]->anim_n = 13;
	mlx->obj_l[id]->delay = 4;
	mlx->obj_l[id]->expl = 0;
	int i = -1;
	while (++i < 13)
	{
		fd = open(fire[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->obj_l[id]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[id]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[id]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, fire[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_canister(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 6;
	char *can[4] = { "textures/obj/canister/canister01.xpm", "textures/obj/canister/canister02.xpm",
						"textures/obj/canister/canister03.xpm", "textures/obj/canister/canister03.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 4);
	mlx->obj_l[id]->anim_n = 4;
	mlx->obj_l[id]->delay = 7;
	mlx->obj_l[id]->expl = 0;
	int i = -1;
	while (++i < 4)
	{
		fd = open(can[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->obj_l[id]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[id]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[id]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, can[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_water(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 5;
	char *water[4] = { "textures/obj/water/water01.xpm", "textures/obj/water/water02.xpm",
						"textures/obj/water/water03.xpm", "textures/obj/water/water04.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 4);
	mlx->obj_l[id]->anim_n = 4;
	mlx->obj_l[id]->delay = 6;
	mlx->obj_l[id]->expl = 0;
	int i = -1;
	while (++i < 4)
	{
		fd = open(water[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->obj_l[id]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[id]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[id]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, water[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_firepot(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 4;
	char *pot[4] = { "textures/obj/firepot/firepot1.xpm", "textures/obj/firepot/firepot2.xpm",
						"textures/obj/firepot/firepot3.xpm", "textures/obj/firepot/firepot4.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 4);
	mlx->obj_l[id]->anim_n = 4;
	mlx->obj_l[id]->delay = 6;
	mlx->obj_l[id]->expl = 0;
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
		mlx->obj_l[id]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[id]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[id]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, pot[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_anim_obj(t_mlx *mlx)
{
	ft_init_firepot(mlx);
	ft_init_water(mlx);
	ft_init_canister(mlx);
	ft_init_fire_a(mlx);
}

void	ft_init_static_obj(t_mlx *mlx)
{
	int fd;
	char *line;
	char *objs[4] = { "textures/obj/static/barrel.xpm", "textures/obj/static/backpack.xpm", "textures/obj/static/cacodemon.xpm",
						"textures/obj/static/canister01.xpm" };
	int i = -1;
	while (++i < 4)
	{
		fd = open(objs[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->obj_l[i] = (t_anim_list*)malloc(sizeof(t_anim_list));
		mlx->obj_l[i]->anim = (t_img**)malloc(sizeof(t_img));
		mlx->obj_l[i]->anim[0] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[i]->anim[0]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[i]->anim[0]->h = ft_atoi(tmp[1]);
		mlx->obj_l[i]->anim[0]->img = mlx_xpm_file_to_image(mlx->mlx, objs[i], &mlx->obj_l[i]->anim[0]->w, &mlx->obj_l[i]->anim[0]->h);
		mlx->obj_l[i]->anim[0]->data = (int*)mlx_get_data_addr(mlx->obj_l[i]->anim[0]->img, &mlx->obj_l[i]->anim[0]->bpp, &mlx->obj_l[i]->anim[0]->size_line, &mlx->obj_l[i]->anim[0]->endian);
		mlx->obj_l[i]->anim_n = 1;
		mlx->obj_l[i]->expl = 0;
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_scaler(t_mlx *mlx)
{
	mlx->obj_l[0]->scaler = 2.5f;
	mlx->obj_l[1]->scaler = 4.5f;
	mlx->obj_l[2]->scaler = -4.5f;
	mlx->obj_l[3]->scaler = 2.0f;
	mlx->obj_l[4]->scaler = 2.0f;
	mlx->obj_l[5]->scaler = -10.0f;
	mlx->obj_l[6]->scaler = 2.0f;
	mlx->obj_l[7]->scaler = 2.5;

	mlx->obj_l[0]->aspect_scaler = 1.0f;
	mlx->obj_l[1]->aspect_scaler = 0.95f;
	mlx->obj_l[2]->aspect_scaler = 1.25f;
	mlx->obj_l[3]->aspect_scaler = 1.0f;
	mlx->obj_l[4]->aspect_scaler = 1.5f;
	mlx->obj_l[5]->aspect_scaler = 1.0f;
	mlx->obj_l[6]->aspect_scaler = 1.0f;
	mlx->obj_l[7]->aspect_scaler = 1.5f;

	mlx->obj_l[3]->expl = 1;
}

void	ft_init_obj(t_mlx *mlx)
{
	mlx->obj_l = (t_anim_list**)malloc(sizeof(t_anim_list*) * OBJ);
	ft_init_static_obj(mlx);
	ft_init_anim_obj(mlx);
	ft_init_scaler(mlx);
}
