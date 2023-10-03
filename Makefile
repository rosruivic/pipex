# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/18 13:12:22 by roruiz-v          #+#    #+#              #
#    Updated: 2023/10/03 12:39:08 by roruiz-v         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRC		=	pipex.c \
			000_pipex_errors.c \
			100_init_data.c \
			200_forks.c \
			900_free_all.c

OBJS	= $(SRC:.c=.o)
OFILES = $(addprefix obj/, $(OBJS))

CC		= gcc

FLAGS	= -Wall -Werror -Wextra #-fsanitize=address

EXTRA	=	-framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/roruiz-v/.brew/opt/glfw/lib/"

#LEAKS = memory-leaks/memory_leaks.a

LIBFT_PATH = libft/libft.a

all:	$(NAME)

#	We cannot call (LIBFT) or (MLX42) in (NAME) because it would be searching for the
#	".a" files before creating them, resulting in an error. We 1st create the rules to
#	compile both libft and MLX42, and then we compile the .a files of both libraries
#	with the apropiate flags and frameworks.

$(NAME): $(OFILES) $(LIBFT_PATH) $(MLX42_PATH)
		$(CC) $(FLAGS) $(EXTRA) $(OFILES) $(LIBFT_PATH) -o $(NAME)
		clear
		
$(OFILES): $(SRC)
		@mkdir -p obj/
		gcc -Wall -Wextra -Werror -c $(SRC)
		@mv *.o obj/

# If a debug with lldb is needed, do 'make' with this rule:
debug: $(LIBFT_PATH)
		$(CC) $(FLAGS) $(EXTRA) $(SRC) $(LIBFT_PATH) -o $(NAME) -g
		clear

clean:
		rm -rf obj objb
		make -C libft clean

fclean: clean
		@make fclean -C libft/
		@rm $(NAME)

re:	fclean all

$(LIBFT_PATH):
		make -C libft all


.PHONY: all clean fclean re
