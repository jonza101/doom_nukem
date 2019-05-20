/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:23:44 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/20 18:56:29 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_draw_line_start(t_mlx *mlx, int xo, int yo, int x, int y, int *delta_x, int *delta_y)
{
	if (x < xo)
		*delta_x = -1;
	else
		*delta_x = 1;
	if (y < yo)
		*delta_y = -1;
	else
		*delta_y = 1;
}

void	ft_draw_line(t_mlx *mlx, int xo, int yo, int x, int y, int color)
{
	int angle_x;
	int angle_y;
	int delta_x;
	int delta_y;
	int error;

	angle_x = abs(x - xo);
	angle_y = abs(y - yo);
	error = angle_x - angle_y;
	ft_draw_line_start(mlx, xo, yo, x, y, &delta_x, &delta_y);
	ft_image(mlx, x, y, color);
	while (xo != x || yo != y)
	{
		ft_image(mlx, xo, yo, color);
		if (error * 2 > -angle_y)
		{
			error -= angle_y;
			xo += delta_x;
		}
		else if (error * 2 < angle_x)
		{
			error += angle_x;
			yo += delta_y;
		}
		else
			break ;
	}
}

void	ft_draw_triangle(t_mlx *mlx, int x1, int y1, int x2, int y2, int x3, int y3)
{
	ft_draw_line(mlx, x1, y1, x2, y2, 0xFFFFFF);
	ft_draw_line(mlx, x2, y2, x3, y3, 0xFFFFFF);
	ft_draw_line(mlx, x3, y3, x1, y1, 0xFFFFFF);
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

void	ft_draw(t_mlx *mlx)
{
	ft_init_cube(mlx);
	
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

	t_martix *mat_rot_z;
	t_martix *mat_rot_x;
	t_martix *mat_rot_y;
	mlx->theta += 1.0 * mlx->angle;

	mat_rot_z = (t_martix*)malloc(sizeof(t_martix));
	mat_rot_x = (t_martix*)malloc(sizeof(t_martix));
	mat_rot_y = (t_martix*)malloc(sizeof(t_martix));

	//ROTATION Z
	mat_rot_z->mat[0][0] = cosf(mlx->theta);
	mat_rot_z->mat[0][1] = sinf(mlx->theta);
	mat_rot_z->mat[1][0] = -sinf(mlx->theta);
	mat_rot_z->mat[1][1] = cosf(mlx->theta);
	mat_rot_z->mat[2][2] = 1;
	mat_rot_z->mat[3][3] = 1;

	//ROTATION X
	mat_rot_x->mat[0][0] = 1;
	mat_rot_x->mat[1][1] = cosf(mlx->theta * 0.5);
	mat_rot_x->mat[1][2] = sin(mlx->theta * 0.5);
	mat_rot_x->mat[2][1] = -sinf(mlx->theta * 0.5);
	mat_rot_x->mat[2][2] = cosf(mlx->theta * 0.5);
	mat_rot_x->mat[3][3] = 1;

	//ROTATION Y
	mat_rot_y->mat[0][0] = cosf(mlx->theta * 0.25);
	mat_rot_y->mat[0][2] = -sinf(mlx->theta * 0.25);
	mat_rot_y->mat[1][1] = 1;
	mat_rot_y->mat[2][0] = sinf(mlx->theta * 0.25);
	mat_rot_y->mat[2][2] = cosf(mlx->theta * 0.25);
	mat_rot_y->mat[3][3] = 1;

	int i = 0;
	while (i < 12)
	{
		ft_multiply_matrix_vector(mlx->cube->triangles[i].points[0], mlx->tri_rotated_z->points[0], mat_rot_z);
		ft_multiply_matrix_vector(mlx->cube->triangles[i].points[1], mlx->tri_rotated_z->points[1], mat_rot_z);
		ft_multiply_matrix_vector(mlx->cube->triangles[i].points[2], mlx->tri_rotated_z->points[2], mat_rot_z);

		ft_multiply_matrix_vector(mlx->tri_rotated_z->points[0], mlx->tri_rotated_zx->points[0], mat_rot_x);
		ft_multiply_matrix_vector(mlx->tri_rotated_z->points[1], mlx->tri_rotated_zx->points[1], mat_rot_x);
		ft_multiply_matrix_vector(mlx->tri_rotated_z->points[2], mlx->tri_rotated_zx->points[2], mat_rot_x);

		ft_multiply_matrix_vector(mlx->tri_rotated_zx->points[0], mlx->tri_rotated_zxy->points[0], mat_rot_y);
		ft_multiply_matrix_vector(mlx->tri_rotated_zx->points[1], mlx->tri_rotated_zxy->points[1], mat_rot_y);
		ft_multiply_matrix_vector(mlx->tri_rotated_zx->points[2], mlx->tri_rotated_zxy->points[2], mat_rot_y);


		mlx->tri_translated->points[0] = mlx->tri_rotated_zxy->points[0];
		mlx->tri_translated->points[1] = mlx->tri_rotated_zxy->points[1];
		mlx->tri_translated->points[2] = mlx->tri_rotated_zxy->points[2];

		mlx->tri_translated->points[0]->z = mlx->tri_rotated_zxy->points[0]->z + 3.0;
		mlx->tri_translated->points[1]->z = mlx->tri_rotated_zxy->points[1]->z + 3.0;
		mlx->tri_translated->points[2]->z = mlx->tri_rotated_zxy->points[2]->z + 3.0;

		ft_multiply_matrix_vector(mlx->tri_translated->points[0], mlx->tri_proj->points[0], mlx->mat_proj);
		ft_multiply_matrix_vector(mlx->tri_translated->points[1], mlx->tri_proj->points[1], mlx->mat_proj);
		ft_multiply_matrix_vector(mlx->tri_translated->points[2], mlx->tri_proj->points[2], mlx->mat_proj);

		//SCALE
		mlx->tri_proj->points[0]->x += 1.0;		mlx->tri_proj->points[0]->y += 1.0;
		mlx->tri_proj->points[1]->x += 1.0;		mlx->tri_proj->points[1]->y += 1.0;
		mlx->tri_proj->points[2]->x += 1.0;		mlx->tri_proj->points[2]->y += 1.0;

		mlx->tri_proj->points[0]->x *= 0.5 * W;		mlx->tri_proj->points[0]->y *= 0.5 * H;
		mlx->tri_proj->points[1]->x *= 0.5 * W;		mlx->tri_proj->points[1]->y *= 0.5 * H;
		mlx->tri_proj->points[2]->x *= 0.5 * W;		mlx->tri_proj->points[2]->y *= 0.5 * H;

		ft_draw_triangle(mlx, mlx->tri_proj->points[0]->x, mlx->tri_proj->points[0]->y,
			mlx->tri_proj->points[1]->x, mlx->tri_proj->points[1]->y,
				mlx->tri_proj->points[2]->x, mlx->tri_proj->points[2]->y);

		i++;
	}
}