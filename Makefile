# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: widraugr <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/17 12:23:41 by widraugr          #+#    #+#              #
#    Updated: 2019/01/17 15:51:08 by widraugr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

LIB_FILE = libft.a

CFILES = check_file.c ft_backtraking.c ft_concat_str.c ft_putfinalboard.c get_coords.c main.c valid_tetrimino.c

OFILES = check_file.o ft_backtraking.o ft_concat_str.o ft_putfinalboard.o get_coords.o main.o valid_tetrimino.o
FLAGS = -Wall -Wextra -Werror

HFILE = -I.

all: $(NAME)

$(NAME):
	make re -C ./libft
	gcc -g $(FLAGS) $(HFILES) -c $(CFILES) 
	gcc -g $(FLAFS) $(OFILES) -L./libft -lft -o $(NAME)
	make fclean -C ./libft 

clean: 
	/bin/rm -f $(OFILES)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
