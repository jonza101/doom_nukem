/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transparent.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 15:59:23 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/08/14 17:26:50 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

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
