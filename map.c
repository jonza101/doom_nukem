/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 15:25:41 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/20 20:35:28 by zjeyne-l         ###   ########.fr       */
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
	t_sector *sect_to = mlx->sect[sect_to_find];
	s = -1;
	while (++s < sect_to->verts_count)
	{
		if (v1->x == sect_to->verts[s + 1]->x && v1->y == sect_to->verts[s + 1]->y
				&& v2->x == sect_to->verts[s + 0]->x && v2->y == sect_to->verts[s + 0]->y)
			return (s);
	}
	return (-1);
}

void	ft_set_obj_collider(t_mlx *mlx, t_obj *obj)
{
	(!(obj->specs->verts = (t_vec2**)malloc(sizeof(t_vec2*) * 5))) ? ft_mem_error() : 1;
	int f = -1;
	while (++f < 5)
		(!(obj->specs->verts[f] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
	obj->specs->has_collider = 1;

	obj->specs->verts[0]->x = obj->specs->x - mlx->obj_l[obj->specs->obj_i]->col_w;
	obj->specs->verts[0]->y = obj->specs->y + mlx->obj_l[obj->specs->obj_i]->col_w;

	obj->specs->verts[1]->x = obj->specs->x - mlx->obj_l[obj->specs->obj_i]->col_w;
	obj->specs->verts[1]->y = obj->specs->y - mlx->obj_l[obj->specs->obj_i]->col_w;

	obj->specs->verts[2]->x = obj->specs->x + mlx->obj_l[obj->specs->obj_i]->col_w;
	obj->specs->verts[2]->y = obj->specs->y - mlx->obj_l[obj->specs->obj_i]->col_w;

	obj->specs->verts[3]->x = obj->specs->x + mlx->obj_l[obj->specs->obj_i]->col_w;
	obj->specs->verts[3]->y = obj->specs->y + mlx->obj_l[obj->specs->obj_i]->col_w;

	obj->specs->verts[4]->x = obj->specs->x - mlx->obj_l[obj->specs->obj_i]->col_w;
	obj->specs->verts[4]->y = obj->specs->y + mlx->obj_l[obj->specs->obj_i]->col_w;
}

int		ft_obj_index_check(int index)
{
	if (index == 0 || index == 3)
		return (1);
	return (0);
}

void	ft_strsplit_free(char **temp)
{
	int i;

	i = 0;
	while (temp[i])
	{
		free(temp[i]);
		i++;
	}
	free(temp);
}

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
	int g = 1;
	int w = 1;
	int seg = 1;
	int p = 0;
	
	char *line;
	int fd = open(map_file, O_RDONLY);
	if (fd < 0)
		ft_map_error();
	
	char **temp;

	t_vec2 **verts = NULL, **tmp_v = NULL;

	t_sector **tmp_s = NULL;

	t_obj *temp_obj = NULL;

	t_trans *temp_trans = NULL, *trans_prev = NULL;
	mlx->trans_list = NULL;
	mlx->trans_count = 0;

	t_wobj *temp_wobj = NULL, *wobj_last = NULL;
	mlx->wobj_list = NULL;
	mlx->wobj_count = 0;

	mlx->activated_doors = 0;
	while (get_next_line(fd, &line))
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			temp = ft_strsplit(line, ' ');

			int l = -1;
			while (temp[++l]);
			if (l < 3)
				ft_map_error();

			if (v > 1)
			{
				(!(tmp_v = (t_vec2**)malloc(sizeof(t_vec2*) * (v - 1)))) ? ft_mem_error() : 1;
				int j = v - 2;
				while (j >= 0)
				{
					(!(tmp_v[j] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
					ft_memcpy(tmp_v[j], verts[j], sizeof(t_vec2));
					free(verts[j]);
					j--;
				}
				free(verts);
				(!(verts = (t_vec2**)malloc(sizeof(t_vec2*) * v))) ? ft_mem_error() : 1;
				j = 0;
				while (j < v - 1)
				{
					(!(verts[j] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
					ft_memcpy(verts[j], tmp_v[j], sizeof(t_vec2));
					free(tmp_v[j]);
					j++;
				}
				free(tmp_v);
				(!(verts[v - 1] = (t_vec2*)malloc(sizeof(t_vec2))) ? ft_mem_error() : 1);

				if (!ft_fval_check(temp[1]) || !ft_fval_check(temp[2]))
					ft_map_error();

				verts[v - 1]->x = (double)ft_atof(temp[2]);
				verts[v - 1]->y = (double)ft_atof(temp[1]);
				v++;
			}
			else
			{
				(!(verts = (t_vec2**)malloc(sizeof(t_vec2*) * 1))) ? ft_mem_error() : 1;
				(!(verts[0] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

				if (!ft_fval_check(temp[1]) || !ft_fval_check(temp[2]))
					ft_map_error();

				verts[0]->x = (double)ft_atof(temp[2]);
				verts[0]->y = (double)ft_atof(temp[1]);
				int j = 0;
				v++;
			}
			ft_strsplit_free(temp);
		}
		if (line[0] == 's' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');

			int l = -1;
			while (temp[++l]);
			if (l < 4)
				ft_map_error();

			if (s > 1)
			{
				(!(tmp_s = (t_sector**)malloc(sizeof(t_sector*) * (s - 1)))) ? ft_mem_error() : 1;
				int j = s - 2;
				while (j >= 0)
				{
					(!(tmp_s[j] = (t_sector*)malloc(sizeof(t_sector))) ? ft_mem_error() : 1);
					ft_memcpy(tmp_s[j], mlx->sect[j], sizeof(t_sector));
					free(mlx->sect[j]);
					j--;
				}
				free(mlx->sect);
				(!(mlx->sect = (t_sector**)malloc(sizeof(t_sector*) * s))) ? ft_mem_error() : 1;
				j = 0;
				while (j < s - 1)
				{
					(!(mlx->sect[j] = (t_sector*)malloc(sizeof(t_sector)))) ? ft_mem_error() : 1;
					ft_memcpy(mlx->sect[j], tmp_s[j], sizeof(t_sector));
					free(tmp_s[j]);
					j++;
				}
				free(tmp_s);
				(!(mlx->sect[s - 1] = (t_sector*)malloc(sizeof(t_sector)))) ? ft_mem_error() : 1;

				char **t;
				t = ft_strsplit(temp[1], ' ');

				if (!ft_fval_check(t[0]) || !ft_fval_check(t[1]))
					ft_map_error();

				mlx->sect[s - 1]->floor = (double)ft_atof(t[0]);
				mlx->sect[s - 1]->ceiling = (double)ft_atof(t[1]);

				if (mlx->sect[s - 1]->floor > mlx->sect[s - 1]->ceiling)
					ft_map_error();

				ft_strsplit_free(t);

				t = ft_strsplit(temp[2], ' ');
				int v_count = 0;
				while (t[v_count])
					v_count++;

				if (v_count < 3)
					ft_map_error();

				mlx->sect[s - 1]->verts_count = v_count;
				(!(mlx->sect[s - 1]->verts = (t_vec2**)malloc(sizeof(t_vec2*) * (v_count + 1)))) ? ft_mem_error() : 1;

				mlx->sect[s - 1]->txt_count = v_count;
				(!(mlx->sect[s - 1]->texts = (char**)malloc(sizeof(char*) * v_count))) ? ft_mem_error() : 1;

				j = -1;
				while (++j < v_count)
				{
					(!(mlx->sect[s - 1]->verts[j + 1] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

					if (!ft_ival_check(t[j]))
						ft_map_error();
					int indx = ft_atoi(t[j]);
					if (indx < 0 || indx > v - 2)
						ft_map_error();

					mlx->sect[s - 1]->verts[j + 1]->x = (double)verts[indx]->x;
					mlx->sect[s - 1]->verts[j + 1]->y = (double)verts[indx]->y;

					mlx->sect[s - 1]->texts[j] = NULL;
				}
				(!(mlx->sect[s - 1]->verts[0] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

				if (!ft_ival_check(t[j - 1]))
					ft_map_error();
				int indx = ft_atoi(t[j - 1]);
				if (indx < 0 || indx > v - 2)
					ft_map_error();

				mlx->sect[s - 1]->verts[0]->x = (double)verts[ft_atoi(t[j - 1])]->x;
				mlx->sect[s - 1]->verts[0]->y = (double)verts[ft_atoi(t[j - 1])]->y;

				ft_strsplit_free(t);

				t = ft_strsplit(temp[3], ' ');
				int n_count = 0;
				while (t[n_count])
					n_count++;

				if (n_count != v_count)
					ft_map_error();

				mlx->sect[s - 1]->neighbors_count = n_count;
				(!(mlx->sect[s - 1]->neighbors = (int*)malloc(sizeof(int) * n_count))) ? ft_mem_error() : 1;
				j = 0;
				while (j < n_count)
				{
					int neigh = ft_atoi(t[j]);
					if (neigh < -1 || neigh > v - 2)
						ft_map_error();

					mlx->sect[s - 1]->neighbors[j] = ft_atoi(t[j]);
					j++;
				}
				mlx->sect[s - 1]->ceil_txt = -1;
				mlx->sect[s - 1]->floor_txt = -1;

				mlx->sect[s - 1]->obj_list = NULL;
				mlx->sect[s - 1]->obj_count = 0;

				if (temp[4] && ft_fval_check(temp[4]))
				{
					mlx->sect[s - 1]->light = 0;
					mlx->sect[s - 1]->lum = ft_clamp(ft_atof(temp[4]), 0.25f, 0.95f);
					mlx->sect[s - 1]->has_switcher = 1;
				}
				else
				{
					mlx->sect[s - 1]->light = 1;
					mlx->sect[s - 1]->lum = 0.5f;
					mlx->sect[s - 1]->has_switcher = 0;
				}

				mlx->sect[s - 1]->sky = 0;
				mlx->sect[s - 1]->is_door = 0;
				mlx->sect[s - 1]->is_finish = 0;

				ft_strsplit_free(t);
			}
			else
			{
				(!(mlx->sect = (t_sector**)malloc(sizeof(t_sector*) * 1))) ? ft_mem_error() : 1;
				(!(mlx->sect[0] = (t_sector*)malloc(sizeof(t_sector)))) ? ft_mem_error() : 1;

				char **t;
				t = ft_strsplit(temp[1], ' ');

				if (!ft_fval_check(t[0]) || !ft_fval_check(t[1]))
					ft_map_error();

				mlx->sect[0]->floor = (double)ft_atof(t[0]);
				mlx->sect[0]->ceiling = (double)ft_atof(t[1]);

				if (mlx->sect[0]->floor > mlx->sect[0]->ceiling)
					ft_map_error();

				ft_strsplit_free(t);

				t = ft_strsplit(temp[2], ' ');
				int v_count = 0;
				while (t[v_count])
					v_count++;

				if (v_count < 3)
					ft_map_error();

				mlx->sect[0]->verts_count = v_count;
				(!(mlx->sect[0]->verts = (t_vec2**)malloc(sizeof(t_vec2*) * (v_count + 1)))) ? ft_mem_error() : 1;

				mlx->sect[0]->txt_count = v_count;
				(!(mlx->sect[0]->texts = (char**)malloc(sizeof(char*) * v_count))) ? ft_mem_error() : 1;

				int j = -1;
				while (++j < v_count)
				{
					(!(mlx->sect[0]->verts[j + 1] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

					if (!ft_ival_check(t[j]))
						ft_map_error();
					int indx = ft_atoi(t[j]);
					if (indx < 0 || indx > v - 2)
						ft_map_error();

					mlx->sect[0]->verts[j + 1]->x = (double)verts[indx]->x;
					mlx->sect[0]->verts[j + 1]->y = (double)verts[indx]->y;

					mlx->sect[0]->texts[j] = NULL;
				}
				(!(mlx->sect[0]->verts[0] = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

				if (!ft_ival_check(t[j - 1]))
						ft_map_error();
				int indx = ft_atoi(t[j - 1]);
				if (indx < 0 || indx > v - 2)
					ft_map_error();

				mlx->sect[0]->verts[0]->x = (double)verts[indx]->x;
				mlx->sect[0]->verts[0]->y = (double)verts[indx]->y;

				ft_strsplit_free(t);

				t = ft_strsplit(temp[3], ' ');
				int n_count = 0;
				while (t[n_count])
					n_count++;

				if (n_count != v_count)
					ft_map_error();

				mlx->sect[0]->neighbors_count = n_count;
				(!(mlx->sect[0]->neighbors = (int*)malloc(sizeof(int) * n_count))) ? ft_mem_error() : 1;
				j = 0;
				while (j < n_count)
				{
					int neigh = ft_atoi(t[j]);
					if (neigh < -1 || neigh > v - 2)
						ft_map_error();

					mlx->sect[0]->neighbors[j] = neigh;
					j++;
				}
				mlx->sect[0]->ceil_txt = -1;
				mlx->sect[0]->floor_txt = -1;

				mlx->sect[0]->obj_list = NULL;
				mlx->sect[0]->obj_count = 0;

				if (temp[4] && ft_fval_check(temp[4]))
				{
					mlx->sect[0]->light = 0;
					mlx->sect[0]->lum = ft_clamp(ft_atof(temp[4]), 0.25f, 0.95f);
					mlx->sect[0]->has_switcher = 1;
				}
				else
				{
					mlx->sect[0]->light = 1;
					mlx->sect[0]->lum = 0.5f;
					mlx->sect[0]->has_switcher = 0;
				}

				mlx->sect[0]->sky = 0;
				mlx->sect[0]->is_door = 0;
				mlx->sect[0]->is_finish = 0;

				ft_strsplit_free(t);
			}
			ft_strsplit_free(temp);
			s++;
		}
		if (line[0] == 't' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');

			int l = -1;
			while (temp[++l]);
			if (l < 4 || !ft_ival_check(temp[1]))
				ft_map_error();
			int sect = ft_atoi(temp[1]);
			if (sect < 0 || sect > s - 2)
				ft_map_error();

			char **tmp_t = ft_strsplit(temp[2], ' ');

			l = -1;
			while (tmp_t[++l]);
			if (l < 2)
				ft_map_error();

			int floor_txt = ft_atoi(tmp_t[0]);
			int ceil_txt = ft_atoi(tmp_t[1]);
			if (floor_txt < 0 || floor_txt > TXT - 1)
				mlx->sect[sect]->floor_txt = -1;
			else
				mlx->sect[sect]->floor_txt = floor_txt;
			if (ceil_txt < 0 || ceil_txt > TXT - 1)
				mlx->sect[sect]->ceil_txt = -1;
			else
				mlx->sect[sect]->ceil_txt = ceil_txt;

			if (ft_strcmp(tmp_t[1], "sky") == 0)
			{
				mlx->sect[sect]->sky = 1;
				mlx->sect[sect]->ceil_txt = -1;
			}
			if (!ft_ival_check(tmp_t[0]) || (!ft_ival_check(tmp_t[1]) && mlx->sect[sect]->sky != 1))
				ft_map_error();

			ft_strsplit_free(tmp_t);

			tmp_t = ft_strsplit(temp[3], ' ');

			l = -1;
			while (tmp_t[++l]);
			if (l != mlx->sect[sect]->verts_count)
				ft_map_error();

			int j = -1;
			while (++j < mlx->sect[sect]->txt_count)
				mlx->sect[sect]->texts[j] = ft_strdup(tmp_t[j]);

			ft_strsplit_free(tmp_t);
			ft_strsplit_free(temp);
		}
		if (line[0] == 'o' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			int l = -1;
			while (temp[++l]);
			if (l < 4)
				ft_map_error();

			char **tmp_t = ft_strsplit(temp[2], ' ');
			l = -1;
			while (tmp_t[++l]);
			if (l != 2 || !ft_fval_check(tmp_t[0]) || !ft_fval_check(tmp_t[1]))
				ft_map_error();

			int sect_n = ft_atoi(temp[1]);
			if (sect_n < 0 || sect_n > s - 2)
				ft_map_error();

			if (!ft_ival_check(temp[3]))
				ft_map_error();
			int obj_i = ft_atoi(temp[3]);
			if (obj_i < 0 || obj_i > OBJ - 1)
				ft_map_error();

			t_sector *sect = mlx->sect[sect_n];

			if (sect->obj_count > 0)
			{
				(!(sect->obj_list->next = (t_obj*)malloc(sizeof(t_obj))) ? ft_mem_error() : 1);
				(!(sect->obj_list->next->specs = (t_obj_specs*)malloc(sizeof(t_obj_specs)))) ? ft_mem_error() : 1;
				sect->obj_list->next->specs->sect = sect_n;
				sect->obj_list->next->specs->x = ft_atof(tmp_t[0]);
				sect->obj_list->next->specs->y = ft_atof(tmp_t[1]);
				sect->obj_list->next->specs->z = mlx->sect[sect_n]->floor;
				sect->obj_list->next->specs->obj_i = obj_i;
				sect->obj_list->next->specs->has_collider = 0;
				if (ft_obj_index_check(sect->obj_list->next->specs->obj_i))
					ft_set_obj_collider(mlx, sect->obj_list->next);

				if (temp[4])
					sect->obj_list->next->specs->pov = ft_atof(temp[4]);
				else
					sect->obj_list->next->specs->pov = 0.0f;

				sect->obj_list->next->specs->frame = mlx->obj_l[sect->obj_list->next->specs->obj_i]->anim[0];
				sect->obj_list->next->specs->del = 0;
				sect->obj_list->next->specs->anim_i = 0;
				sect->obj_list = sect->obj_list->next;
				sect->obj_list->next = NULL;
				sect->obj_count++;
			}
			else
			{
				(!(sect->obj_list = (t_obj*)malloc(sizeof(t_obj)))) ? ft_mem_error() : 1;
				(!(sect->obj_list->specs = (t_obj_specs*)malloc(sizeof(t_obj_specs)))) ? ft_mem_error() : 1;
				sect->obj_list->specs->sect = sect_n;
				sect->obj_list->specs->x = ft_atof(tmp_t[0]);
				sect->obj_list->specs->y = ft_atof(tmp_t[1]);
				sect->obj_list->specs->z = mlx->sect[sect_n]->floor;
				sect->obj_list->specs->obj_i = obj_i;
				sect->obj_list->specs->has_collider = 0;
				if (ft_obj_index_check(sect->obj_list->specs->obj_i))
					ft_set_obj_collider(mlx, sect->obj_list);

				if (temp[4])
					sect->obj_list->specs->pov = ft_atof(temp[4]);
				else
					sect->obj_list->specs->pov = 0.0f;

				sect->obj_list->specs->frame = mlx->obj_l[sect->obj_list->specs->obj_i]->anim[0];
				sect->obj_list->specs->del = 0;
				sect->obj_list->specs->anim_i = 0;
				sect->obj_list->specs->expl_f = 0;
				sect->obj_head = sect->obj_list;
				sect->obj_list->next = NULL;
				sect->obj_count++;
			}

			ft_strsplit_free(temp);
			ft_strsplit_free(tmp_t);
		}
		if (line[0] == 'g' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			int l = -1;
			while (temp[++l]);
			if (l < 4 || !ft_ival_check(temp[1]) || !ft_ival_check(temp[2]) || !ft_ival_check(temp[3]))
				ft_map_error();

			int sect = ft_atoi(temp[1]);
			if (sect < 0 || sect > s - 2)
				ft_map_error();

			int side = ft_atoi(temp[2]);
			if (side < 0 || side > mlx->sect[sect]->verts_count - 1)
				ft_map_error();

			int trans_i = ft_atoi(temp[3]);
			if (trans_i < 0 || trans_i > TRANSPARENT - 1)
				ft_map_error();

			if (g > 1)
			{
				(!(mlx->trans_list->next = (t_trans*)malloc(sizeof(t_trans)))) ? ft_mem_error() : 1;
				mlx->trans_list->next->sect = sect;
				mlx->trans_list->next->side = side;
				mlx->trans_list->next->trans_i = trans_i;
				mlx->trans_list = mlx->trans_list->next;

				mlx->trans_list->prev = trans_prev;
				trans_prev = mlx->trans_list;

				(!(mlx->trans_list->next = (t_trans*)malloc(sizeof(t_trans)))) ? ft_mem_error() : 1;
				int neigh_sect = (mlx->sect[mlx->trans_list->sect]->neighbors[mlx->trans_list->side]);

				if (neigh_sect < 0)
					ft_map_error();

				int mirror_side = ft_find_sect_mirror_side(mlx, mlx->trans_list->sect, mlx->trans_list->side, neigh_sect);

				mlx->trans_list->next->sect = neigh_sect;
				mlx->trans_list->next->side = mirror_side;
				mlx->trans_list->next->trans_i = mlx->trans_list->trans_i;

				mlx->trans_list = mlx->trans_list->next;
				mlx->trans_list->prev = trans_prev;
				trans_prev = mlx->trans_list;
			}
			else
			{
				(!(mlx->trans_list = (t_trans*)malloc(sizeof(t_trans)))) ? ft_mem_error() : 1;
				mlx->trans_list->sect = sect;
				mlx->trans_list->side = side;
				mlx->trans_list->trans_i = trans_i;

				mlx->trans_list->prev = NULL;
				temp_trans = mlx->trans_list;
				trans_prev = mlx->trans_list;

				(!(mlx->trans_list->next = (t_trans*)malloc(sizeof(t_trans)))) ? ft_mem_error() : 1;
				int neigh_sect = (mlx->sect[mlx->trans_list->sect]->neighbors[mlx->trans_list->side]);

				if (neigh_sect < 0)
					ft_map_error();

				int mirror_side = ft_find_sect_mirror_side(mlx, mlx->trans_list->sect, mlx->trans_list->side, neigh_sect);

				mlx->trans_list->next->sect = neigh_sect;
				mlx->trans_list->next->side = mirror_side;
				mlx->trans_list->next->trans_i = mlx->trans_list->trans_i;

				mlx->trans_list = mlx->trans_list->next;
				mlx->trans_list->prev = trans_prev;
				trans_prev = mlx->trans_list;
			}
			ft_strsplit_free(temp);

			g++;
			mlx->trans_count++;
		}
		if (line[0] == 'w' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			int l = -1;
			while (temp[++l]);
			if (l < 5 || !ft_ival_check(temp[1]) || !ft_ival_check(temp[2]) || !ft_ival_check(temp[4]))
				ft_map_error();

			int w_sect = ft_atoi(temp[1]);
			if (w_sect < 0 || w_sect > s - 2)
				ft_map_error();

			int w_side = ft_atoi(temp[2]);
			if (w_side < 0 || w_side > mlx->sect[w_sect]->verts_count - 1)
				ft_map_error();

			char **w_pos = ft_strsplit(temp[3], ' ');
			l = -1;
			while (w_pos[++l]);
			if (l != 3 || !ft_fval_check(w_pos[0]) || !ft_fval_check(w_pos[1]) || !ft_fval_check(w_pos[2]))
				ft_map_error();

			int w_i = ft_atoi(temp[4]);
			if (w_i < 0 || w_i > WOBJ - 1)
				ft_map_error();

			short swtch = 1;
			if (w_i == 8 && mlx->sect[w_sect]->has_switcher)
				swtch = 0;

			if (w_i == 8)
			{
				if (temp[5] && ft_fval_check(temp[5]))
				{
					double lum = ft_atof(temp[5]);
					if (lum >= 0.25f && lum <= 0.95f)
						mlx->sect[w_sect]->lum = lum;
				}
				mlx->sect[w_sect]->has_switcher = 1;
			}

			if (mlx->wobj_count > 0 && swtch)
			{
				(!(mlx->wobj_list->next = (t_wobj*)malloc(sizeof(t_wobj)))) ? ft_mem_error() : 1;
				mlx->wobj_list->next->sect = w_sect;
				mlx->wobj_list->next->side = w_side;
				mlx->wobj_list->next->wobj_i = w_i;
				mlx->wobj_list->next->rendered = 0;
				mlx->wobj_list->next->del = 0;
				mlx->wobj_list->next->anim_i = 0;
				mlx->wobj_list->next->frame = mlx->wobj_l[w_i]->anim[0];
				(!(mlx->wobj_list->next->pos = (t_vec3*)malloc(sizeof(t_vec3)))) ? ft_mem_error() : 1;
				mlx->wobj_list->next->pos->x = ft_atof(w_pos[0]);
				mlx->wobj_list->next->pos->y = ft_atof(w_pos[1]);
				mlx->wobj_list->next->pos->z = ft_atof(w_pos[2]);

				(!(mlx->wobj_list->next->p1 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
				(!(mlx->wobj_list->next->p2 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

				mlx->wobj_list = mlx->wobj_list->next;
				mlx->wobj_list->next = NULL;

				mlx->last_wobj = mlx->wobj_list;

				mlx->wobj_count++;
			}
			else if (mlx->wobj_count == 0 && swtch)
			{
				(!(mlx->wobj_list = (t_wobj*)malloc(sizeof(t_wobj)))) ? ft_mem_error() : 1;
				mlx->wobj_list->sect = w_sect;
				mlx->wobj_list->side = w_side;
				mlx->wobj_list->wobj_i = w_i;
				mlx->wobj_list->rendered = 0;
				mlx->wobj_list->del = 0;
				mlx->wobj_list->anim_i = 0;
				mlx->wobj_list->frame = mlx->wobj_l[w_i]->anim[0];
				(!(mlx->wobj_list->pos = (t_vec3*)malloc(sizeof(t_vec3)))) ? ft_mem_error() : 1;
				mlx->wobj_list->pos->x = ft_atof(w_pos[0]);
				mlx->wobj_list->pos->y = ft_atof(w_pos[1]);
				mlx->wobj_list->pos->z = ft_atof(w_pos[2]);

				(!(mlx->wobj_list->p1 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;
				(!(mlx->wobj_list->p2 = (t_vec2*)malloc(sizeof(t_vec2)))) ? ft_mem_error() : 1;

				mlx->wobj_list->next = NULL;
				temp_wobj = mlx->wobj_list;
				mlx->last_wobj = mlx->wobj_list;

				mlx->wobj_count++;
			}

			ft_strsplit_free(w_pos);
			ft_strsplit_free(temp);
		}
		if (line[0] == 'd' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			int l = -1;
			while (temp[++l]);
			if (l < 2 || !ft_ival_check(temp[1]))
				ft_map_error();

			int sect = ft_atoi(temp[1]);
			if (sect < 0 || sect > s - 2)
				ft_map_error();

			mlx->sect[sect]->is_door = 1;
			mlx->sect[sect]->close = 0;
			mlx->sect[sect]->open = 0;
			mlx->sect[sect]->up = 0;
			mlx->sect[sect]->start_ceiling = mlx->sect[sect]->ceiling;
			mlx->sect[sect]->ceiling = mlx->sect[sect]->floor;

			ft_strsplit_free(temp);
		}
		if (line[0] == 'p' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			int l = -1;
			while (temp[++l]);
			if (l < 4 || !ft_ival_check(temp[2]) || !ft_fval_check(temp[3]))
				ft_map_error();

			int sect = ft_atoi(temp[2]);
			if (sect < 0 || sect > s - 2)
				ft_map_error();

			(!(mlx->player->pos = (t_vec3*)malloc(sizeof(t_vec3)))) ? ft_mem_error() : 1;
			(!(mlx->player->velocity = (t_vec3*)malloc(sizeof(t_vec3)))) ? ft_mem_error() : 1;

			mlx->player->eye_h = EYE_H;
			mlx->player->angle = (double)ft_atof(temp[3]);
			mlx->player->sector = sect;

			char **t;
			t = ft_strsplit(temp[1], ' ');
			l = -1;
			while (t[++l]);
			if (l != 2 || !ft_fval_check(t[0]) || !ft_fval_check(t[1]))
				ft_map_error();

			mlx->player->pos->x = (double)ft_atof(t[0]);
			mlx->player->pos->y = (double)ft_atof(t[1]);
			mlx->player->pos->z = (double)mlx->sect[mlx->player->sector]->floor + mlx->player->eye_h;

			mlx->player->jetpack = 0;

			p++;

			ft_strsplit_free(t);
			ft_strsplit_free(temp);
		}
		if (line[0] == 'f' && line[1] == '|')
		{
			temp = ft_strsplit(line, '|');
			int l = -1;
			while (temp[++l]);
			if (l < 2 || !ft_ival_check(temp[1]))
				ft_map_error();
			int sect = ft_atoi(temp[1]);
			if (sect < 0 || sect > s - 2)
				ft_map_error();
			mlx->sect[sect]->is_finish = 1;
			ft_strsplit_free(temp);
		}
		ft_strdel(&line);
	}
	close(fd);
	mlx->num_sec = s - 1;

	if (mlx->trans_count > 0)
	{
		mlx->trans_list->next = NULL;
		mlx->trans_list = temp_trans;
	}

	if (mlx->wobj_count > 0)
	{
		mlx->wobj_list->next = NULL;
		mlx->wobj_list = temp_wobj;
		ft_wobj_pos_correct(mlx);
	}

	if (p != 1)
		ft_player_count_error(p);

	int j = -1;
	while (++j < v - 1)
		free(verts[j]);
	free(verts);

	(!(mlx->sect_wobj = (t_sect_wobj**)malloc(sizeof(t_sect_wobj*) * mlx->num_sec))) ? ft_mem_error() : 1;
	int i = -1;
	while (++i < mlx->num_sec)
	{
		(!(mlx->sect_wobj[i] = (t_sect_wobj*)malloc(sizeof(t_sect_wobj)))) ? ft_mem_error() : 1;
		(!(mlx->sect_wobj[i]->side = (int*)malloc(sizeof(int) * mlx->sect[i]->verts_count))) ? ft_mem_error() : 1;
		int t = -1;
		while (++t < mlx->sect[i]->verts_count)
		{
			mlx->sect_wobj[i]->side[t] = 0;
		}

		if (mlx->sect[i]->obj_count > 0)
			mlx->sect[i]->obj_list = mlx->sect[i]->obj_head;
			mlx->sect[i]->obj_head = NULL;
	}

	t_wobj *wobj = mlx->wobj_list;
	while (wobj)
	{
		mlx->sect_wobj[wobj->sect]->side[wobj->side]++;
		wobj = wobj->next;
	}

	ft_validate_map(mlx);
}
