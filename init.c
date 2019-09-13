/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 21:24:48 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/13 21:03:09 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_init_menu_fire(t_mlx *mlx)
{
	mlx->fire[0] = 0xDDDDDD;	//	0xFFFFFF
	mlx->fire[1] = 0x1F0707;
	mlx->fire[2] = 0x2F0E07;
	mlx->fire[3] = 0x470E07;
	mlx->fire[4] = 0x571706;
	mlx->fire[5] = 0x661F06;
	mlx->fire[6] = 0x761F06;
	mlx->fire[7] = 0x8F2706;
	mlx->fire[8] = 0x9F2F05;
	mlx->fire[9] = 0xAF3E06;
	mlx->fire[10] = 0xBE4708;
	mlx->fire[11] = 0xC74707;
	mlx->fire[12] = 0xDF4F05;
	mlx->fire[13] = 0xDF5707;
	mlx->fire[14] = 0xDF5707;
	mlx->fire[15] = 0xD75F06;
	mlx->fire[16] = 0xD6670F;
	mlx->fire[17] = 0xCF6F0F;
	mlx->fire[18] = 0xCF770D;
	mlx->fire[19] = 0xCF7E0E;
	mlx->fire[20] = 0xCF8717;
	mlx->fire[21] = 0xC78617;
	mlx->fire[22] = 0xC78F17;
	mlx->fire[23] = 0xC6971E;
	mlx->fire[24] = 0xBF9F1E;
	mlx->fire[25] = 0xBF9F1E;
	mlx->fire[26] = 0xBFA627;
	mlx->fire[27] = 0xBFA627;
	mlx->fire[28] = 0xBFAF2F;
	mlx->fire[29] = 0xB7AF2F;
	mlx->fire[30] = 0xB7B72E;
	mlx->fire[31] = 0xB7B737;
	mlx->fire[32] = 0xCFCF6F;
	mlx->fire[33] = 0xDFDF9F;
	mlx->fire[34] = 0xEEEFC7;
	mlx->fire[35] = 0xFFFFFF;
}

