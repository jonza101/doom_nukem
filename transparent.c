/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:59:23 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/15 12:53:02 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

// void	ft_add_trans_wall(t_mlx *mlx, int n_sect, int side, int index)
// {
// 	t_sector *sector = mlx->sect[n_sect];
// 	if (sector->trans_count > 0)
// 	{

// 	}
// 	else
// 	{
// 		sector->trans_list = (t_trans*)malloc(sizeof(t_trans));
// 		sector->trans_list->sect = n_sect;
// 		sector->trans_list->side = side;
// 		sector->trans_list->trans_i = index;


// 	}
// }

int		ft_find_trans_sect(t_mlx *mlx, int sector, int side)
{
	if (mlx->trans_count <= 0)
		return (-1);
	t_trans *trans = mlx->trans_list;
	while (trans)
	{
		if (mlx->trans_i >= MAX_VISTRANSPARENT)
			return (-1);
		if (trans->sect == sector && trans->side == side)
			return (trans->trans_i);
		trans = trans->next;
	}
	return (-1);
}
