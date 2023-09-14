# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: isalama <isalama@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/15 18:09:46 by isalama           #+#    #+#              #
#    Updated: 2023/09/14 18:16:23 by isalama          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3d
SRC = cub3d.c helpers/helper_class.c helpers/get_next_line.c \
	  helpers/parsing_class.c

LIBFT = libft/strings_1.c libft/strings_2.c
OBJ = $(SRC:.c=.o) $(LIBFT:.c=.o)
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