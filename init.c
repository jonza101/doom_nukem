/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:24:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/07/07 18:42:18 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_textures(t_mlx *mlx)
{
	int fd = 0;
	char *line = NULL;
	char *txt[TXT] = { "textures/brick.xpm", "textures/wall.xpm", "textures/scifi_wall.xpm" };
	int i = -1;
	while (++i < TXT)
	{
		fd = open(txt[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
			get_next_line(fd, &line);
		char **tmp = ft_strsplit(line, ' ');
		mlx->txt_temp[i] = (t_img*)malloc(sizeof(t_img));
		mlx->txt_temp[i]->w = ft_atoi(&tmp[0][1]);
		mlx->txt_temp[i]->h = ft_atoi(tmp[1]);
		mlx->txt_temp[i]->img = mlx_xpm_file_to_image(mlx->mlx, txt[i], &mlx->txt_temp[i]->w, &mlx->txt_temp[i]->h);
		mlx->txt_temp[i]->data = (int*)mlx_get_data_addr(mlx->txt_temp[i]->img, &mlx->txt_temp[i]->bpp, &mlx->txt_temp[i]->size_line, &mlx->txt_temp[i]->endian);
		// close(fd);
	}
}
