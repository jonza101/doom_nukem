/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:22:02 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/12 19:36:25 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int		ft_ctwords(char *start, char c)
{
	unsigned int		i;
	unsigned int		mem;

	i = 0;
	mem = 0;
	while (*start)
	{
		if (*start == c && mem == 1)
			mem = 0;
		if (*start != c && mem == 0)
		{
			mem = 1;
			i++;
		}
		start++;
	}
	return (i);
}
