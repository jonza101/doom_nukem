/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:24:18 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/15 18:39:19 by zjeyne-l         ###   ########.fr       */
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

void	ft_map_error()
{
	ft_putstr("Map error!\n");
	exit(0);
}

void	ft_sect_error(int sect)
{
	char *sect_str = ft_itoa(sect);
	char *temp = ft_strdup("Sector ");
	char *tmp = ft_strjoin(temp, sect_str);
	char *str = ft_strjoin(tmp, " is not convex!\n");
	ft_putstr(str);
	free(sect_str);
	free(temp);
	free(tmp);
	free(str);
	ft_map_error();
}

void	ft_obj_error(t_obj *obj, int n)
{
	char *temp = ft_strdup("Object ");
	char *n_str = ft_itoa(n);
	char *tmp = ft_strjoin(temp, n_str);
	char *s = ft_strjoin(tmp, " out of sector ");
	char *sect = ft_itoa(obj->specs->sect);
	char *st = ft_strjoin(s, sect);
	char *str = ft_strjoin(st, "!\n");
	ft_putstr(str);
	free(temp);
	free(n_str);
	free(tmp);
	free(s);
	free(sect);
	free(st);
	free(str);
	ft_map_error();
}

void	ft_player_sect_error()
{
	ft_putstr("Player out of sector!\n");
	ft_map_error();
}

void	ft_player_count_error(int count)
{
	if (count == 0)
		ft_putstr("Player not found!\n");
	if (count > 1)
		ft_putstr("Found more then one player!\n");
	ft_map_error();
}
