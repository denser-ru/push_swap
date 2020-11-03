# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/21 22:11:50 by cayako            #+#    #+#              #
#    Updated: 2020/11/03 18:11:27 by cayako           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCDIR  = ./src/
INCDIR  = ./inc/
OBJDIR  = ./obj/
FTDIR   = ./libft/

SRC = main.c
OBJ	= $(addprefix $(OBJDIR),$(SRC:.c=.o))
LIBFT = $(FTDIR)libft.a

.PHONY: all clean fclean count

all: $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(FTDIR) -o $@ -c $<

$(LIBFT):
	make -C $(FTDIR)

$(NAME): obj $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME)

count:
	wc ./src/*.c ./inc/*.h

clean:
	rm -rf $(OBJDIR)
	make -sC $(FTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -sC $(FTDIR) fclean

re: fclean all
