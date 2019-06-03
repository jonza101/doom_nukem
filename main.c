/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:54:13 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/06/03 22:43:05 by zjeyne-l         ###   ########.fr       */
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
}

int		main()
{
	t_mlx	*mlx;

	mlx = (t_mlx*)malloc(sizeof(t_mlx));
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, W, H, "Doom-Nukem");
	mlx->img = mlx_new_image(mlx->mlx, W, H);
	mlx->data = (int *)mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line, &mlx->endian);

	ft_load_map(mlx, "map");

	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);

	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
