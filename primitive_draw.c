/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:08:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/26 02:39:42 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_vec_swap(t_vector_3d *a, t_vector_3d *b)
{
	t_vector_3d *temp;

	temp = (t_vector_3d*)malloc(sizeof(t_vector_3d));	
	temp->x = a->x;
	temp->y = a->y;
	temp->z = a->z;
	a->x = (int)b->x;
	a->y = (int)b->y;
	a->z = (int)b->z;
	b->x = (int)temp->x;
	b->y = (int)temp->y;
	b->z = (int)temp->z;
}

void	ft_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

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

void	ft_draw_triangle(t_mlx *mlx, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
	ft_draw_line(mlx, x1, y1, x2, y2, color);
	ft_draw_line(mlx, x2, y2, x3, y3, color);
	ft_draw_line(mlx, x3, y3, x1, y1, color);
}

void	ft_fill_triangle(t_mlx *mlx, t_vector_3d *p0, t_vector_3d *p1, t_vector_3d *p2, int color)
{
	if ((int)p0->y == (int)p1->y && (int)p0->y == (int)p2->y)
		return ;
	//SORT
	if ((int)p0->y > (int)p1->y)
		ft_vec_swap(p0, p1);
	if ((int)p0->y > (int)p2->y)
		ft_vec_swap(p0, p2);
	if ((int)p1->y > (int)p2->y)
		ft_vec_swap(p1, p2);
	//

	int total_h = (int)p2->y - (int)p0->y;
	int i = 0;
	while (i < total_h)
	{
		int second_half = (i > (int)p1->y - (int)p0->y || (int)p1->y == (int)p0->y) ? 1 : 0;
		int segment_h = (second_half == 1) ? (int)p2->y - (int)p1->y : (int)p1->y - (int)p0->y;
		double alpha = (double)i / total_h;
		double beta = (double)(i - (second_half == 1 ? (int)p1->y - (int)p0->y : 0)) / segment_h;

		t_vector_3d *a = (t_vector_3d*)malloc(sizeof(t_vector_3d));
		a->x = (int)((int)p0->x + ((int)p2->x - (int)p0->x) * alpha);
		a->y = (int)((int)p0->y + ((int)p2->y - (int)p0->y) * alpha);
		a->z = (int)((int)p0->z + ((int)p2->z - (int)p0->z) * alpha);

		t_vector_3d *b = (t_vector_3d*)malloc(sizeof(t_vector_3d));
		b->x = (second_half == 1) ? (int)((int)p1->x + ((int)p2->x - (int)p1->x) * beta) : (int)((int)p0->x + ((int)p1->x - (int)p0->x) * beta);
		b->y = (second_half == 1) ? (int)((int)p1->y + ((int)p2->y - (int)p1->y) * beta) : (int)((int)p0->y + ((int)p1->y - (int)p0->y) * beta);
		b->z = (second_half == 1) ? (int)((int)p1->z + ((int)p2->z - (int)p1->z) * beta) : (int)((int)p0->z + ((int)p1->z - (int)p0->z) * beta);

		if (a->x > b->x)
			ft_vec_swap(a, b);

		int j = a->x;
		while (j <= b->x)
		{
			// double phi = (b->x == a->x) ? 1.0 : (double)(j - a->x) / (double)(b->x - a->x);

			// t_vector_3d *p = (t_vector_3d*)malloc(sizeof(t_vector_3d));
			// p->x = (int)((double)a->x + (double)(b->x - a->x) * phi);
			// p->y = (int)((double)a->y + (double)(b->y - a->y) * phi);
			// p->z = (int)((double)a->z + (double)(b->z - a->z) * phi);

			// // printf("pz %f		z_buf %f\n", p->z, mlx->z_buffer[(int)p->y][(int)p->x]);
			// if ((p->x >= 0 && p->x < W && p->y >= 0 && p->y < H &&
			// 	p->z >= mlx->z_buffer[(int)p->y][(int)p->x]))
			// {
			// 	mlx->z_buffer[(int)p->y][(int)p->x] = p->z;
				ft_image(mlx, /*p->x*/j, /*p->y*/ p0->y + i, color);
			// }
			//free(p);
			j++;
		}
		free(a);
		free(b);
		i++;
	}
}
