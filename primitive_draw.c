/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 20:08:11 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/22 19:32:53 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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

void	ft_fill_triangle(t_mlx *mlx, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
	if (y1 == y2 && y1 == y3)
		return ;
	//SORT
	if (y1 > y2)
	{
		ft_swap(&x1, &x2);
		ft_swap(&y1, &y2);
	}
	if (y1 > y3)
	{
		ft_swap(&x1, &x3);
		ft_swap(&y1, &y3);
	}
	if (y2 > y3)
	{
		ft_swap(&x2, &x3);
		ft_swap(&y2, &y3);
	}
	//

	int total_h = y3 - y1;
	int i = 0;
	while (i < total_h)
	{
		int second_half = (i > y2 - y1 || y2 == y1) ? 1 : 0;
		int segment_h = (second_half == 1) ? y3 - y2 : y2 - y1;
		double alpha = (double)i / total_h;
		double beta = (double)(i - (second_half == 1 ? y2 - y1 : 0)) / segment_h;
		int a_x = x1 + (x3 - x1) * alpha;
		int a_y = y1 + (y3 - y1) * alpha;
		int b_x = (second_half == 1) ? x2 + (x3 - x2) * beta : x1 + (x2 - x1) * beta;
		int b_y = (second_half == 1) ? y2 + (y3 - y2) * beta : y1 + (y2 - y1) * beta;

		if (a_x > b_x)
		{
			ft_swap(&a_x, &b_x);
			ft_swap(&a_y, &b_y);
		}

		int j = a_x;
		while (j <= b_x)
		{
			ft_image(mlx, j, y1 + i, color);
			j++;
		}
		i++;
	}
}
