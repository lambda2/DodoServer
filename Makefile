# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aaubin <aaubin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/02/22 03:19:43 by aaubin            #+#    #+#              #
#    Updated: 2014/02/23 01:58:29 by aaubin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=clang
LKFLAGS=-Wall -Wextra -pedantic -I./c_vector -I./libft/includes -Werror\
		-L./libft -lft -L./c_vector -lvector
CFLAGS=-Wall -Wextra -pedantic -I./c_vector -I./libft/includes
LDFLAGS=-g
NAME=DodoServer
SRC=main.c\
	handlers.c\
	request.c\
	file_reader.c\
	main.c\
	http_head.c\
	get_next_line.c\
	parser.c\
	server.c

NOM=$(basename $(SRC))
OBJ=$(addsuffix .o, $(NOM))

all: makelib normal

normal: $(NAME)

makelib:
	@git submodule update --init -q
	@make -f Makefile -C libft
	@make -f Makefile -C c_vector

cleanlib:
	@git submodule update --init -q
	@make -f Makefile -C libft clean
	@make -f Makefile -C c_vector clean

fcleanlib:
	@git submodule update --init -q
	@make -f Makefile -C libft fclean
	@make -f Makefile -C c_vector fclean

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(INC_PATH) $^ $(LKFLAGS)

%.o: %.c
	$(CC) $(LFLAGS) -g -o $@ -c $< $(CFLAGS)

clean: cleanlib
	@rm -rf $(OBJ)

fclean: clean fcleanlib mrproper

re: fclean fcleanlib all

.PHONY: clean mrproper

mrproper: clean
	@rm -rf $(NAME)
