# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adoyle <adoyle@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/08 15:22:17 by zjeyne-l          #+#    #+#              #
#    Updated: 2019/09/08 14:12:39 by adoyle           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = main.c map.c funcs.c render.c move.c init.c thread.c obj.c draw.c game.c keys.c init_weapon.c error.c obj_anim.c init_obj.c ray.c transparent.c wobj.c init_wobj.c init_boost.c mouse_rotation.c mouse_hooks.c soundeff.c
SRC += gnl/get_next_line.c gnl/libft/libft.a

all :
	gcc -g -Ofast $(SRC) -lm -lpthread -lmlx -framework OpenGL -framework AppKit -L /Users/adoyle/homebrew/lib -lSDL2-2.0.0 -I /Users/adoyle/homebrew/include -L /Users/adoyle/homebrew/lib -lSDL2_mixer-2.0.0