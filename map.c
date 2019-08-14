/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:25:41 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/14 19:44:44 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

int		ft_find_sect_mirror_side(t_mlx *mlx, int sector, int side, int sect_to_find)
{
	int s = -1;
	t_vec2 *v1;
	t_vec2 *v2;

	t_sector *sect = mlx->sect[sector];
	while (++s < sect->verts_count)
	{
		if (s == side)
		{
			v1 = sect->verts[s + 0];
			v2 = sect->verts[s + 1];
			break ;
		}
	}
	// printf("v1x %f		v1y %f\nv2x %f		v2y %f\n\n", v1->x, v1->y, v2->x, v2->y);
	t_sector *sect_to = mlx->sect[sect_to_find];
	s = 0;
	while (++s < sect_to->verts_count)
	{
		if (v1->x == sect_to->verts[s + 1]->x && v1->y == sect_to->verts[s + 1]->y
				&& v2->x == sect_to->verts[s + 0]->x && v2->y == sect_to->verts[s + 0]->y)
			return (s);
	}
	return (-1);
}

void	ft_strsplit_free(char **temp)
{
	int i;

	i = -1;
	while (temp[++i])
		free(temp[i]);
	free(temp);
}

//		UNSTABLE
double	ft_atof(char *str)
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
	int t = 1;
	int o = 1;
	int g = 1;		//	TRANSPARENT
	int seg = 1;
	
	char *line;
	int fd = open(map_file, O_RDONLY);
	if (fd < 0)
		return ;
	
	char **temp;

	t_vec2 **verts, **tmp_v;

	t_sector **tmp_s;

	t_img **tmp_t;

	t_obj *temp_obj, *prev;
	mlx->obj_count = 0;

	t_trans *temp_trans, *trans_prev;
	mlx->trans_count = 0;

	while (get_next_line(fd, &line))
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
					ft_memcpy(tmp_v[j], verts[j], sizeof(t_vec2));
					free(verts[j]);
					j--;
				}
				free(verts);
				verts = (t_vec2**)malloc(sizeof(t_vec2*) * v);
				j = 0;
				while (j < v - 1)
				{
					verts[j] = (t_vec2*)malloc(sizeof(t_vec2));
					ft_memcpy(verts[j], tmp_v[j], sizeof(t_vec2));
					free(tmp_v[j]);
					j++;
				}
				free(tmp_v);
				verts[v - 1] = (t_vec2*)malloc(sizeof(t_vec2));
				verts[v - 1]->x = (double)ft_atof(temp[2]);
				verts[v - 1]->y = (double)ft_atof(temp[1]);
			}
			else
			{
				verts = (t_vec2**)malloc(sizeof(t_vec2*) * 1);
				verts[0] = (t_vec2*)malloc(sizeof(t_vec2));
				verts[0]->x = (double)ft_atof(temp[2]);
				verts[0]->y = (double)ft_atof(temp[1]);
				int j = 0;
			}
			ft_strsplit_free(temp);
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
					ft_memcpy(tmp_s[j], mlx->sect[j], sizeof(t_sector));
					free(mlx->sect[j]);
					j--;
				}
				free(mlx->sect);
				mlx->sect = (t_sector**)malloc(sizeof(t_sector) * s);
				j = 0;
				while (j < s - 1)
				{
					mlx->sect[j] = (t_sector*)malloc(sizeof(t_sector));
					ft_memcpy(mlx->sect[j], tmp_s[j], sizeof(t_sector));
					free(tmp_s[j]);
					j++;
				}
				free(tmp_s);
				mlx->sect[s - 1] = (t_sector*)malloc(sizeof(t_sector));

				mlx->sect[s - 1]->txt_count = 0;

				char **t;
				t = ft_strsplit(temp[1], ' ');
				mlx->sect[s - 1]->floor = (double)ft_atof(t[0]);
				mlx->sect[s - 1]->ceiling = (double)ft_atof(t[1]);

				ft_strsplit_free(t);

				t = ft_strsplit(temp[2], ' ');
				int v_count = 0;
				while (t[v_count])
					v_count++;
				mlx->sect[s - 1]->verts_count = v_count;
				mlx->sect[s - 1]->verts = (t_vec2**)malloc(sizeof(t_vec2*) * (v_count + 1));
				j = -1;
				while (++j < v_count)
				{
					mlx->sect[s - 1]->verts[j + 1] = (t_vec2*)malloc(sizeof(t_vec2));
					mlx->sect[s - 1]->verts[j + 1]->x = (double)verts[ft_atoi(t[j])]->x;
					mlx->sect[s - 1]->verts[j + 1]->y = (double)verts[ft_atoi(t[j])]->y;
				}
				mlx->sect[s - 1]->verts[0] = (t_vec2*)malloc(sizeof(t_vec2));
				mlx->sect[s - 1]->verts[0]->x = (double)verts[ft_atoi(t[j - 1])]->x;
				mlx->sect[s - 1]->verts[0]->y = (double)verts[ft_atoi(t[j - 1])]->y;

				ft_strsplit_free(t);

				t = ft_strsplit(temp[3], ' ');
				int n_count = 0;
				while (t[n_count])
					n_count++;
				mlx->sect[s - 1]->neighbors_count = n_count;
				mlx->sect[s - 1]->neighbors = (char**)malloc(sizeof(char*) * n_count);
				j = 0;
				while (j < n_count)
				{
					mlx->sect[s - 1]->neighbors[j] = ft_strdup(t[j]);
					j++;
				}
				mlx->sect[s - 1]->ceil_txt = -1;
				mlx->sect[s - 1]->floor_txt = -1;

				ft_strsplit_free(t);
			}
			else
			{
				mlx->sect = (t_sector**)malloc(sizeof(t_sector*) * 1);
				mlx->sect[0] = (t_sector*)malloc(sizeof(t_sector));

				mlx->sect[0]->txt_count = 0;

				char **t;
				t = ft_strsplit(temp[1], ' ');
				mlx->sect[0]->floor = (double)ft_atof(t[0]);
				mlx->sect[0]->ceiling = (double)ft_atof(t[1]);

				ft_strsplit_free(t);

				t = ft_strsplit(temp[2], ' ');
				int v_count = 0;
				while (t[v_count])
					v_count++;
				mlx->sect[0]->verts_count = v_count;
				mlx->sect[0]->verts = (t_vec2**)malloc(sizeof(t_vec2*) * (v_count + 1));
				int j = 0;
				while (j < v_count)
				{
					mlx->sect[0]->verts[j + 1] = (t_vec2*)malloc(sizeof(t_vec2));
					mlx->sect[0]->verts[j + 1]->x = (double)verts[ft_atoi(t[j])]->x;
					mlx->sect[0]->verts[j + 1]->y = (double)verts[ft_atoi(t[j])]->y;
					j++;
				}
				mlx->sect[0]->verts[0] = (t_vec2*)malloc(sizeof(t_vec2));
				mlx->sect[0]->verts[0]->x = (double)verts[ft_atoi(t[j - 1])]->x;
				mlx->sect[0]->verts[0]->y = (double)verts[ft_atoi(t[j - 1])]->y;

				ft_strsplit_free(t);

				t = ft_strsplit(temp[3], ' ');
				int n_counts = 0;
				while (t[n_counts])
					n_counts++;
				mlx->sect[0]->neighbors_count = n_counts;
				mlx->sect[0]->neighbors = (char**)malloc(sizeof(char*) * n_counts);
				j = 0;
				while (j < n_counts)
				{
					mlx->sect[0]->neighbors[j] = ft_strdup(t[j]);
					j++;
				}
				mlx->sect[0]->ceil_txt = -1;
				mlx->sect[0]->floor_txt = -1;

				ft_strsplit_free(t);
			}
			ft_strsplit_free(temp);
			s++;
		}
		if (line[0] == 't' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			int tmp = ft_atoi(temp[1]);
			char **tmp_t = ft_strsplit(temp[3], ' ');
			int txt_count = 0;
			while (tmp_t[txt_count])
				txt_count++;
			mlx->sect[tmp]->texts = (char**)malloc(sizeof(char*) * txt_count);
			mlx->sect[tmp]->txt_count = txt_count;
			int j = -1;
			while (++j < txt_count)
				mlx->sect[tmp]->texts[j] = ft_strdup(tmp_t[j]);

			tmp_t = ft_strsplit(temp[2], ' ');
			mlx->sect[tmp]->floor_txt = ft_atoi(tmp_t[0]);
			mlx->sect[tmp]->ceil_txt = ft_atoi(tmp_t[1]);

			ft_strsplit_free(temp);
			ft_strsplit_free(tmp_t);
		}
		if (line[0] == 'o' && line[1] == '|')
		{
			if (o > 1)
			{
				mlx->obj_list->next = (t_obj*)malloc(sizeof(t_obj));
				mlx->obj_list->next->specs = (t_obj_specs*)malloc(sizeof(t_obj_specs));
				temp = ft_strsplit(line, '|');
				char **tmp_t = ft_strsplit(temp[2], ' ');
				mlx->obj_list->next->specs->sect = ft_atoi(temp[1]);
				mlx->obj_list->next->specs->x = ft_atof(tmp_t[0]);
				mlx->obj_list->next->specs->y = ft_atof(tmp_t[1]);
				mlx->obj_list->next->specs->obj_i = ft_atoi(temp[3]);
				mlx->obj_list->next->specs->frame = mlx->obj_l[mlx->obj_list->next->specs->obj_i]->anim[0];
				mlx->obj_list->next->specs->del = 0;
				mlx->obj_list->next->specs->anim_i = 0;
				mlx->obj_list->next->specs->expl_f = 0;
				mlx->obj_list = mlx->obj_list->next;
				mlx->obj_list->prev = prev;
				prev = mlx->obj_list;

				ft_strsplit_free(temp);
				ft_strsplit_free(tmp_t);
			}
			else
			{
				mlx->obj_list = (t_obj*)malloc(sizeof(t_obj));
				mlx->obj_list->specs = (t_obj_specs*)malloc(sizeof(t_obj_specs));
				temp = ft_strsplit(line, '|');
				char **tmp_t = ft_strsplit(temp[2], ' ');
				mlx->obj_list->specs->sect = ft_atoi(temp[1]);
				mlx->obj_list->specs->x = ft_atof(tmp_t[0]);
				mlx->obj_list->specs->y = ft_atof(tmp_t[1]);
				mlx->obj_list->specs->obj_i = ft_atoi(temp[3]);
				mlx->obj_list->specs->frame = mlx->obj_l[mlx->obj_list->specs->obj_i]->anim[0];
				mlx->obj_list->specs->del = 0;
				mlx->obj_list->specs->anim_i = 0;
				mlx->obj_list->specs->expl_f = 0;
				mlx->obj_list->prev = NULL;
				temp_obj = mlx->obj_list;
				prev = mlx->obj_list;

				ft_strsplit_free(temp);
				ft_strsplit_free(tmp_t);
			}
			o++;
			mlx->obj_count++;
		}
		if (line[0] == 'g' && line[1] == '|')
		{
			if (g > 1)
			{
				temp = ft_strsplit(line, '|');

				mlx->trans_list->next = (t_trans*)malloc(sizeof(t_trans));
				mlx->trans_list->next->sect = ft_atoi(temp[1]);
				mlx->trans_list->next->side = ft_atoi(temp[2]);
				mlx->trans_list->next->trans_i = ft_atoi(temp[3]);
				mlx->trans_list = mlx->trans_list->next;

				mlx->trans_list->prev = trans_prev;
				trans_prev = mlx->trans_list;

				mlx->trans_list->next = (t_trans*)malloc(sizeof(t_trans));
				int neigh_sect = ft_atoi(mlx->sect[mlx->trans_list->sect]->neighbors[mlx->trans_list->side]);
				int mirror_side = ft_find_sect_mirror_side(mlx, mlx->trans_list->sect, mlx->trans_list->side, neigh_sect);
				mlx->trans_list->next->sect = neigh_sect;
				mlx->trans_list->next->side = mirror_side;
				mlx->trans_list->next->trans_i = mlx->trans_list->trans_i;

				mlx->trans_list = mlx->trans_list->next;
				mlx->trans_list->prev = trans_prev;
				trans_prev = mlx->trans_list;

				ft_strsplit_free(temp);
			}
			else
			{
				temp = ft_strsplit(line, '|');

				mlx->trans_list = (t_trans*)malloc(sizeof(t_trans));
				mlx->trans_list->sect = ft_atoi(temp[1]);
				mlx->trans_list->side = ft_atoi(temp[2]);
				mlx->trans_list->trans_i = ft_atoi(temp[3]);

				mlx->trans_list->prev = NULL;
				temp_trans = mlx->trans_list;
				trans_prev = mlx->trans_list;

				mlx->trans_list->next = (t_trans*)malloc(sizeof(t_trans));
				int neigh_sect = ft_atoi(mlx->sect[mlx->trans_list->sect]->neighbors[mlx->trans_list->side]);
				int mirror_side = ft_find_sect_mirror_side(mlx, mlx->trans_list->sect, mlx->trans_list->side, neigh_sect);

				mlx->trans_list->next->sect = neigh_sect;
				mlx->trans_list->next->side = mirror_side;
				mlx->trans_list->next->trans_i = mlx->trans_list->trans_i;

				mlx->trans_list = mlx->trans_list->next;
				mlx->trans_list->prev = trans_prev;
				trans_prev = mlx->trans_list;

				ft_strsplit_free(temp);
			}
			g++;
			mlx->trans_count++;
		}
		if (line[0] == 'p' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');

			mlx->player->pos = (t_vec3*)malloc(sizeof(t_vec3));
			mlx->player->velocity = (t_vec3*)malloc(sizeof(t_vec3));

			mlx->player->eye_h = EYE_H;
			mlx->player->angle = (double)ft_atof(temp[2]);
			mlx->player->sector = ft_atoi(temp[3]);

			char **t;
			t = ft_strsplit(temp[1], ' ');
			mlx->player->pos->x = (double)ft_atof(t[0]);
			mlx->player->pos->y = (double)ft_atof(t[1]);
			mlx->player->pos->z = (double)mlx->sect[mlx->player->sector]->floor + mlx->player->eye_h;

			ft_strsplit_free(t);
			ft_strsplit_free(temp);
		}
		ft_strdel(&line);
	}
	close(fd);
	mlx->num_sec = s - 1;

	if (mlx->obj_count > 0)
	{
		mlx->obj_list->next = NULL;
		mlx->obj_list = temp_obj;
	}

	if (mlx->trans_count > 0)
	{
		mlx->trans_list->next = NULL;
		mlx->trans_list = temp_trans;
	}
	
	printf("trans count%d\n", mlx->trans_count);

	printf("px %f	py %f	sect %d\n\n", mlx->player->pos->x, mlx->player->pos->y, mlx->player->sector);
	int j = -1;
	while (++j < v - 1)
		free(verts[j]);
	free(verts);
	// printf("sect %d\n", mlx->num_sec);
	// int j = 0;
	// while (j < s - 1)
	// {
	// 	printf("\nsect %d\n", j);
	// 	printf("v_count %d\n", mlx->sect[j]->verts_count);
	// 	printf("floor %f	ceiling %f\n\n", mlx->sect[j]->floor, mlx->sect[j]->ceiling);
	// 	int k = -1;
	// 	while (++k < mlx->sect[j]->verts_count + 1)
	// 		printf("x %f	y %f\n", mlx->sect[j]->verts[k]->x, mlx->sect[j]->verts[k]->y);
	// 	k = -1;
	// 	while (++k < mlx->sect[j]->neighbors_count)
	// 		printf("%s ", mlx->sect[j]->neighbors[k]);
	// 	printf("\n");
	// 	k = -1;
	// 	while (++k < mlx->sect[j]->txt_count)
	// 		printf("%s ", mlx->sect[j]->texts[k]);
	// 	printf("\n________________________________\n");
	// 	j++;
	// }

	// printf("\n------------------------------------------------\n\n");
	// t_obj *obj = mlx->obj_list;
	// while (obj)
	// {
	// 	printf("sect %d				index %d\n", obj->specs->sect, obj->specs->obj_i);
	// 	printf("x %f			y %f\n", obj->specs->x, obj->specs->y);
	// 	if (obj->prev)
	// 	{
	// 		printf("prev_sect %d			prev_index %d\n", obj->prev->specs->sect, obj->prev->specs->obj_i);
	// 		printf("prev_x %f		prev_y %f\n", obj->prev->specs->x, obj->prev->specs->y);
	// 	}
	// 	else
	// 		printf("prev -\n");
	// 	printf("\n------------------------------------------------\n");
	// 	obj = obj->next;
	// }
}