void	ft_init_menu_buttons(t_mlx *mlx)
{
	int fd;
	char *line;
	char *play[4] = { "textures/m_menu/font/p.xpm", "textures/m_menu/font/l.xpm", "textures/m_menu/font/a.xpm",
						"textures/m_menu/font/y.xpm" };
	char *quit[4] = { "textures/m_menu/font/q.xpm", "textures/m_menu/font/u.xpm", "textures/m_menu/font/_i.xpm",
						"textures/m_menu/font/t.xpm" };
	char *pointer[2] = { "textures/m_menu/font/pointer_l.xpm", "textures/m_menu/font/pointer_r.xpm" };
	int i = -1;
	while (++i < 4)
	{
		fd = open(play[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->menu_play[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->menu_play[i]->w = ft_atoi(&tmp[0][1]);
		mlx->menu_play[i]->h = ft_atoi(tmp[1]);
		mlx->menu_play[i]->img = mlx_xpm_file_to_image(mlx->mlx, play[i], &mlx->menu_play[i]->w, &mlx->menu_play[i]->h);
		mlx->menu_play[i]->data = (int*)mlx_get_data_addr(mlx->menu_play[i]->img, &mlx->menu_play[i]->bpp, &mlx->menu_play[i]->size_line, &mlx->menu_play[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}

	i = -1;
	while (++i < 4)
	{
		fd = open(quit[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->menu_quit[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->menu_quit[i]->w = ft_atoi(&tmp[0][1]);
		mlx->menu_quit[i]->h = ft_atoi(tmp[1]);
		mlx->menu_quit[i]->img = mlx_xpm_file_to_image(mlx->mlx, quit[i], &mlx->menu_quit[i]->w, &mlx->menu_quit[i]->h);
		mlx->menu_quit[i]->data = (int*)mlx_get_data_addr(mlx->menu_quit[i]->img, &mlx->menu_quit[i]->bpp, &mlx->menu_quit[i]->size_line, &mlx->menu_quit[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}

	i = -1;
	while (++i < 2)
	{
		fd = open(pointer[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->menu_pointer[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->menu_pointer[i]->w = ft_atoi(&tmp[0][1]);
		mlx->menu_pointer[i]->h = ft_atoi(tmp[1]);
		mlx->menu_pointer[i]->img = mlx_xpm_file_to_image(mlx->mlx, pointer[i], &mlx->menu_pointer[i]->w, &mlx->menu_pointer[i]->h);
		mlx->menu_pointer[i]->data = (int*)mlx_get_data_addr(mlx->menu_pointer[i]->img, &mlx->menu_pointer[i]->bpp, &mlx->menu_pointer[i]->size_line, &mlx->menu_pointer[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_menu_font(t_mlx *mlx)
{
	int fd;
	char *line;
	char *font[5] = { "textures/m_menu/font/D.xpm", "textures/m_menu/font/O.xpm", "textures/m_menu/font/M.xpm",
						"textures/m_menu/font/I.xpm", "textures/m_menu/font/C.xpm" };
	int i = -1;
	while (++i < 5)
	{
		fd = open(font[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->menu_font[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->menu_font[i]->w = ft_atoi(&tmp[0][1]);
		mlx->menu_font[i]->h = ft_atoi(tmp[1]);
		mlx->menu_font[i]->img = mlx_xpm_file_to_image(mlx->mlx, font[i], &mlx->menu_font[i]->w, &mlx->menu_font[i]->h);
		mlx->menu_font[i]->data = (int*)mlx_get_data_addr(mlx->menu_font[i]->img, &mlx->menu_font[i]->bpp, &mlx->menu_font[i]->size_line, &mlx->menu_font[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}

void	ft_init_font(t_mlx *mlx)
{
	int fd;
	char *line;
	char *font[FONT] = { "textures/font/_zero.xpm", "textures/font/_one.xpm", "textures/font/_two.xpm", "textures/font/_three.xpm",
						"textures/font/_four.xpm", "textures/font/_five.xpm", "textures/font/_six.xpm", "textures/font/_seven.xpm",
						"textures/font/_eight.xpm", "textures/font/_nine.xpm", "textures/font/_R.xpm", "textures/font/_plus.xpm",
						"textures/font/_J.xpm" };
	int i = -1;
	while (++i < FONT)
	{
		fd = open(font[i], O_RDONLY);
		int j = -1;
		while (++j < 4)
		{
			get_next_line(fd, &line);
			(j < 3) ? ft_strdel(&line) : 1;
		}
		char **tmp = ft_strsplit(line, ' ');
		(!(mlx->font[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
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
	char *sky[SKY] = { "textures/sky/sky.xpm" };
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
		(!(mlx->sky[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
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
	(!(mlx->trans = (t_anim_list**)malloc(sizeof(t_anim_list*) * TRANSPARENT))) ? ft_mem_error() : 1;
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
		(!(mlx->trans[i] = (t_anim_list*)malloc(sizeof(t_anim_list)))) ? ft_mem_error() : 1;
		(!(mlx->trans[i]->anim = (t_img**)malloc(sizeof(t_img*)))) ? ft_mem_error() : 1;
		mlx->trans[i]->anim_n = 1;
		mlx->trans[i]->expl = 0;
		(!(mlx->trans[i]->anim[0] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
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
	char *txts[TXT] = { "textures/walls/brick.xpm", "textures/walls/wall.xpm", "textures/walls/scifi_wall.xpm",
						"textures/walls/door.xpm" };
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
		(!(mlx->txt[i] = (t_img*)malloc(sizeof(t_img)))) ? ft_mem_error() : 1;
		mlx->txt[i]->w = ft_atoi(&tmp[0][1]);
		mlx->txt[i]->h = ft_atoi(tmp[1]);
		mlx->txt[i]->img = mlx_xpm_file_to_image(mlx->mlx, txts[i], &mlx->txt[i]->w, &mlx->txt[i]->h);
		mlx->txt[i]->data = (int*)mlx_get_data_addr(mlx->txt[i]->img, &mlx->txt[i]->bpp, &mlx->txt[i]->size_line, &mlx->txt[i]->endian);
		ft_strsplit_free(tmp);
		close(fd);
		ft_strdel(&line);
	}
}