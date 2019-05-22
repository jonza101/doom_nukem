/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meshes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 17:45:05 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/22 18:04:09 by zjeyne-l         ###   ########.fr       */
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

void	ft_pyra_points(t_mlx *mlx)
{
	//SOUTH
	mlx->pyra->triangles[0].points[0]->x = 0.0;
	mlx->pyra->triangles[0].points[0]->y = 0.0;
	mlx->pyra->triangles[0].points[0]->z = 0.0;
	
	mlx->pyra->triangles[0].points[1]->x = 0.5;
	mlx->pyra->triangles[0].points[1]->y = 1.0;
	mlx->pyra->triangles[0].points[1]->z = 0.5;

	mlx->pyra->triangles[0].points[2]->x = 1.0;
	mlx->pyra->triangles[0].points[2]->y = 0.0;
	mlx->pyra->triangles[0].points[2]->z = 0.0;

	//EAST
	mlx->pyra->triangles[1].points[0]->x = 1.0;
	mlx->pyra->triangles[1].points[0]->y = 0.0;
	mlx->pyra->triangles[1].points[0]->z = 0.0;
	
	mlx->pyra->triangles[1].points[1]->x = 0.5;
	mlx->pyra->triangles[1].points[1]->y = 1.0;
	mlx->pyra->triangles[1].points[1]->z = 0.5;

	mlx->pyra->triangles[1].points[2]->x = 1.0;
	mlx->pyra->triangles[1].points[2]->y = 0.0;
	mlx->pyra->triangles[1].points[2]->z = 1.0;

	//NORTH
	mlx->pyra->triangles[2].points[0]->x = 1.0;
	mlx->pyra->triangles[2].points[0]->y = 0.0;
	mlx->pyra->triangles[2].points[0]->z = 1.0;
	
	mlx->pyra->triangles[2].points[1]->x = 0.5;
	mlx->pyra->triangles[2].points[1]->y = 1.0;
	mlx->pyra->triangles[2].points[1]->z = 0.5;

	mlx->pyra->triangles[2].points[2]->x = 0.0;
	mlx->pyra->triangles[2].points[2]->y = 0.0;
	mlx->pyra->triangles[2].points[2]->z = 1.0;

	//WEST
	mlx->pyra->triangles[3].points[0]->x = 0.0;
	mlx->pyra->triangles[3].points[0]->y = 0.0;
	mlx->pyra->triangles[3].points[0]->z = 1.0;
	
	mlx->pyra->triangles[3].points[1]->x = 0.5;
	mlx->pyra->triangles[3].points[1]->y = 1.0;
	mlx->pyra->triangles[3].points[1]->z = 0.5;

	mlx->pyra->triangles[3].points[2]->x = 0.0;
	mlx->pyra->triangles[3].points[2]->y = 0.0;
	mlx->pyra->triangles[3].points[2]->z = 0.0;

	//BOTTOM
	mlx->pyra->triangles[4].points[0]->x = 1.0;		mlx->pyra->triangles[5].points[0]->x = 1.0;
	mlx->pyra->triangles[4].points[0]->y = 0.0;		mlx->pyra->triangles[5].points[0]->x = 0.0;
	mlx->pyra->triangles[4].points[0]->z = 1.0;		mlx->pyra->triangles[5].points[0]->x = 1.0;
	
	mlx->pyra->triangles[4].points[1]->x = 0.0;		mlx->pyra->triangles[5].points[0]->x = 1.0;
	mlx->pyra->triangles[4].points[1]->y = 0.0;		mlx->pyra->triangles[5].points[0]->x = 0.0;
	mlx->pyra->triangles[4].points[1]->z = 1.0;		mlx->pyra->triangles[5].points[0]->x = 0.0;

	mlx->pyra->triangles[4].points[2]->x = 1.0;		mlx->pyra->triangles[5].points[0]->x = 0.0;
	mlx->pyra->triangles[4].points[2]->y = 0.0;		mlx->pyra->triangles[5].points[0]->x = 0.0;
	mlx->pyra->triangles[4].points[2]->z = 0.0;		mlx->pyra->triangles[5].points[0]->x = 0.0;
}

