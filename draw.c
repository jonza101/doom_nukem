/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:23:44 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/26 02:39:40 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_rot_mat_init(t_mlx *mlx)
{
	mlx->mat_rot_z = (t_martix*)malloc(sizeof(t_martix));
	mlx->mat_rot_x = (t_martix*)malloc(sizeof(t_martix));
	mlx->mat_rot_y = (t_martix*)malloc(sizeof(t_martix));
}

void	ft_z_buffer_fill(t_mlx *mlx)
{
	int i;
	int j;
	int max;

	i = 0;
	while (i < H)
	{
		j = 0;
		while (j < W)
		{
			mlx->z_buffer[i][j] = -2147483647.0;
			j++;
		}
		i++;
	}
}

void	ft_multiply_matrix_vector(t_vector_3d *input, t_vector_3d *output, t_martix *matrix)
{
	output->x = input->x * matrix->mat[0][0] + input->y * matrix->mat[1][0] + input->z * matrix->mat[2][0] + matrix->mat[3][0];
	output->y = input->x * matrix->mat[0][1] + input->y * matrix->mat[1][1] + input->z * matrix->mat[2][1] + matrix->mat[3][1];
	output->z = input->x * matrix->mat[0][2] + input->y * matrix->mat[1][2] + input->z * matrix->mat[2][2] + matrix->mat[3][2];
	double w = input->x * matrix->mat[0][3] + input->y * matrix->mat[1][3] + input->z * matrix->mat[2][3] + matrix->mat[3][3];

	if (w != 0.0)
	{
		output->x /= w;
		output->y /= w;
		output->z /= w;
	}
}

