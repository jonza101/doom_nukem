# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/08 15:22:17 by zjeyne-l          #+#    #+#              #
#    Updated: 2019/06/11 15:11:19 by zjeyne-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c map.c funcs.c draw.c move.c gnl/get_next_line.c gnl/libft/libft.a

all :
	gcc -Ofast $(SRC) -lm -lpthread -lmlx -lXext -lX11 -L minilibx/ -I minilibx/