/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primitive_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 13:54:07 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/10 17:12:24 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_triangle_clear(t_vec2 *v0, t_vec2 *v1, t_vec2 *v2)
{
	v0->x = -1;
	v0->y = -1;
	v1->x = -1;
	v1->y = -1;
	v2->x = -1;
	v2->y = -1;
}

int		ft_orient2d(t_vec2 *a, t_vec2 *b, t_vec2 *c)
{
	return (b->x - a->x) * (c->y - a->y) - (b->y - a->y) * (c->x - a->x);
}

void	ft_triangle_rast(t_mlx *mlx, t_vec2 *v0, t_vec2 *v1, t_vec2 *v2)
{
	int min_x = ft_min(v0->x, ft_min(v1->x, v2->x));
	int min_y = ft_min(v0->y, ft_min(v1->y, v2->y));
	int max_x = ft_max(v0->x, ft_max(v1->x, v2->x));
	int max_y = ft_max(v0->y, ft_max(v1->y, v2->y));

	t_vec2 *p = (t_vec2*)malloc(sizeof(t_vec2));
	p->y = min_y - 1;
	while (++p->y <= max_y)
	{
		p->x = min_x - 1;
		while (++p->x <= max_x)
		{
			int w0 = ft_orient2d(v1, v2, p);
			int w1 = ft_orient2d(v2, v0, p);
			int w2 = ft_orient2d(v0, v1, p);

			if (w0 >= 0 && w1 >= 0 && w2 >= 0)
			{
				mlx->opening[(int)p->y][(int)p->x] = -2;
				ft_image(mlx, p->x, p->y, 0xFFFFFF);
			}
		}
	}
}
