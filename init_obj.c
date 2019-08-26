/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_obj.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/11 13:43:09 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/26 20:11:34 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_hp_boost(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 16;
	char *boost[23] = { "textures/obj/hp_boost/hp_boost01.xpm", "textures/obj/hp_boost/hp_boost02.xpm", "textures/obj/hp_boost/hp_boost03.xpm",
						"textures/obj/hp_boost/hp_boost04.xpm", "textures/obj/hp_boost/hp_boost05.xpm", "textures/obj/hp_boost/hp_boost06.xpm",
						"textures/obj/hp_boost/hp_boost07.xpm", "textures/obj/hp_boost/hp_boost08.xpm", "textures/obj/hp_boost/hp_boost09.xpm",
						"textures/obj/hp_boost/hp_boost10.xpm", "textures/obj/hp_boost/hp_boost11.xpm", "textures/obj/hp_boost/hp_boost12.xpm",
						"textures/obj/hp_boost/hp_boost11.xpm", "textures/obj/hp_boost/hp_boost10.xpm", "textures/obj/hp_boost/hp_boost09.xpm",
						"textures/obj/hp_boost/hp_boost08.xpm", "textures/obj/hp_boost/hp_boost07.xpm", "textures/obj/hp_boost/hp_boost06.xpm",
						"textures/obj/hp_boost/hp_boost05.xpm", "textures/obj/hp_boost/hp_boost04.xpm", "textures/obj/hp_boost/hp_boost03.xpm",
						"textures/obj/hp_boost/hp_boost02.xpm", "textures/obj/hp_boost/hp_boost01.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 23);
	mlx->obj_l[id]->anim_n = 23;
	mlx->obj_l[id]->delay = 4;
	mlx->obj_l[id]->expl = 0;
	int i = -1;
	while (++i < 23)
	{
		fd = open(boost[i], O_RDONLY);
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
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, boost[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_speed_boost(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 17;
	char *boost[7] = { "textures/obj/speed_boost/speed_boost01.xpm", "textures/obj/speed_boost/speed_boost02.xpm", "textures/obj/speed_boost/speed_boost03.xpm",
						"textures/obj/speed_boost/speed_boost04.xpm", "textures/obj/speed_boost/speed_boost03.xpm", "textures/obj/speed_boost/speed_boost02.xpm",
						"textures/obj/speed_boost/speed_boost01.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 7);
	mlx->obj_l[id]->anim_n = 7;
	mlx->obj_l[id]->delay = 13;
	mlx->obj_l[id]->expl = 0;
	int i = -1;
	while (++i < 7)
	{
		fd = open(boost[i], O_RDONLY);
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
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, boost[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_backpack(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 12;
	char *backpack[6] = { "textures/obj/backpack/backpack01.xpm", "textures/obj/backpack/backpack02.xpm", "textures/obj/backpack/backpack03.xpm",
							"textures/obj/backpack/backpack04.xpm", "textures/obj/backpack/backpack05.xpm", "textures/obj/backpack/backpack06.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 6);
	mlx->obj_l[id]->anim_n = 6;
	mlx->obj_l[id]->delay = 8;
	mlx->obj_l[id]->expl = 0;
	int i = -1;
	while (++i < 6)
	{
		fd = open(backpack[i], O_RDONLY);
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
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, backpack[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_mouse(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 11;
	char *mouse[2] = { "textures/obj/mouse/mouse01.xpm", "textures/obj/mouse/mouse02.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 2);
	mlx->obj_l[id]->anim_n = 2;
	mlx->obj_l[id]->delay = 30;
	mlx->obj_l[id]->expl = 0;
	int i = -1;
	while (++i < 2)
	{
		fd = open(mouse[i], O_RDONLY);
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
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, mouse[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_hog(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 10;
	char *hog[8] = { "textures/obj/rotatable/hog/hog0.xpm", "textures/obj/rotatable/hog/hog45.xpm", "textures/obj/rotatable/hog/hog90.xpm",
						"textures/obj/rotatable/hog/hog135.xpm", "textures/obj/rotatable/hog/hog180.xpm", "textures/obj/rotatable/hog/hog225.xpm",
						"textures/obj/rotatable/hog/hog270.xpm", "textures/obj/rotatable/hog/hog315.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim_n = 1;
	mlx->obj_l[id]->expl = 0;

	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*));
	mlx->obj_l[id]->anim[0] = (t_img*)malloc(sizeof(t_img));
	fd = open(hog[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	mlx->obj_l[id]->anim[0]->w = ft_atoi(&tmp[0][1]);
	mlx->obj_l[id]->anim[0]->h = ft_atoi(tmp[1]);
	mlx->obj_l[id]->anim[0]->img = mlx_xpm_file_to_image(mlx->mlx, hog[0], &mlx->obj_l[id]->anim[0]->w, &mlx->obj_l[id]->anim[0]->h);
	mlx->obj_l[id]->anim[0]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[0]->img, &mlx->obj_l[id]->anim[0]->bpp, &mlx->obj_l[id]->anim[0]->size_line, &mlx->obj_l[id]->anim[0]->endian);
	ft_strsplit_free(tmp);
	close(fd);
	ft_strdel(&line);

	mlx->obj_l[id]->rot = (t_img**)malloc(sizeof(t_img*) * 8);
	int i = -1;
	while (++i < 8)
	{
		fd = open(hog[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		tmp = ft_strsplit(line, ' ');
		mlx->obj_l[id]->rot[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[id]->rot[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[id]->rot[i]->h = ft_atoi(tmp[1]);
		mlx->obj_l[id]->rot[i]->img = mlx_xpm_file_to_image(mlx->mlx, hog[i], &mlx->obj_l[id]->rot[i]->w, &mlx->obj_l[id]->rot[i]->h);
		mlx->obj_l[id]->rot[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->rot[i]->img, &mlx->obj_l[id]->rot[i]->bpp, &mlx->obj_l[id]->rot[i]->size_line, &mlx->obj_l[id]->rot[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_chair(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 9;
	char *chair[8] = { "textures/obj/rotatable/chair/chair0.xpm", "textures/obj/rotatable/chair/chair45.xpm", "textures/obj/rotatable/chair/chair90.xpm",
						"textures/obj/rotatable/chair/chair135.xpm", "textures/obj/rotatable/chair/chair180.xpm", "textures/obj/rotatable/chair/chair225.xpm",
						"textures/obj/rotatable/chair/chair270.xpm", "textures/obj/rotatable/chair/chair315.xpm"};
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim_n = 1;
	mlx->obj_l[id]->expl = 0;

	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*));
	mlx->obj_l[id]->anim[0] = (t_img*)malloc(sizeof(t_img));
	fd = open(chair[0], O_RDONLY);
	int j = -1;
	while (++j < 4)
	{
		get_next_line(fd, &line);
		(j < 3) ? ft_strdel(&line) : 1;
	}
	char **tmp = ft_strsplit(line, ' ');
	mlx->obj_l[id]->anim[0]->w = ft_atoi(&tmp[0][1]);
	mlx->obj_l[id]->anim[0]->h = ft_atoi(tmp[1]);
	mlx->obj_l[id]->anim[0]->img = mlx_xpm_file_to_image(mlx->mlx, chair[0], &mlx->obj_l[id]->anim[0]->w, &mlx->obj_l[id]->anim[0]->h);
	mlx->obj_l[id]->anim[0]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[0]->img, &mlx->obj_l[id]->anim[0]->bpp, &mlx->obj_l[id]->anim[0]->size_line, &mlx->obj_l[id]->anim[0]->endian);
	ft_strsplit_free(tmp);
	close(fd);
	ft_strdel(&line);

	mlx->obj_l[id]->rot = (t_img**)malloc(sizeof(t_img*) * 8);
	int i = -1;
	while (++i < 8)
	{
		fd = open(chair[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		tmp = ft_strsplit(line, ' ');
		mlx->obj_l[id]->rot[i] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[id]->rot[i]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[id]->rot[i]->h = ft_atoi(tmp[1]);
		mlx->obj_l[id]->rot[i]->img = mlx_xpm_file_to_image(mlx->mlx, chair[i], &mlx->obj_l[id]->rot[i]->w, &mlx->obj_l[id]->rot[i]->h);
		mlx->obj_l[id]->rot[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->rot[i]->img, &mlx->obj_l[id]->rot[i]->bpp, &mlx->obj_l[id]->rot[i]->size_line, &mlx->obj_l[id]->rot[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_explosion(t_mlx *mlx)
{
	int fd;
	char *line;
	int id = 8;
	char *expl[21] = { "textures/obj/explosion/explosion01.xpm", "textures/obj/explosion/explosion02.xpm", "textures/obj/explosion/explosion03.xpm",
						"textures/obj/explosion/explosion04.xpm", "textures/obj/explosion/explosion05.xpm", "textures/obj/explosion/explosion06.xpm",
						"textures/obj/explosion/explosion07.xpm", "textures/obj/explosion/explosion08.xpm", "textures/obj/explosion/explosion09.xpm",
						"textures/obj/explosion/explosion10.xpm", "textures/obj/explosion/explosion11.xpm", "textures/obj/explosion/explosion12.xpm",
						"textures/obj/explosion/explosion13.xpm", "textures/obj/explosion/explosion14.xpm", "textures/obj/explosion/explosion15.xpm",
						"textures/obj/explosion/explosion16.xpm", "textures/obj/explosion/explosion17.xpm", "textures/obj/explosion/explosion18.xpm",
						"textures/obj/explosion/explosion19.xpm", "textures/obj/explosion/explosion20.xpm", "textures/obj/explosion/explosion21.xpm" };
	mlx->obj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->obj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 21);
	mlx->obj_l[id]->anim_n = 21;
	mlx->obj_l[id]->delay = 5;
	mlx->obj_l[id]->expl = 1;
	int i = -1;
	while (++i < 21)
	{
		fd = open(expl[i], O_RDONLY);
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
		mlx->obj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, expl[i], &mlx->obj_l[id]->anim[i]->w, &mlx->obj_l[id]->anim[i]->h);
		mlx->obj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->obj_l[id]->anim[i]->img, &mlx->obj_l[id]->anim[i]->bpp, &mlx->obj_l[id]->anim[i]->size_line, &mlx->obj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

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

void	ft_init_static_obj_next(t_mlx *mlx)
{
	int fd;
	char *line;
	char *objs[3] = { "textures/obj/static/ammo_crate1.xpm", "textures/obj/static/ammo_crate2.xpm", "textures/obj/static/shotgun_ammo.xpm" };
	int i = 12;
	while (++i < 16)
	{
		fd = open(objs[i - 13], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->obj_l[i] = (t_anim_list*)malloc(sizeof(t_anim_list));
		mlx->obj_l[i]->anim = (t_img**)malloc(sizeof(t_img*));
		mlx->obj_l[i]->anim[0] = (t_img*)malloc(sizeof(t_img));
		mlx->obj_l[i]->anim[0]->w = ft_atoi(&tmp[0][1]);
		mlx->obj_l[i]->anim[0]->h = ft_atoi(tmp[1]);
		mlx->obj_l[i]->anim[0]->img = mlx_xpm_file_to_image(mlx->mlx, objs[i - 13], &mlx->obj_l[i]->anim[0]->w, &mlx->obj_l[i]->anim[0]->h);
		mlx->obj_l[i]->anim[0]->data = (int*)mlx_get_data_addr(mlx->obj_l[i]->anim[0]->img, &mlx->obj_l[i]->anim[0]->bpp, &mlx->obj_l[i]->anim[0]->size_line, &mlx->obj_l[i]->anim[0]->endian);
		mlx->obj_l[i]->anim_n = 1;
		mlx->obj_l[i]->expl = 0;
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_static_obj(t_mlx *mlx)
{
	int fd;
	char *line;
	char *objs[4] = { "textures/obj/static/barrel.xpm", "textures/obj/static/ammo_crate.xpm", "textures/obj/static/cacodemon.xpm",
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
		mlx->obj_l[i]->anim = (t_img**)malloc(sizeof(t_img*));
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

void	ft_init_obj_specs(t_mlx *mlx)
{
	mlx->obj_l[0]->scaler = 2.5f;
	mlx->obj_l[1]->scaler = 5.75f;
	mlx->obj_l[2]->scaler = -4.5f;
	mlx->obj_l[3]->scaler = 2.0f;
	mlx->obj_l[4]->scaler = 2.0f;
	mlx->obj_l[5]->scaler = -10.0f;
	mlx->obj_l[6]->scaler = 2.0f;
	mlx->obj_l[7]->scaler = 2.5;
	mlx->obj_l[8]->scaler = -1.0f;
	mlx->obj_l[9]->scaler = 3.5f;
	mlx->obj_l[10]->scaler = -1.0f;
	mlx->obj_l[11]->scaler = 6.0f;
	mlx->obj_l[12]->scaler = 4.0f;
	mlx->obj_l[13]->scaler = 6.0f;
	mlx->obj_l[14]->scaler = 5.5;
	mlx->obj_l[15]->scaler = 6.0f;
	mlx->obj_l[16]->scaler = 4.5f;
	mlx->obj_l[17]->scaler = 5.5f;

	mlx->obj_l[0]->aspect_scaler = 1.0f;
	mlx->obj_l[1]->aspect_scaler = 0.95f;
	mlx->obj_l[2]->aspect_scaler = 1.25f;
	mlx->obj_l[3]->aspect_scaler = 1.0f;
	mlx->obj_l[4]->aspect_scaler = 1.5f;
	mlx->obj_l[5]->aspect_scaler = 1.0f;
	mlx->obj_l[6]->aspect_scaler = 1.0f;
	mlx->obj_l[7]->aspect_scaler = 1.5f;
	mlx->obj_l[8]->aspect_scaler = 1.0f;
	mlx->obj_l[9]->aspect_scaler = 1.0f;
	mlx->obj_l[10]->aspect_scaler = 1.0f;
	mlx->obj_l[11]->aspect_scaler = 1.0f;
	mlx->obj_l[12]->aspect_scaler = 1.0f;
	mlx->obj_l[13]->aspect_scaler = 1.0f;
	mlx->obj_l[14]->aspect_scaler = 1.0f;
	mlx->obj_l[15]->aspect_scaler = 1.0f;
	mlx->obj_l[16]->aspect_scaler = 1.0f;
	mlx->obj_l[17]->aspect_scaler = 1.0f;

	mlx->obj_l[0]->col_w = 1.0f;
	mlx->obj_l[3]->col_w = 0.75f;

	mlx->obj_l[3]->expl = 1;

	mlx->obj_l[0]->can_rotate = 0;
	mlx->obj_l[1]->can_rotate = 0;
	mlx->obj_l[2]->can_rotate = 0;
	mlx->obj_l[3]->can_rotate = 0;
	mlx->obj_l[4]->can_rotate = 0;
	mlx->obj_l[5]->can_rotate = 0;
	mlx->obj_l[6]->can_rotate = 0;
	mlx->obj_l[7]->can_rotate = 0;
	mlx->obj_l[8]->can_rotate = 0;
	mlx->obj_l[9]->can_rotate = 1;
	mlx->obj_l[10]->can_rotate = 1;
	mlx->obj_l[11]->can_rotate = 0;
	mlx->obj_l[12]->can_rotate = 0;
	mlx->obj_l[13]->can_rotate = 0;
	mlx->obj_l[14]->can_rotate = 0;
	mlx->obj_l[15]->can_rotate = 0;
	mlx->obj_l[16]->can_rotate = 0;
	mlx->obj_l[17]->can_rotate = 0;

	mlx->obj_l[0]->is_collectable = 0;
	mlx->obj_l[1]->is_collectable = 1;
	mlx->obj_l[2]->is_collectable = 0;
	mlx->obj_l[3]->is_collectable = 0;
	mlx->obj_l[4]->is_collectable = 0;
	mlx->obj_l[5]->is_collectable = 0;
	mlx->obj_l[6]->is_collectable = 0;
	mlx->obj_l[7]->is_collectable = 0;
	mlx->obj_l[8]->is_collectable = 0;
	mlx->obj_l[9]->is_collectable = 0;
	mlx->obj_l[10]->is_collectable = 0;
	mlx->obj_l[11]->is_collectable = 0;
	mlx->obj_l[12]->is_collectable = 1;
	mlx->obj_l[13]->is_collectable = 1;
	mlx->obj_l[14]->is_collectable = 1;
	mlx->obj_l[15]->is_collectable = 1;
	mlx->obj_l[16]->is_collectable = 1;
	mlx->obj_l[17]->is_collectable = 1;

	int i = -1;
	while (++i < 16)
		mlx->obj_l[i]->is_boost = 0;
	mlx->obj_l[16]->is_boost = 1;
	mlx->obj_l[17]->is_boost = 1;
}

void	ft_init_rot_obj(t_mlx *mlx)
{
	ft_init_chair(mlx);
	ft_init_hog(mlx);
}

void	ft_init_anim_obj(t_mlx *mlx)
{
	ft_init_firepot(mlx);
	ft_init_water(mlx);
	ft_init_canister(mlx);
	ft_init_fire_a(mlx);
	ft_init_explosion(mlx);
	ft_init_mouse(mlx);
	ft_init_backpack(mlx);
	ft_init_speed_boost(mlx);
	ft_init_hp_boost(mlx);
}

void	ft_init_obj(t_mlx *mlx)
{
	mlx->obj_l = (t_anim_list**)malloc(sizeof(t_anim_list*) * OBJ);
	ft_init_static_obj(mlx);
	ft_init_static_obj_next(mlx);
	ft_init_anim_obj(mlx);
	ft_init_rot_obj(mlx);
	ft_init_obj_specs(mlx);
}
