/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wobj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 15:19:18 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/22 13:35:08 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_switcher(t_mlx *mlx)
{
	int fd;
	int id = 8;
	char *line;
	char *switcher[2] = { "textures/wall_obj/switcher/switcher_up.xpm", "textures/wall_obj/switcher/switcher_down.xpm" };
	mlx->wobj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->wobj_l[id]->wobj_specs = (t_wobj_specs*)malloc(sizeof(t_wobj_specs));
	mlx->wobj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 2);
	mlx->wobj_l[id]->anim_n = 2;
	mlx->wobj_l[id]->delay = 0;
	mlx->wobj_l[id]->expl = 0;
	int i = -1;
	while (++i < 2)
	{
		fd = open(switcher[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->wobj_l[id]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->wobj_l[id]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->wobj_l[id]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->wobj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, switcher[i], &mlx->wobj_l[id]->anim[i]->w, &mlx->wobj_l[id]->anim[i]->h);
		mlx->wobj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->wobj_l[id]->anim[i]->img, &mlx->wobj_l[id]->anim[i]->bpp, &mlx->wobj_l[id]->anim[i]->size_line, &mlx->wobj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_axeanim(t_mlx *mlx)
{
	int fd;
	int id = 7;
	char *line;
	char *axe_anim[2] = { "textures/wall_obj/axe_anim/axe_anim01.xpm", "textures/wall_obj/axe_anim/axe_anim02.xpm" };
	mlx->wobj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->wobj_l[id]->wobj_specs = (t_wobj_specs*)malloc(sizeof(t_wobj_specs));
	mlx->wobj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 2);
	mlx->wobj_l[id]->anim_n = 2;
	mlx->wobj_l[id]->delay = 7;
	mlx->wobj_l[id]->expl = 0;
	int i = -1;
	while (++i < 2)
	{
		fd = open(axe_anim[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->wobj_l[id]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->wobj_l[id]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->wobj_l[id]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->wobj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, axe_anim[i], &mlx->wobj_l[id]->anim[i]->w, &mlx->wobj_l[id]->anim[i]->h);
		mlx->wobj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->wobj_l[id]->anim[i]->img, &mlx->wobj_l[id]->anim[i]->bpp, &mlx->wobj_l[id]->anim[i]->size_line, &mlx->wobj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_radar(t_mlx *mlx)
{
	int fd;
	int id = 6;
	char *line;
	char *radar[6] = { "textures/wall_obj/radar/radar01.xpm", "textures/wall_obj/radar/radar02.xpm", "textures/wall_obj/radar/radar03.xpm",
						"textures/wall_obj/radar/radar04.xpm", "textures/wall_obj/radar/radar05.xpm", "textures/wall_obj/radar/radar06.xpm" };
	mlx->wobj_l[id] = (t_anim_list*)malloc(sizeof(t_anim_list));
	mlx->wobj_l[id]->wobj_specs = (t_wobj_specs*)malloc(sizeof(t_wobj_specs));
	mlx->wobj_l[id]->anim = (t_img**)malloc(sizeof(t_img*) * 6);
	mlx->wobj_l[id]->anim_n = 6;
	mlx->wobj_l[id]->delay = 8;
	mlx->wobj_l[id]->expl = 0;
	int i = -1;
	while (++i < 6)
	{
		fd = open(radar[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->wobj_l[id]->anim[i] = (t_img*)malloc(sizeof(t_img));
		mlx->wobj_l[id]->anim[i]->w = ft_atoi(&tmp[0][1]);
		mlx->wobj_l[id]->anim[i]->h = ft_atoi(tmp[1]);
		mlx->wobj_l[id]->anim[i]->img = mlx_xpm_file_to_image(mlx->mlx, radar[i], &mlx->wobj_l[id]->anim[i]->w, &mlx->wobj_l[id]->anim[i]->h);
		mlx->wobj_l[id]->anim[i]->data = (int*)mlx_get_data_addr(mlx->wobj_l[id]->anim[i]->img, &mlx->wobj_l[id]->anim[i]->bpp, &mlx->wobj_l[id]->anim[i]->size_line, &mlx->wobj_l[id]->anim[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_static_wobj(t_mlx *mlx)
{
	int fd;
	char *line;
	char *wobj[6] = { "textures/wall_obj/static/puppy_pic.xpm", "textures/wall_obj/static/dog_pic.xpm", "textures/wall_obj/static/w_blood1.xpm",
						"textures/wall_obj/static/w_blood2.xpm", "textures/wall_obj/static/bullet_hole01.xpm", "textures/wall_obj/static/bullet_hole02.xpm"};
	int i = -1;
	while (++i < 6)
	{
		fd = open(wobj[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->wobj_l[i] = (t_anim_list*)malloc(sizeof(t_anim_list));
		mlx->wobj_l[i]->wobj_specs = (t_wobj_specs*)malloc(sizeof(t_wobj_specs));
		mlx->wobj_l[i]->anim = (t_img**)malloc(sizeof(t_img*));
		mlx->wobj_l[i]->anim[0] = (t_img*)malloc(sizeof(t_img));
		mlx->wobj_l[i]->anim[0]->w = ft_atoi(&tmp[0][1]);
		mlx->wobj_l[i]->anim[0]->h = ft_atoi(tmp[1]);
		mlx->wobj_l[i]->anim[0]->img = mlx_xpm_file_to_image(mlx->mlx, wobj[i], &mlx->wobj_l[i]->anim[0]->w, &mlx->wobj_l[i]->anim[0]->h);
		mlx->wobj_l[i]->anim[0]->data = (int*)mlx_get_data_addr(mlx->wobj_l[i]->anim[0]->img, &mlx->wobj_l[i]->anim[0]->bpp, &mlx->wobj_l[i]->anim[0]->size_line, &mlx->wobj_l[i]->anim[0]->endian);
		mlx->wobj_l[i]->anim_n = 1;
		mlx->wobj_l[i]->expl = 0;
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_wobj_specs(t_mlx *mlx)
{
	mlx->wobj_l[0]->wobj_specs->abs_w = 0.75f;
	mlx->wobj_l[0]->wobj_specs->abs_h = 2.0f;
	mlx->wobj_l[0]->wobj_specs->u0 = 0;
	mlx->wobj_l[0]->wobj_specs->u1 = 32;
	mlx->wobj_l[0]->wobj_specs->is_switcher = 0;

	mlx->wobj_l[1]->wobj_specs->abs_w = 1.5;
	mlx->wobj_l[1]->wobj_specs->abs_h = 5.0f;
	mlx->wobj_l[1]->wobj_specs->aspect_ratio = (double)(1.5f / 5.0f);
	mlx->wobj_l[1]->wobj_specs->u0 = 0;
	mlx->wobj_l[1]->wobj_specs->u1 = 64;
	mlx->wobj_l[1]->wobj_specs->is_switcher = 0;

	mlx->wobj_l[2]->wobj_specs->abs_w = 1.5;
	mlx->wobj_l[2]->wobj_specs->abs_h = 5.0f;
	mlx->wobj_l[2]->wobj_specs->u0 = 1;
	mlx->wobj_l[2]->wobj_specs->u1 = 39;
	mlx->wobj_l[2]->wobj_specs->is_switcher = 0;

	mlx->wobj_l[3]->wobj_specs->abs_w = 1.75;
	mlx->wobj_l[3]->wobj_specs->abs_h = 5.0f;
	mlx->wobj_l[3]->wobj_specs->u0 = 0;
	mlx->wobj_l[3]->wobj_specs->u1 = 44;
	mlx->wobj_l[3]->wobj_specs->is_switcher = 0;

	mlx->wobj_l[4]->wobj_specs->abs_w = 0.1;
	mlx->wobj_l[4]->wobj_specs->abs_h = 0.35;
	mlx->wobj_l[4]->wobj_specs->u0 = 0;
	mlx->wobj_l[4]->wobj_specs->u1 = 60;
	mlx->wobj_l[4]->wobj_specs->is_switcher = 0;

	mlx->wobj_l[6]->wobj_specs->abs_w = 2.0f;
	mlx->wobj_l[6]->wobj_specs->abs_h = 5.0;
	mlx->wobj_l[6]->wobj_specs->u0 = 0;
	mlx->wobj_l[6]->wobj_specs->u1 = 64;
	mlx->wobj_l[6]->wobj_specs->is_switcher = 0;

	mlx->wobj_l[7]->wobj_specs->abs_w = 1.0f;
	mlx->wobj_l[7]->wobj_specs->abs_h = 2.5;
	mlx->wobj_l[7]->wobj_specs->u0 = 0;
	mlx->wobj_l[7]->wobj_specs->u1 = 64;
	mlx->wobj_l[7]->wobj_specs->is_switcher = 0;

	mlx->wobj_l[8]->wobj_specs->abs_w = 0.25f;
	mlx->wobj_l[8]->wobj_specs->abs_h = 1.25f;
	mlx->wobj_l[8]->wobj_specs->u0 = 0;
	mlx->wobj_l[8]->wobj_specs->u1 = 31;
	mlx->wobj_l[8]->wobj_specs->is_switcher = 1;
}

void	ft_init_wobj(t_mlx *mlx)
{
	mlx->wobj_l = (t_anim_list**)malloc(sizeof(t_anim_list*) * WOBJ);
	ft_init_static_wobj(mlx);
	ft_init_radar(mlx);
	ft_init_axeanim(mlx);
	ft_init_switcher(mlx);

	ft_init_wobj_specs(mlx);
}
