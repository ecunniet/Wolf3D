# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecunniet <ecunniet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/14 23:03:00 by ecunniet          #+#    #+#              #
#    Updated: 2017/04/25 13:52:33 by ecunniet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = wolf3d
SRCS = srcs/ft_error.c \
	srcs/main.c \
	srcs/ft_parser.c \
	srcs/ft_hook_keyboard.c
OBJ = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Begining Wolf3D"
	make -C libft
	make -C minilibx_macos
	gcc -o $(NAME) $(FLAGS) $(OBJ) -L minilibx_macos -lmlx -framework OpenGL -framework AppKit libft/libft.a minilibx_macos/libmlx.a
	@echo "Wolf3D Done"

clean:
	make clean -C libft
	make clean -C minilibx_macos
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

norme:
	@norminette $(SRCS) $(POINTH)
	@norminette libft/

.PHONY: all clean fclean re norme
