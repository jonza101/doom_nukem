/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 19:15:24 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/24 23:11:38 by zjeyne-l         ###   ########.fr       */
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
	int fd;
	char *line;
	char **v;
	t_vector_3d **verts;
	t_vector_3d **temp;
	
	i = 1;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	while (get_next_line(fd, &line) == 1)
	{
		if (line[0] == 'v' && line[1] == ' ')
		{
			v = ft_strsplit(line, ' ');
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
				verts[i - 1]->x = (double)ft_datoi(v[1]);
				verts[i - 1]->y =(double) ft_datoi(v[2]);
				verts[i - 1]->z = (double)ft_datoi(v[3]);
				// printf("%s   %s   %s\n", v[1], v[2], v[3]);
				// printf("%f %f %f\n\n", verts[i - 1]->x, verts[i - 1]->y, verts[i - 1]->z);
			}
			else
			{
				verts = (t_vector_3d**)malloc(sizeof(t_vector_3d*) * 1);
				verts[0] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
				verts[0]->x = (double)ft_datoi(v[1]);
				verts[0]->y = (double)ft_datoi(v[2]);
				verts[0]->z = (double)ft_datoi(v[3]);
				// printf("%s   %s   %s\n", v[1], v[2], v[3]);
				// printf("%f %f %f\n\n", verts[0]->x, verts[0]->y, verts[0]->z);
			}
			i++;
		}
	}
	mlx->cube = (t_mesh*)malloc(sizeof(t_mesh));
	mlx->cube->triangles = (t_triangle*)malloc(sizeof(t_triangle) * (i - 1));
	mlx->cube->tri_count = i - 1;
	int j = 0;
	while (j < mlx->cube->tri_count)
	{
		// mlx->cube->triangles[j]
		j++;
	}
	printf("count %d\n", i - 1);
	close(fd);
	return (1);
}