void	ft_octahedron_points(t_mlx *mlx)
{
	//T_SOUTH
	mlx->octahedron->triangles[0].points[0]->x = 0.0;
	mlx->octahedron->triangles[0].points[0]->y = 0.0;
	mlx->octahedron->triangles[0].points[0]->z = 0.0;
	
	mlx->octahedron->triangles[0].points[1]->x = 0.5;
	mlx->octahedron->triangles[0].points[1]->y = 1.0;
	mlx->octahedron->triangles[0].points[1]->z = 0.5;

	mlx->octahedron->triangles[0].points[2]->x = 1.0;
	mlx->octahedron->triangles[0].points[2]->y = 0.0;
	mlx->octahedron->triangles[0].points[2]->z = 0.0;

	//T_EAST
	mlx->octahedron->triangles[1].points[0]->x = 1.0;
	mlx->octahedron->triangles[1].points[0]->y = 0.0;
	mlx->octahedron->triangles[1].points[0]->z = 0.0;
	
	mlx->octahedron->triangles[1].points[1]->x = 0.5;
	mlx->octahedron->triangles[1].points[1]->y = 1.0;
	mlx->octahedron->triangles[1].points[1]->z = 0.5;

	mlx->octahedron->triangles[1].points[2]->x = 1.0;
	mlx->octahedron->triangles[1].points[2]->y = 0.0;
	mlx->octahedron->triangles[1].points[2]->z = 1.0;

	//T_NORTH
	mlx->octahedron->triangles[2].points[0]->x = 1.0;
	mlx->octahedron->triangles[2].points[0]->y = 0.0;
	mlx->octahedron->triangles[2].points[0]->z = 1.0;
	
	mlx->octahedron->triangles[2].points[1]->x = 0.5;
	mlx->octahedron->triangles[2].points[1]->y = 1.0;
	mlx->octahedron->triangles[2].points[1]->z = 0.5;

	mlx->octahedron->triangles[2].points[2]->x = 0.0;
	mlx->octahedron->triangles[2].points[2]->y = 0.0;
	mlx->octahedron->triangles[2].points[2]->z = 1.0;

	//T_WEST
	mlx->octahedron->triangles[3].points[0]->x = 0.0;
	mlx->octahedron->triangles[3].points[0]->y = 0.0;
	mlx->octahedron->triangles[3].points[0]->z = 1.0;
	
	mlx->octahedron->triangles[3].points[1]->x = 0.5;
	mlx->octahedron->triangles[3].points[1]->y = 1.0;
	mlx->octahedron->triangles[3].points[1]->z = 0.5;

	mlx->octahedron->triangles[3].points[2]->x = 0.0;
	mlx->octahedron->triangles[3].points[2]->y = 0.0;
	mlx->octahedron->triangles[3].points[2]->z = 0.0;

	//B_SOUTH
	mlx->octahedron->triangles[4].points[0]->x = 0.0;
	mlx->octahedron->triangles[4].points[0]->y = 0.0;
	mlx->octahedron->triangles[4].points[0]->z = 0.0;
	
	mlx->octahedron->triangles[4].points[1]->x = 1.0;
	mlx->octahedron->triangles[4].points[1]->y = 0.0;
	mlx->octahedron->triangles[4].points[1]->z = 0.0;

	mlx->octahedron->triangles[4].points[2]->x = 0.5;
	mlx->octahedron->triangles[4].points[2]->y = -1.0;
	mlx->octahedron->triangles[4].points[2]->z = 0.5;

	//B_EAST
	mlx->octahedron->triangles[5].points[0]->x = 0.5;
	mlx->octahedron->triangles[5].points[0]->y = -1.0;
	mlx->octahedron->triangles[5].points[0]->z = 0.5;
	
	mlx->octahedron->triangles[5].points[1]->x = 1.0;
	mlx->octahedron->triangles[5].points[1]->y = 0.0;
	mlx->octahedron->triangles[5].points[1]->z = 1.0;

	mlx->octahedron->triangles[5].points[2]->x = 1.0;
	mlx->octahedron->triangles[5].points[2]->y = 0.0;
	mlx->octahedron->triangles[5].points[2]->z = 0.0;

	//B_NORTH
	mlx->octahedron->triangles[6].points[0]->x = 1.0;
	mlx->octahedron->triangles[6].points[0]->y = 0.0;
	mlx->octahedron->triangles[6].points[0]->z = 1.0;
	
	mlx->octahedron->triangles[6].points[1]->x = 0.5;
	mlx->octahedron->triangles[6].points[1]->y = -1.0;
	mlx->octahedron->triangles[6].points[1]->z = 0.5;

	mlx->octahedron->triangles[6].points[2]->x = 0.0;
	mlx->octahedron->triangles[6].points[2]->y = 0.0;
	mlx->octahedron->triangles[6].points[2]->z = 1.0;

	//B_WEST
	mlx->octahedron->triangles[7].points[0]->x = 0.0;
	mlx->octahedron->triangles[7].points[0]->y = 0.0;
	mlx->octahedron->triangles[7].points[0]->z = 1.0;
	
	mlx->octahedron->triangles[7].points[1]->x = 0.5;
	mlx->octahedron->triangles[7].points[1]->y = -1.0;
	mlx->octahedron->triangles[7].points[1]->z = 0.5;

	mlx->octahedron->triangles[7].points[2]->x = 0.0;
	mlx->octahedron->triangles[7].points[2]->y = 0.0;
	mlx->octahedron->triangles[7].points[2]->z = 0.0;
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
			mlx->cube->triangles[i].points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
			j++;
		}
		i++;
	}
	ft_cube_points(mlx);
}

void	ft_init_pyra(t_mlx *mlx)
{
	mlx->pyra = (t_mesh*)malloc(sizeof(t_mesh));
	mlx->pyra->tri_count = 6;
	mlx->pyra->triangles = (t_triangle*)malloc(sizeof(t_triangle) * mlx->pyra->tri_count);
	int i = 0;
	while (i < mlx->pyra->tri_count)
	{
		int j = 0;
		while (j < 3)
		{
			mlx->pyra->triangles[i].points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
			j++;
		}
		i++;
	}
	ft_pyra_points(mlx);
}

void	ft_init_octahedron(t_mlx *mlx)
{
	mlx->octahedron = (t_mesh*)malloc(sizeof(t_mesh));
	mlx->octahedron->tri_count = 8;
	mlx->octahedron->triangles = (t_triangle*)malloc(sizeof(t_triangle) * mlx->octahedron->tri_count);
	int i = 0;
	while (i < mlx->octahedron->tri_count)
	{
		int j = 0;
		while (j < 3)
		{
			mlx->octahedron->triangles[i].points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
			j++;
		}
		i++;
	}
	ft_octahedron_points(mlx);
}
