/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:15:24 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/25 23:33:05 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

double	ft_datoi(char *str)
{
	int len;
	double res;

	res = 0;
	len = ft_strlen(str);
	while (str[len - 1])
	{
		if (str[len - 1] == '.')
			break ;
		res = res / 10 + (str[len - 1] - '0');
		len--;
	}
	res /= 10;
	if (str[0] == '-')
	{
		res -= ft_atoi(str);
		res *= -1;
	}
	else
		res += ft_atoi(str);
	return (res);
}

int		ft_load_obj_file(t_mlx *mlx, char *file_name)
{
	int i;
	int f;
	int fd;
	char *line;
	char **vt;
	t_vector_3d **verts;
	t_vector_3d **temp;
	t_mesh *tmp;

	int color = 0xD15AD1;
	
	i = 1;
	f = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			vt = ft_strsplit(line, ' ');
			if (i > 1)
			{
				temp = (t_vector_3d**)malloc(sizeof(t_vector_3d*) * (i - 1));
				int j = i - 2;;
				while (j >= 0)
				{
					temp[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
					ft_memcpy((void*)temp[j], (const void*)verts[j], sizeof(t_vector_3d));
					free(verts[j]);
					j--;
				}
				verts = (t_vector_3d**)malloc(sizeof(t_vector_3d*) * i);
				j = 0;
				while (j < i - 1)
				{
					verts[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
					ft_memcpy((void*)verts[j], (const void*)temp[j], sizeof(t_vector_3d));
					j++;
				}
				
				verts[i - 1] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
				verts[i - 1]->x = (double)ft_datoi(vt[1]);
				verts[i - 1]->y =(double) ft_datoi(vt[2]);
				verts[i - 1]->z = (double)ft_datoi(vt[3]);
				// printf("%s   %s   %s\n", vt[1], vt[2], vt[3]);
				// printf("%f %f %f\n\n", verts[i - 1]->x, verts[i - 1]->y, verts[i - 1]->z);
			}
			else
			{
				verts = (t_vector_3d**)malloc(sizeof(t_vector_3d*) * 1);
				verts[0] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
				verts[0]->x = (double)ft_datoi(vt[1]);
				verts[0]->y = (double)ft_datoi(vt[2]);
				verts[0]->z = (double)ft_datoi(vt[3]);
				// printf("%s   %s   %s\n", vt[1], vt[2], vt[3]);
				// printf("%f %f %f\n\n", verts[0]->x, verts[0]->y, verts[0]->z);
			}
			i++;
		}
		if (line[0] == 'f' && line[1] == ' ')
		{
			vt = ft_strsplit(line, ' ');
			if (f > 1)
			{
				tmp = (t_mesh*)malloc(sizeof(t_mesh));
				tmp->triangles = (t_triangle*)malloc(sizeof(t_triangle) * (f - 1));
				int j =  f - 2;
				while (j >= 0)
				{
					int k = 0;
					while (k < 3)
					{
						tmp->triangles[j].points[k] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
						tmp->triangles[j].points[k]->x = mlx->cube->triangles[j].points[k]->x;
						tmp->triangles[j].points[k]->y = mlx->cube->triangles[j].points[k]->y;
						tmp->triangles[j].points[k]->z = mlx->cube->triangles[j].points[k]->z;
						free(mlx->cube->triangles[j].points[k]);
						k++;
					}
					j--;
				}
				free(mlx->cube->triangles);
				mlx->cube->triangles = (t_triangle*)malloc(sizeof(t_triangle) * f);
				j = 0;
				while (j < f - 1)
				{
					int k = 0;
					while (k < 3)
					{
						mlx->cube->triangles[j].points[k] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
						mlx->cube->triangles[j].color = color;
						mlx->cube->triangles[j].points[k]->x = tmp->triangles[j].points[k]->x;
						mlx->cube->triangles[j].points[k]->y = tmp->triangles[j].points[k]->y;
						mlx->cube->triangles[j].points[k]->z = tmp->triangles[j].points[k]->z;
						free(tmp->triangles[j].points[k]);
						k++;
					}
					j++;
				}
				free(tmp->triangles);
				free(tmp);
				int k = 0;
				while (k < 3)
				{
					mlx->cube->triangles[f - 1].points[k] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
					mlx->cube->triangles[f - 1].color = color;
					mlx->cube->triangles[f - 1].points[k]->x = verts[ft_atoi(vt[k + 1]) - 1]->x;
					mlx->cube->triangles[f - 1].points[k]->y = verts[ft_atoi(vt[k + 1]) - 1]->y;
					mlx->cube->triangles[f - 1].points[k]->z = verts[ft_atoi(vt[k + 1]) - 1]->z;
					k++;
				}
			}
			else
			{
				mlx->cube = (t_mesh*)malloc(sizeof(t_mesh));
				mlx->cube->triangles = (t_triangle*)malloc(sizeof(t_triangle) * 1);
				int j = 0;
				while (j < 3)
				{
					mlx->cube->triangles[0].points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
					mlx->cube->triangles[0].color= 0xD15AD1;
					mlx->cube->triangles[0].points[j]->x = verts[ft_atoi(vt[j + 1]) - 1]->x;
					mlx->cube->triangles[0].points[j]->y = verts[ft_atoi(vt[j + 1]) - 1]->y;
					mlx->cube->triangles[0].points[j]->z = verts[ft_atoi(vt[j + 1]) - 1]->z;
					j++;
				}
				// printf("x %f y %f z %f\n", mlx->cube->triangles[0].points[0]->x, mlx->cube->triangles[0].points[0]->y, mlx->cube->triangles[0].points[0]->z);
				// printf("x %f y %f z %f\n", mlx->cube->triangles[0].points[1]->x, mlx->cube->triangles[0].points[1]->y, mlx->cube->triangles[0].points[1]->z);
				// printf("x %f y %f z %f\n", mlx->cube->triangles[0].points[2]->x, mlx->cube->triangles[0].points[2]->y, mlx->cube->triangles[0].points[2]->z);
			}
			f++;
		}
	}
	printf("count %d\n", i - 1);
	printf("t count %d\n", f - 1);
	mlx->cube->tri_count = f - 1;
	close(fd);
	
	return (1);
}
