/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 14:49:08 by zjeyne-l          #+#    #+#             */
/*   Updated: 2019/09/16 17:48:05 by zjeyne-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_cut_line(char **temp, int fd, char **line, int len)
{
	int		i;
	char	*str;

	i = 0;
	while (temp[fd][i] && temp[fd][i] != '\n')
		i++;
	if (temp[fd][i] == '\n')
	{
		*line = ft_strsub(temp[fd], 0, i);
		str = ft_strdup(&temp[fd][i + 1]);
		free(temp[fd]);
		temp[fd] = ft_strdup(str);
		free(str);
		if (!temp[fd][0])
			ft_strdel(&temp[fd]);
	}
	else if (!temp[fd][i])
	{
		if (len == BUFF_SIZE)
			get_next_line(fd, line);
		*line = ft_strdup(temp[fd]);
		ft_strdel(&temp[fd]);
	}
}

int		ft_newline_check(char *buff)
{
	int i;

	i = 0;
	while (buff[i])
	{
		if (buff[i] == '\n')
			return (0);
		i++;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static	char	*temp[1];
	char			*buff;
	char			*t;
	int				len;

	if (fd < 0 || !(buff = (char*)malloc(BUFF_SIZE + 1)))
		return (-1);
	while ((len = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[len] = '\0';
		if (temp[fd] == NULL)
			temp[fd] = ft_strnew(1);
		t = ft_strjoin(temp[fd], buff);
		free(temp[fd]);
		temp[fd] = t;
		if (ft_newline_check(buff) == 0)
			break ;
	}
	free(buff);
	if (len < 0)
		return (-1);
	if (len == 0 && (temp[fd] == NULL || temp[fd][0] == '\0'))
		return (0);
	ft_cut_line(temp, fd, line, len);
	return (1);
}
