/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 18:23:44 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/17 20:24:24 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_draw(t_mlx *mlx)
{
	double z_far = 0.1;
	double z_near = 1000;
	double fov = 90;
	double aspect_ratio = (double)H / (double)W;
	double fov_rad = 1.0 / tanf(fov / 2.0 / 180.0 * 3.14159);

	ft_init_cube(mlx);
}