void	ft_draw(t_mlx *mlx, t_mesh *fig)
{
	double z_far = 0.1;
	double z_near = 1000;
	double fov = 90;
	double aspect_ratio = (double)H / (double)W;
	double fov_rad = 1.0 / tanf(fov / 2.0 / 180.0 * 3.14159);

	mlx->mat_proj->mat[0][0] = aspect_ratio * fov_rad;
	mlx->mat_proj->mat[1][1] = fov_rad;
	mlx->mat_proj->mat[2][2] = z_far / (z_far - z_near);
	mlx->mat_proj->mat[3][2] = (-z_far * z_near) / (z_far - z_near);
	mlx->mat_proj->mat[2][3] = 1.0;
	mlx->mat_proj->mat[3][3] = 0.0;

	mlx->theta += 1.0 * mlx->angle;

	//ROTATION Z
	mlx->mat_rot_z->mat[0][0] = cosf(mlx->theta);
	mlx->mat_rot_z->mat[0][1] = sinf(mlx->theta);
	mlx->mat_rot_z->mat[1][0] = -sinf(mlx->theta);
	mlx->mat_rot_z->mat[1][1] = cosf(mlx->theta);
	mlx->mat_rot_z->mat[2][2] = 1;
	mlx->mat_rot_z->mat[3][3] = 1;

	//ROTATION X
	mlx->mat_rot_x->mat[0][0] = 1;
	mlx->mat_rot_x->mat[1][1] = cosf(mlx->theta * 0.5);
	mlx->mat_rot_x->mat[1][2] = sin(mlx->theta * 0.5);
	mlx->mat_rot_x->mat[2][1] = -sinf(mlx->theta * 0.5);
	mlx->mat_rot_x->mat[2][2] = cosf(mlx->theta * 0.5);
	mlx->mat_rot_x->mat[3][3] = 1;

	//ROTATION Y
	mlx->mat_rot_y->mat[0][0] = cosf(mlx->theta * 0.25);
	mlx->mat_rot_y->mat[0][2] = -sinf(mlx->theta * 0.25);
	mlx->mat_rot_y->mat[1][1] = 1;
	mlx->mat_rot_y->mat[2][0] = sinf(mlx->theta * 0.25);
	mlx->mat_rot_y->mat[2][2] = cosf(mlx->theta * 0.25);
	mlx->mat_rot_y->mat[3][3] = 1;

	int i = 0;
	while (i < fig->tri_count)
	{
		ft_multiply_matrix_vector(fig->triangles[i].points[0], mlx->tri_rotated_z->points[0], mlx->mat_rot_z);
		ft_multiply_matrix_vector(fig->triangles[i].points[1], mlx->tri_rotated_z->points[1], mlx->mat_rot_z);
		ft_multiply_matrix_vector(fig->triangles[i].points[2], mlx->tri_rotated_z->points[2], mlx->mat_rot_z);

		ft_multiply_matrix_vector(mlx->tri_rotated_z->points[0], mlx->tri_rotated_zx->points[0], mlx->mat_rot_x);
		ft_multiply_matrix_vector(mlx->tri_rotated_z->points[1], mlx->tri_rotated_zx->points[1], mlx->mat_rot_x);
		ft_multiply_matrix_vector(mlx->tri_rotated_z->points[2], mlx->tri_rotated_zx->points[2], mlx->mat_rot_x);

		// ft_multiply_matrix_vector(mlx->tri_rotated_zx->points[0], mlx->tri_rotated_zxy->points[0], mlx->mat_rot_y);
		// ft_multiply_matrix_vector(mlx->tri_rotated_zx->points[1], mlx->tri_rotated_zxy->points[1], mlx->mat_rot_y);
		// ft_multiply_matrix_vector(mlx->tri_rotated_zx->points[2], mlx->tri_rotated_zxy->points[2], mlx->mat_rot_y);

		mlx->tri_translated->points[0] = mlx->tri_rotated_zx->points[0];
		mlx->tri_translated->points[1] = mlx->tri_rotated_zx->points[1];
		mlx->tri_translated->points[2] = mlx->tri_rotated_zx->points[2];

		//OFFSET INTO SCREEN
		mlx->tri_translated->points[0]->z = mlx->tri_rotated_zx->points[0]->z + mlx->zoom;
		mlx->tri_translated->points[1]->z = mlx->tri_rotated_zx->points[1]->z + mlx->zoom;
		mlx->tri_translated->points[2]->z = mlx->tri_rotated_zx->points[2]->z + mlx->zoom;

		mlx->line_1->x = mlx->tri_translated->points[1]->x - mlx->tri_translated->points[0]->x;
		mlx->line_1->y = mlx->tri_translated->points[1]->y - mlx->tri_translated->points[0]->y;
		mlx->line_1->z = mlx->tri_translated->points[1]->z - mlx->tri_translated->points[0]->z;

		mlx->line_2->x = mlx->tri_translated->points[2]->x - mlx->tri_translated->points[0]->x;
		mlx->line_2->y = mlx->tri_translated->points[2]->y - mlx->tri_translated->points[0]->y;
		mlx->line_2->z = mlx->tri_translated->points[2]->z - mlx->tri_translated->points[0]->z;

		mlx->normal->x = mlx->line_1->y * mlx->line_2->z - mlx->line_1->z * mlx->line_2->y;
		mlx->normal->y = mlx->line_1->z * mlx->line_2->x - mlx->line_1->x * mlx->line_2->z;
		mlx->normal->z = mlx->line_1->x * mlx->line_2->y - mlx->line_1->y * mlx->line_2->x;

		double normal_len = sqrtf(powf(mlx->normal->x, 2) + powf(mlx->normal->y, 2) + powf(mlx->normal->z, 2));
		mlx->normal->x /= normal_len;
		mlx->normal->y /= normal_len;
		mlx->normal->z /= normal_len;

		if (mlx->normal->x * (mlx->tri_translated->points[0]->x - mlx->v_camera->x) +
			mlx->normal->y * (mlx->tri_translated->points[0]->y - mlx->v_camera->y) +
			mlx->normal->z * (mlx->tri_translated->points[0]->z - mlx->v_camera->z) < 0.0)
		{
			double light_normanl_len = sqrtf(powf(mlx->light_dir->x, 2) + powf(mlx->light_dir->y, 2) + powf(mlx->light_dir->z, 2));
			mlx->light_dir->x /= light_normanl_len;
			mlx->light_dir->y /= light_normanl_len;
			mlx->light_dir->z /= light_normanl_len;

			double dot_prod = mlx->normal->x * mlx->light_dir->x + mlx->normal->y * mlx->light_dir->y + mlx->normal->z * mlx->light_dir->z;

			//PROJECT TRIANGLES FROM 3D TO 2D
			ft_multiply_matrix_vector(mlx->tri_translated->points[0], mlx->tri_proj->points[0], mlx->mat_proj);
			ft_multiply_matrix_vector(mlx->tri_translated->points[1], mlx->tri_proj->points[1], mlx->mat_proj);
			ft_multiply_matrix_vector(mlx->tri_translated->points[2], mlx->tri_proj->points[2], mlx->mat_proj);

			//COLOR
			mlx->tri_proj->color = ft_get_color(ft_dec_to_hex(fig->triangles->color), dot_prod);

			//SCALE
			mlx->tri_proj->points[0]->x += 1.0;		mlx->tri_proj->points[0]->y += 1.0;
			mlx->tri_proj->points[1]->x += 1.0;		mlx->tri_proj->points[1]->y += 1.0;
			mlx->tri_proj->points[2]->x += 1.0;		mlx->tri_proj->points[2]->y += 1.0;

			mlx->tri_proj->points[0]->x *= 0.5 * W;		mlx->tri_proj->points[0]->y *= 0.5 * H;
			mlx->tri_proj->points[1]->x *= 0.5 * W;		mlx->tri_proj->points[1]->y *= 0.5 * H;
			mlx->tri_proj->points[2]->x *= 0.5 * W;		mlx->tri_proj->points[2]->y *= 0.5 * H;

			ft_fill_triangle(mlx, mlx->tri_proj->points[0], mlx->tri_proj->points[1], mlx->tri_proj->points[2], mlx->tri_proj->color);

			// ft_draw_triangle(mlx, mlx->tri_proj->points[0]->x, mlx->tri_proj->points[0]->y,
			// 									mlx->tri_proj->points[1]->x, mlx->tri_proj->points[1]->y,
			// 									mlx->tri_proj->points[2]->x, mlx->tri_proj->points[2]->y, 0xFFFFFF);
		}
		i++;
	}
}