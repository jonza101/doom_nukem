/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:54:13 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/05/23 21:53:12 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_image(t_mlx *mlx, int x, int y, int color)
{
	if (x >= 0 && x < W && y >= 0 && y < H)
		mlx->data[x + y * W] = mlx_get_color_value(mlx->mlx, color);
}

void	ft_reset_image(t_mlx *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);
	mlx_clear_window(mlx->mlx, mlx->win);
}

int		key_press(int keycode, t_mlx *mlx)
{
	// printf("%d\n", keycode);
	(keycode == 65307) ? exit(0) : 1;
	if (keycode == 1739)
	{
		mlx->angle = -0.05;
		ft_reset_image(mlx);
		ft_draw(mlx, mlx->ch_fig);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	}
}

int		main()
{
	t_mlx	*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Doom-Nukem");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	mlx->mat_proj = (t_martix*)malloc(sizeof(t_martix));
	mlx->tri_proj = (t_triangle*)malloc(sizeof(t_triangle));
	mlx->tri_translated = (t_triangle*)malloc(sizeof(t_triangle));
	mlx->tri_rotated_z = (t_triangle*)malloc(sizeof(t_triangle));
	mlx->tri_rotated_zx = (t_triangle*)malloc(sizeof(t_triangle));
	mlx->tri_rotated_zxy = (t_triangle*)malloc(sizeof(t_triangle));

	mlx->normal = (t_vector_3d*)malloc(sizeof(t_vector_3d));
	mlx->line_1 = (t_vector_3d*)malloc(sizeof(t_vector_3d));
	mlx->line_2 = (t_vector_3d*)malloc(sizeof(t_vector_3d));

	mlx->v_camera = (t_vector_3d*)malloc(sizeof(t_vector_3d));

	mlx->light_dir = (t_vector_3d*)malloc(sizeof(t_vector_3d));
	mlx->light_dir->x = 0.0;
	mlx->light_dir->y = 0.0;
	mlx->light_dir->z = -1.0;

	int j = 0;
	while (j < 3)
	{
		mlx->tri_proj->points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
		mlx->tri_translated->points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
		mlx->tri_rotated_z->points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
		mlx->tri_rotated_zx->points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));
		mlx->tri_rotated_zxy->points[j] = (t_vector_3d*)malloc(sizeof(t_vector_3d));

		j++;
	}

	ft_z_buffer_fill(mlx);

	ft_init_cube(mlx);

	mlx->ch_fig = mlx->cube;
	ft_draw(mlx, mlx->ch_fig);

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
