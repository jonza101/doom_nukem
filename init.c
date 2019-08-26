/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:24:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/26 18:13:25 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_font(t_mlx *mlx)
{
	int fd;
	char *line;
	char *font[12] = { "textures/font/_zero.xpm", "textures/font/_one.xpm", "textures/font/_two.xpm", "textures/font/_three.xpm",
						"textures/font/_four.xpm", "textures/font/_five.xpm", "textures/font/_six.xpm", "textures/font/_seven.xpm",
						"textures/font/_eight.xpm", "textures/font/_nine.xpm", "textures/font/_R.xpm", "textures/font/_plus.xpm" };
	int i = -1;
	while (++i < 12)
	{
		fd = open(font[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		mlx->font[i] = (t_img*)malloc(sizeof(t_img));
		mlx->font[i]->w = ft_atoi(&tmp[0][1]);
		mlx->font[i]->h = ft_atoi(tmp[1]);
		mlx->font[i]->img = mlx_xpm_file_to_image(mlx->mlx, font[i], &mlx->font[i]->w, &mlx->font[i]->h);
		mlx->font[i]->data = (int*)mlx_get_data_addr(mlx->font[i]->img, &mlx->font[i]->bpp, &mlx->font[i]->size_line, &mlx->font[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
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
	char *twall[TRANSPARENT] = { "textures/transparent/glass.xpm", "textures/transparent/bars.xpm", "textures/transparent/fence.xpm",
								"textures/transparent/breakable_wall_hole.xpm" };
	mlx->trans = (t_anim_list**)malloc(sizeof(t_anim_list*) * TRANSPARENT);
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
		mlx->trans[i] = (t_anim_list*)malloc(sizeof(t_anim_list));
		mlx->trans[i]->anim = (t_img**)malloc(sizeof(t_img*));
		mlx->trans[i]->anim_n = 1;
		mlx->trans[i]->expl = 0;
		mlx->trans[i]->anim[0] = (t_img*)malloc(sizeof(t_img));
		mlx->trans[i]->anim[0]->w = ft_atoi(&tmp[0][1]);
		mlx->trans[i]->anim[0]->h = ft_atoi(tmp[1]);
		mlx->trans[i]->anim[0]->img = mlx_xpm_file_to_image(mlx->mlx, twall[i], &mlx->trans[i]->anim[0]->w, &mlx->trans[i]->anim[0]->h);
		mlx->trans[i]->anim[0]->data = (int*)mlx_get_data_addr(mlx->trans[i]->anim[0]->img, &mlx->trans[i]->anim[0]->bpp, &mlx->trans[i]->anim[0]->size_line, &mlx->trans[i]->anim[0]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
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
