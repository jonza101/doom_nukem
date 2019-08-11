# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zjeyne-l <zjeyne-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/08 15:22:17 by zjeyne-l          #+#    #+#              #
#    Updated: 2019/08/11 13:43:03 by zjeyne-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c map.c funcs.c render.c move.c init.c thread.c obj.c draw.c game.c keys.c init_weapon.c primitive_draw.c error.c obj_anim.c init_obj.c
SRC += gnl/get_next_line.c gnl/libft/libft.a

all :
	gcc -Ofast $(SRC) -lm -lpthread -lmlx -framework OpenGL -framework AppKit