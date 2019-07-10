/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:24:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/10 18:58:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_sky(t_mlx *mlx)
{
	int fd = 0;
	char *line = NULL;
	char *sky[SKY] = { "textures/sky/skybox.xpm" };
	int i = -1;
	while (++i < SKY)
	{
		fd = open(sky[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
			get_next_line(fd, &line);
		char **tmp = ft_strsplit(line, ' ');
		mlx->sky[i] = (t_img*)malloc(sizeof(t_img));
		mlx->sky[i]->w = ft_atoi(&tmp[0][1]);
		mlx->sky[i]->h = ft_atoi(tmp[1]);
		mlx->sky[i]->img = mlx_xpm_file_to_image(mlx->mlx, sky[i], &mlx->sky[i]->w, &mlx->sky[i]->h);
		mlx->sky[i]->data = (int*)mlx_get_data_addr(mlx->sky[i]->img, &mlx->sky[i]->bpp, &mlx->sky[i]->size_line, &mlx->sky[i]->endian);
		ft_strsplit_free(tmp);
		// close(fd);
	}
}

void	ft_init_textures(t_mlx *mlx)
{
	int fd = 0;
	char *line = NULL;
	char *txts[TXT] = { "textures/brick.xpm", "textures/wall.xpm", "textures/scifi_wall.xpm" };
	int i = -1;
	while (++i < TXT)
	{
		fd = open(txts[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
			get_next_line(fd, &line);
		char **tmp = ft_strsplit(line, ' ');
		mlx->txt[i] = (t_img*)malloc(sizeof(t_img));
		mlx->txt[i]->w = ft_atoi(&tmp[0][1]);
		mlx->txt[i]->h = ft_atoi(tmp[1]);
		mlx->txt[i]->img = mlx_xpm_file_to_image(mlx->mlx, txts[i], &mlx->txt[i]->w, &mlx->txt[i]->h);
		mlx->txt[i]->data = (int*)mlx_get_data_addr(mlx->txt[i]->img, &mlx->txt[i]->bpp, &mlx->txt[i]->size_line, &mlx->txt[i]->endian);
		ft_strsplit_free(tmp);
		// close(fd);
	}
}
