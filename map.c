/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:44:25 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/03 22:56:03 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double	ft_datoi(char *str)
{
	int len, dot;
	double res;

	res = 0;
	dot = 0;
	len = ft_strlen(str);
	while (str[len - 1])
	{
		if (str[len - 1] == '.')
		{
			dot = 1;
			break ;
		}
		res = res / 10 + (str[len - 1] - '0');
		len--;
	}
	res /= 10;
	if (!dot)
		return (ft_atoi(str));
	if (str[0] == '-')
	{
		res -= ft_atoi(str);
		res *= -1;
	}
	else
		res += ft_atoi(str);
	return (res);
}

void	ft_load_map(t_mlx *mlx, char *map_file)
{
	int v = 1;
	int s = 1;
	
	char *line;
	int fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return ;
	
	char **temp;

	t_vec2 **verts, **tmp_v;

	t_sector **tmp_s;

	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			temp = ft_strsplit(line, ' ');
			if (v > 1)
			{
				tmp_v = (t_vec2**)malloc(sizeof(t_vec2*) * (v - 1));
				int j = v - 2;
				while (j >= 0)
				{
					tmp_v[j] = (t_vec2*)malloc(sizeof(t_vec2));
					ft_memcpy((void*)tmp_v[j], (const void*)verts[j], sizeof(t_vec2));
					free(verts[j]);
					j--;
				}
				free(verts);
				verts = (t_vec2**)malloc(sizeof(t_vec2*) * v);
				j = 0;
				while (j < v - 1)
				{
					verts[j] = (t_vec2*)malloc(sizeof(t_vec2));
					ft_memcpy((void*)verts[j], (const void*)tmp_v[j], sizeof(t_vec2));
					free(tmp_v[j]);
					j++;
				}
				free(tmp_v);
				verts[v - 1] = (t_vec2*)malloc(sizeof(t_vec2));
				verts[v - 1]->x = (double)ft_datoi(temp[1]);
				verts[v - 1]->y = (double)ft_datoi(temp[2]);
			}
			else
			{
				verts = (t_vec2**)malloc(sizeof(t_vec2*) * 1);
				verts[0] = (t_vec2*)malloc(sizeof(t_vec2));
				verts[0]->x = (double)ft_datoi(temp[1]);
				verts[0]->y = (double)ft_datoi(temp[2]);
			}
			v++;
		}
		if (line[0] == 's' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			if (s > 1)
			{
				tmp_s = (t_sector**)malloc(sizeof(t_sector) * (s - 1));
				int j = s - 2;
				while (j >= 0)
				{
					tmp_s[j] = (t_sector*)malloc(sizeof(t_sector));
					ft_memcpy((void*)tmp_s[j], (const void*)mlx->sect[j], sizeof(t_sector));
					free(mlx->sect[j]);
					j--;
				}
				free(mlx->sect);
				mlx->sect = (t_sector**)malloc(sizeof(t_sector) * s);
				j = 0;
				while (j < s - 1)
				{
					mlx->sect[j] = (t_sector*)malloc(sizeof(t_sector));
					ft_memcpy((void*)mlx->sect[j], (const void*)tmp_s[j], sizeof(t_sector));
					free(tmp_s[j]);
					j++;
				}
				free(tmp_s);
				mlx->sect[s - 1] = (t_sector*)malloc(sizeof(t_sector));

				char **t;
				t = ft_strsplit(temp[1], ' ');
				mlx->sect[s - 1]->floor = (double)ft_datoi(t[0]);
				mlx->sect[s - 1]->ceiling = (double)ft_datoi(t[1]);

				t = ft_strsplit(temp[2], ' ');
				int v_count = 0;
				while (t[v_count])
					v_count++;
				mlx->sect[s - 1]->verts_count = v_count;
				mlx->sect[s - 1]->verts = (t_vec2**)malloc(sizeof(t_vec2*) * v_count);
				j = 0;
				while (j < v_count)
				{
					mlx->sect[s - 1]->verts[j] = (t_vec2*)malloc(sizeof(t_vec2));
					mlx->sect[s - 1]->verts[j]->x = (double)verts[ft_atoi(t[j])]->x;
					mlx->sect[s - 1]->verts[j]->y = (double)verts[ft_atoi(t[j])]->y;
					j++;
				}
			}
			else
			{
				mlx->sect = (t_sector**)malloc(sizeof(t_sector*) * 1);
				mlx->sect[0] = (t_sector*)malloc(sizeof(t_sector));
				
				char **t;
				t = ft_strsplit(temp[1], ' ');
				mlx->sect[0]->floor = (double)ft_datoi(t[0]);
				mlx->sect[0]->ceiling = (double)ft_datoi(t[1]);

				t = ft_strsplit(temp[2], ' ');
				int v_count = 0;
				while (t[v_count])
					v_count++;
				mlx->sect[0]->verts_count = v_count;
				mlx->sect[0]->verts = (t_vec2**)malloc(sizeof(t_vec2*) * v_count);
				int j = 0;
				while (j < v_count)
				{
					mlx->sect[0]->verts[j] = (t_vec2*)malloc(sizeof(t_vec2));
					mlx->sect[0]->verts[j]->x = (double)verts[ft_atoi(t[j])]->x;
					mlx->sect[0]->verts[j]->y = (double)verts[ft_atoi(t[j])]->y;
					j++;
				}
			}
			s++;
		}
		if (line[0] == 'p' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');

			mlx->player = (t_player*)malloc(sizeof(t_player));
			mlx->player->pos = (t_vec3*)malloc(sizeof(t_vec3));
			mlx->player->velocity = (t_vec3*)malloc(sizeof(t_vec3));

			mlx->player->eye_h = EYE_H;
			mlx->player->angle = (double)ft_datoi(temp[2]);
			mlx->player->sector = ft_atoi(temp[3]);

			char **t;
			t = ft_strsplit(temp[1], ' ');
			mlx->player->pos->x = (double)ft_datoi(t[0]);
			mlx->player->pos->y = (double)ft_datoi(t[1]);
			mlx->player->pos->z = (double)mlx->sect[mlx->player->sector]->floor + mlx->player->eye_h;

		}
	}
	close(fd);

	// int j = 0;
	// printf("verts %d\n", v - 1);
	// while (j < v - 1)
	// {
	// 	printf("x %f	y %f			%d\n", verts[j]->x, verts[j]->y, j);
	// 	j++;
	// }
	// printf("sect %d\n", s - 1);
	int j = 0;
	while (j < s - 1)
	{
		printf("sect %d\n\n", j);
		printf("v_count %d\n", mlx->sect[j]->verts_count);
		printf("floor %f	ceiling %f\n\n", mlx->sect[j]->floor, mlx->sect[j]->ceiling);
		int k = 0;
		while (k < mlx->sect[j]->verts_count)
		{
			printf("x %f	y %f\n", mlx->sect[j]->verts[k]->x, mlx->sect[j]->verts[k]->y);
			k++;
		}
		printf("________________________________\n", j);
		j++;
	}
}