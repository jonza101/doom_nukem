/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:08:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/24 22:52:54 by zjeyne-l         ###   ########.fr       */
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
	a->x = b->x;
	a->y = b->y;
	a->z = b->z;
	b->x = temp->x;
	b->y = temp->y;
	b->z = temp->z;
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

void	ft_fill_triangle(t_mlx *mlx, t_vector_3d *p1, t_vector_3d *p2, t_vector_3d *p3, int color)
{
	if ((int)p1->y == (int)p2->y && (int)p1->y == (int)p3->y)
		return ;
	//SORT
	if (p1->y > p2->y)
	{
		int tmp = (int)p1->x;
		p1->x = p2->x;
		p2->x = tmp;

		tmp = (int)p1->y;
		p1->y = (int)p2->y;
		p2->y = tmp;
		
		// ft_swap(&p1->x, &p2->x);
		// ft_swap(&p1->y, &p2->y);
	}
	if (p1->y > p3->y)
	{
		int tmp = (int)p1->x;
		p1->x = (int)p3->x;
		p3->x = tmp;

		tmp = (int)p1->y;
		p1->y = (int)p3->y;
		p3->y = tmp;

		// ft_swap(&p1->x, &p3->x);
		// ft_swap(&p1->y, &p3->y);
	}
	if (p2->y > p3->y)
	{
		int tmp = (int)p2->x;
		p2->x = (int)p3->x;
		p3->x = tmp;

		tmp = (int)p2->y;
		p2->y = (int)p3->y;
		p3->y = tmp;

		// ft_swap(&p2->x, &p3->x);
		// ft_swap(&p2->y, &p3->y);
	}
	//

	int total_h = (int)p3->y - (int)p1->y;
	int i = 0;
	while (i < total_h)
	{
		int second_half = (i > (int)p2->y - (int)p1->y || (int)p2->y == (int)p1->y) ? 1 : 0;
		int segment_h = (second_half == 1) ? (int)p3->y - (int)p2->y : (int)p2->y - (int)p1->y;
		double alpha = (double)i / total_h;
		double beta = (double)(i - (second_half == 1 ? (int)p2->y - (int)p1->y : 0)) / segment_h;
		int a_x = (int)p1->x + (p3->x - p1->x) * alpha;
		int a_y = (int)p1->y + (p3->y - p1->y) * alpha;
		int a_z = (int)p1->z + (p3->z - p1->z) * alpha;
		int b_x = (second_half == 1) ? (int)p2->x + (p3->x - p2->x) * beta : (int)p1->x + (p2->x - p1->x) * beta;
		int b_y = (second_half == 1) ? (int)p2->y + (p3->y - p2->y) * beta : (int)p1->y + (p2->y - p1->y) * beta;
		int b_z = (second_half == 1) ? (int)p2->z + (p3->z - p2->z) * beta : (int)p1->z + (p2->z - p1->z) * beta;

		if (a_x > b_x)
		{
			ft_swap(&a_x, &b_x);
			ft_swap(&a_y, &b_y);
			ft_swap(&a_z, &b_z);
		}

		int j = a_x;
		while (j <= b_x)
		{
			double phi = (b_x == a_x) ? 1.0 : (double)(j - a_x) / (double)(b_x - a_x);
			int p_x = (double)a_x + (double)(b_x - a_x) * phi;
			int p_y = (double)a_y + (double)(b_y - a_y) * phi;
			int p_z = (double)a_z + ((double)b_z - a_z) * phi;

			if (p_x >= 0 && p_x < W && p_y >= 0 && p_y < H && mlx->z_buffer[p_x][p_y] <= p_z)
			{
				// printf("px %d		py %d\n", p_x, p_y);
				mlx->z_buffer[p_x][p_y] = p_z;
				ft_image(mlx, j, (int)p1->y + i, color);
			}
			j++;
		}
		i++;
	}
}

// void	ft_fill_triangle(t_mlx *mlx, t_vector_3d *p1, t_vector_3d *p2, t_vector_3d *p3, int color)
// {
// 	if (p1->y == (int)p2->y && (int)p1->y == (int)p3->y)
// 		return ;
// 	//SORT
// 	if (p1->y > p2->y)
// 		ft_vec_swap(p1, p2);
// 	if (p1->y > p3->y)
// 		ft_vec_swap(p1, p3);
// 	if (p2->y > p3->y)
// 		ft_vec_swap(p2, p3);
// 	//

// 	int total_h = (int)p3->y - (int)p1->y;
// 	int i = 0;
// 	while (i < total_h)
// 	{
// 		int second_half = (i > (int)p2->y - (int)p1->y || (int)p2->y == (int)p1->y) ? 1 : 0;
// 		int segment_h = (second_half == 1) ? (int)p3->y - (int)p2->y : (int)p2->y - (int)p1->y;
// 		double alpha = (double)i / total_h;
// 		double beta = (double)(i - (second_half == 1 ? (int)p2->y - (int)p1->y : 0)) / segment_h;

// 		t_vector_3d *a = (t_vector_3d*)malloc(sizeof(t_vector_3d));
// 		a->x = (int)p1->x + (p3->x - p1->x) * alpha;
// 		a->y = (int)p1->y + (p3->y - p1->y) * alpha;
// 		a->z = (int)p1->z + (p3->z - p1->z) * alpha;

// 		t_vector_3d *b = (t_vector_3d*)malloc(sizeof(t_vector_3d));
// 		b->x = (second_half == 1) ? (int)p2->x + (p3->x - p2->x) * beta : (int)p1->x + (p2->x - p1->x) * beta;
// 		b->y = (second_half == 1) ? (int)p2->y + (p3->y - p2->y) * beta : (int)p1->y + (p2->y - p1->y) * beta;
// 		b->z = (second_half == 1) ? (int)p2->z + (p3->z - p2->z) * beta : (int)p1->z + (p2->z - p1->z) * beta;

// 		if (a->x > b->x)
// 			ft_vec_swap(a, b);

// 		int j = a->x;
// 		while (j <= b->x)
// 		{
// 			double phi = (b->x == a->x) ? 1.0 : (double)(j - a->x) / (double)(b->x - a->x);

// 			t_vector_3d *p = (t_vector_3d*)malloc(sizeof(t_vector_3d));
// 			p->x = (double)a->x + (double)(b->x - a->x) * phi;
// 			p->y = (double)a->y + (double)(b->y - a->y) * phi;
// 			p->z = (double)a->z + (double)(b->z - a->z) * phi;

// 			if (p->x >= 0 && p->x < W && p->y >= 0 && p->y < H && mlx->z_buffer[(int)p->x][(int)p->y] < p->z)
// 			{
// 				// printf("px %d		py %d\n", p_x, p_y);
// 				mlx->z_buffer[(int)p->x][(int)p->y] = p->z;
// 				ft_image(mlx, (int)p->x, (int)p->y, color);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }
