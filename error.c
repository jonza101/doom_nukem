/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:24:18 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/13 21:23:59 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	ft_drawseg_error()
{
	ft_putstr("Drawseg overflow!\n");
	exit(0);
}

void	ft_mem_error()
{
	ft_putstr("Memory allocation error!\n");
	exit(0);
}
