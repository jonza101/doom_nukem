# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsteuber <jsteuber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/06 15:55:47 by jsteuber          #+#    #+#              #
#    Updated: 2019/09/24 17:41:59 by jsteuber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=Editor

CFLAGS=-Wall -Wextra -Werror
FFLAGS=-framework OpenGL -framework AppKit

SRC_PATH=./src
INC_PATH=./include
MLX_PATH=./minilibx_macos
MLX_INC_PATH=/usr/X11/include
FT_PATH=./libft
BIN_PATH=./bin

SRC= main.c image.c init.c show.c actions.c actions2.c actions3.c \
walls.c walls2.c selection.c context_menu.c gui.c \
gui_func.c gui_func2.c sectors.c sectors2.c sectors3.c colors.c \
output.c output2.c output3.c output4.c input.c input2.c input3.c grid.c \
objects.c objects2.c objects3.c player.c sec_list.c validation.c \
im_events_wall.c im_canvas_wall.c im_canvas_obj.c im_events_obj.c \
im_canvas_sec.c im_events_sec.c raycast.c sec_list2.c sec_list3.c \
sec_list4.c gnl_struct.c utilities.c utilities2.c utilities3.c \
bresenham.c
OBJ:= $(addprefix $(BIN_PATH)/,$(SRC:.c=.o))

.PHONY: all clean fclean re

all: $(BIN_PATH) $(NAME)

$(BIN_PATH):
	mkdir -p bin

$(NAME): $(OBJ) $(INC_PATH)/editor.h
	@make -s -C $(FT_PATH)
	gcc -o $@ $(OBJ) -L$(MLX_PATH) -lmlx -I$(MLX_INC_PATH) -L$(FT_PATH) -lft -I$(FT_PATH) $(FFLAGS)

$(BIN_PATH)/%.o: $(SRC_PATH)/%.c
	gcc -g $(CFLAGS) -o $@ -c $< -I$(INC_PATH) -I$(FT_PATH)

clean:
	@make -s -C $(FT_PATH) fclean
	rm -rf $(BIN_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
