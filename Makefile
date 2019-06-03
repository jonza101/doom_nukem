# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/17 17:00:52 by zjeyne-l          #+#    #+#              #
#    Updated: 2019/06/03 22:56:00 by zjeyne-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c map.c funcs.c gnl/get_next_line.c gnl/libft/libft.a

all :
	gcc -g -Ofast $(SRC) -lm -lmlx -lXext -lX11 -L minilibx/ -I minilibx/