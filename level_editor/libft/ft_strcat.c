/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 18:16:09 by jsteuber          #+#    #+#             */
/*   Updated: 2019/01/22 18:16:37 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, const char *src)
{
	char	*cp_dest;

	cp_dest = dest;
	while (*cp_dest != '\0')
		cp_dest++;
	while (*src != '\0')
		*cp_dest++ = *src++;
	*cp_dest = '\0';
	return (dest);
}
