# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalama <isalama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 18:09:46 by isalama           #+#    #+#              #
#    Updated: 2023/10/18 21:15:02 by isalama          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D
			
PARSERS =   parsers/parse_map.c \
	  	  	parsers/parse_attributes.c \
	  	  	parsers/parse_utils.c
		  
DRAWERS =	drawers/window/mlx_window.c \
			drawers/window/mlx_map.c \
			drawers/window/mlx_utils.c \
			drawers/player/mlx_player.c \
			drawers/player/player_directions.c 

HELPERS =	helpers/utils_basics.c \
			helpers/utils_getline.c \
		  	helpers/utils_garbage_collectors.c

LIBFT =		helpers/libft/strings_1.c \
			helpers/libft/strings_2.c \
			helpers/libft/strings_3.c \
			helpers/libft/strings_4.c \
			helpers/libft/strings_5.c \
			helpers/libft/strings_6.c

RAYCAST =	raycasting/raycasting_horizontal.c \
			raycasting/raycasting_vertical.c \
			raycasting/raycasting_utils.c

		
SRC = $(HELPERS) $(DRAWERS) $(LIBFT) $(RAYCAST) $(PARSERS) cub3d.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror
COMPILER = cc

all: $(NAME)

$(NAME): $(OBJ)
	$(COMPILER) $(FLAGS) -Imlx -lmlx -framework OpenGL -framework AppKit  $(OBJ) -o $(NAME)
	@clear

%.o: %.c cub3d.h
	$(COMPILER) $(FLAGS) -c $< -o $@
	@clear
clean:
	rm -rf $(OBJ)
	@clear

fclean: clean
	rm -rf $(NAME)
	@clear

re: fclean all