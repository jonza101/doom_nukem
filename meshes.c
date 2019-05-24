/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meshes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:45:05 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/24 23:15:27 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_cube_points(t_mlx *mlx)
{
	//SOUTH
	mlx->cube->triangles[0].points[0]->x = 0.0;		mlx->cube->triangles[1].points[0]->x = 0.0;
	mlx->cube->triangles[0].points[0]->y = 0.0;		mlx->cube->triangles[1].points[0]->y = 0.0;
	mlx->cube->triangles[0].points[0]->z = 0.0;		mlx->cube->triangles[1].points[0]->z = 0.0;

	mlx->cube->triangles[0].points[1]->x = 0.0;		mlx->cube->triangles[1].points[1]->x = 1.0;
	mlx->cube->triangles[0].points[1]->y = 1.0;		mlx->cube->triangles[1].points[1]->y = 1.0;
	mlx->cube->triangles[0].points[1]->z = 0.0;		mlx->cube->triangles[1].points[1]->z = 0.0;

	mlx->cube->triangles[0].points[2]->x = 1.0;		mlx->cube->triangles[1].points[2]->x = 1.0;
	mlx->cube->triangles[0].points[2]->y = 1.0;		mlx->cube->triangles[1].points[2]->y = 0.0;
	mlx->cube->triangles[0].points[2]->z = 0.0;		mlx->cube->triangles[1].points[2]->z = 0.0;

	//EAST
	mlx->cube->triangles[2].points[0]->x = 1.0;		mlx->cube->triangles[3].points[0]->x = 1.0;
	mlx->cube->triangles[2].points[0]->y = 0.0;		mlx->cube->triangles[3].points[0]->y = 0.0;
	mlx->cube->triangles[2].points[0]->z = 0.0;		mlx->cube->triangles[3].points[0]->z = 0.0;

	mlx->cube->triangles[2].points[1]->x = 1.0;		mlx->cube->triangles[3].points[1]->x = 1.0;
	mlx->cube->triangles[2].points[1]->y = 1.0;		mlx->cube->triangles[3].points[1]->y = 1.0;
	mlx->cube->triangles[2].points[1]->z = 0.0;		mlx->cube->triangles[3].points[1]->z = 1.0;

	mlx->cube->triangles[2].points[2]->x = 1.0;		mlx->cube->triangles[3].points[2]->x = 1.0;
	mlx->cube->triangles[2].points[2]->y = 1.0;		mlx->cube->triangles[3].points[2]->y = 0.0;
	mlx->cube->triangles[2].points[2]->z = 1.0;		mlx->cube->triangles[3].points[2]->z = 1.0;

	//NORTH
	mlx->cube->triangles[4].points[0]->x = 1.0;		mlx->cube->triangles[5].points[0]->x = 1.0;
	mlx->cube->triangles[4].points[0]->y = 0.0;		mlx->cube->triangles[5].points[0]->y = 0.0;
	mlx->cube->triangles[4].points[0]->z = 1.0;		mlx->cube->triangles[5].points[0]->z = 1.0;

	mlx->cube->triangles[4].points[1]->x = 1.0;		mlx->cube->triangles[5].points[1]->x = 0.0;
	mlx->cube->triangles[4].points[1]->y = 1.0;		mlx->cube->triangles[5].points[1]->y = 1.0;
	mlx->cube->triangles[4].points[1]->z = 1.0;		mlx->cube->triangles[5].points[1]->z = 1.0;

	mlx->cube->triangles[4].points[2]->x = 0.0;		mlx->cube->triangles[5].points[2]->x = 0.0;
	mlx->cube->triangles[4].points[2]->y = 1.0;		mlx->cube->triangles[5].points[2]->y = 0.0;
	mlx->cube->triangles[4].points[2]->z = 1.0;		mlx->cube->triangles[5].points[2]->z = 1.0;

	//WEST
	mlx->cube->triangles[6].points[0]->x = 0.0;		mlx->cube->triangles[7].points[0]->x = 0.0;
	mlx->cube->triangles[6].points[0]->y = 0.0;		mlx->cube->triangles[7].points[0]->y = 0.0;
	mlx->cube->triangles[6].points[0]->z = 1.0;		mlx->cube->triangles[7].points[0]->z = 1.0;

	mlx->cube->triangles[6].points[1]->x = 0.0;		mlx->cube->triangles[7].points[1]->x = 0.0;
	mlx->cube->triangles[6].points[1]->y = 1.0;		mlx->cube->triangles[7].points[1]->y = 1.0;
	mlx->cube->triangles[6].points[1]->z = 1.0;		mlx->cube->triangles[7].points[1]->z = 0.0;

	mlx->cube->triangles[6].points[2]->x = 0.0;		mlx->cube->triangles[7].points[2]->x = 0.0;
	mlx->cube->triangles[6].points[2]->y = 1.0;		mlx->cube->triangles[7].points[2]->y = 0.0;
	mlx->cube->triangles[6].points[2]->z = 0.0;		mlx->cube->triangles[7].points[2]->z = 0.0;

	//TOP
	mlx->cube->triangles[8].points[0]->x = 0.0;		mlx->cube->triangles[9].points[0]->x = 0.0;
	mlx->cube->triangles[8].points[0]->y = 1.0;		mlx->cube->triangles[9].points[0]->y = 1.0;
	mlx->cube->triangles[8].points[0]->z = 0.0;		mlx->cube->triangles[9].points[0]->z = 0.0;

	mlx->cube->triangles[8].points[1]->x = 0.0;		mlx->cube->triangles[9].points[1]->x = 1.0;
	mlx->cube->triangles[8].points[1]->y = 1.0;		mlx->cube->triangles[9].points[1]->y = 1.0;
	mlx->cube->triangles[8].points[1]->z = 1.0;		mlx->cube->triangles[9].points[1]->z = 1.0;

	mlx->cube->triangles[8].points[2]->x = 1.0;		mlx->cube->triangles[9].points[2]->x = 1.0;
	mlx->cube->triangles[8].points[2]->y = 1.0;		mlx->cube->triangles[9].points[2]->y = 1.0;
	mlx->cube->triangles[8].points[2]->z = 1.0;		mlx->cube->triangles[9].points[2]->z = 0.0;

	//BOTTOM
	mlx->cube->triangles[10].points[0]->x = 1.0;		mlx->cube->triangles[11].points[0]->x = 1.0;
	mlx->cube->triangles[10].points[0]->y = 0.0;		mlx->cube->triangles[11].points[0]->y = 0.0;
	mlx->cube->triangles[10].points[0]->z = 1.0;		mlx->cube->triangles[11].points[0]->z = 1.0;

	mlx->cube->triangles[10].points[1]->x = 0.0;		mlx->cube->triangles[11].points[1]->x = 0.0;
	mlx->cube->triangles[10].points[1]->y = 0.0;		mlx->cube->triangles[11].points[1]->y = 0.0;
	mlx->cube->triangles[10].points[1]->z = 1.0;		mlx->cube->triangles[11].points[1]->z = 0.0;

	mlx->cube->triangles[10].points[2]->x = 0.0;		mlx->cube->triangles[11].points[2]->x = 1.0;
	mlx->cube->triangles[10].points[2]->y = 0.0;		mlx->cube->triangles[11].points[2]->y = 0.0;
	mlx->cube->triangles[10].points[2]->z = 0.0;		mlx->cube->triangles[11].points[2]->z = 0.0;
}

void	ft_init_cube(t_mlx *mlx)
{
	mlx->cube = (t_mesh*)malloc(sizeof(t_mesh));
	mlx->cube->tri_count = 12;
	mlx->cube->triangles = (t_triangle*)malloc(sizeof(t_triangle) * mlx->cube->tri_count);

	int i = 0;
	while (i < mlx->cube->tri_count)
	{
		int j = 0;
		while (j < 3)
		{
			mlx->cube->triangles->color = 0xD15AD1;
			mlx->cube->triangles[i].points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
			j++;
		}
		i++;
	}
	ft_cube_points(mlx);
}
