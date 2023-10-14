# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalama <isalama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 18:09:46 by isalama           #+#    #+#              #
#    Updated: 2023/10/14 15:19:10 by isalama          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d

HELPERS =	helpers/class_helper.c \
			helpers/class_getline.c \
	  	  	helpers/parsing/class_parsing_1.c \
	  	  	helpers/parsing/class_parsing_2.c \
		  	helpers/class_utils.c \
	  	  	helpers/parsing/parsing_utils.c
		  
DRAWERS =	drawers/mlx_window.c \
			drawers/mlx_map.c \
			drawers/mlx_player.c \
			drawers/player/player_directions.c 

LIBFT =		libft/strings_1.c \
			libft/strings_2.c \
			libft/strings_3.c \
			libft/strings_4.c \
			libft/strings_5.c \
			libft/strings_6.c

RAYCAST =	raycasting/raycasting_horizontal.c \
			raycasting/raycasting_vertical.c \
			raycasting/raycasting_utils.c

		
SRC = $(HELPERS) $(DRAWERS) $(LIBFT) $(RAYCAST) cub3d.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -Ofast #-g -fsanitize=address
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