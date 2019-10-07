/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_struct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 18:49:55 by jsteuber          #+#    #+#             */
/*   Updated: 2019/10/07 20:13:52 by jsteuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "stdlib.h"

void					prepare_gnlstr(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

static void				rewrite(char **str, char **line)
{
	size_t	n;
	size_t	ll;

	if ((*str) == NULL)
		return ;
	n = 0;
	while ((*str)[n] != '\n' && (*str)[n] != '\0')
		n++;
	*line = ft_strsub(*str, 0, n);
	ll = ft_strlen(*str + n);
	ft_memmove(*str, *str + n + 1, ll);
	(*str)[ll] = '\0';
}

static int				readbuf(char *buf, char **str, const int fd)
{
	int			bytesnumb;
	char		*tmp;

	if ((bytesnumb = read(fd, buf, BUFF_SIZE)) == -1)
	{
		ft_strdel(str);
		return (-1);
	}
	buf[bytesnumb] = '\0';
	tmp = *str;
	*str = ft_strjoin(*str, buf);
	ft_strdel(&tmp);
	return (bytesnumb);
}

static void				zeroex(char **arr, int *ret)
{
	ft_strdel(arr);
	*ret = 0;
}

int						gnl_struct(char **gnlstr, const int fd, char **line)
{
	int				bytesnumb;
	char			buf[BUFF_SIZE + 1];
	int				ret;

	if (fd < 0 || !line || read(fd, NULL, 0) < 0)
		return (-1);
	*line = NULL;
	bytesnumb = 1;
	ret = 1;
	buf[0] = '\0';
	if (*gnlstr == NULL)
	{
		if ((*gnlstr = ft_strnew(0)) == NULL)
			return (-1);
	}
	while (!ft_strchr(buf, '\n') && bytesnumb != 0)
	{
		if ((bytesnumb = readbuf(buf, gnlstr, fd)) == -1)
			return (-1);
		else if (bytesnumb == 0 && *gnlstr[0] == '\0')
			zeroex(gnlstr, &ret);
	}
	rewrite((char **)gnlstr, line);
	return (ret);
}
