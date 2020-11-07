# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/21 22:11:50 by cayako            #+#    #+#              #
#    Updated: 2020/11/06 02:54:00 by cayako           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRCDIR  = ./src/
INCDIR  = ./inc/
OBJDIR  = ./obj/
FTDIR   = ./libft/
PRNTDIR  = ./ft_printf/

SRC = main.c ft_lst_swaps.c  ft_mem_u.c ft_frame.c ft_read_in.c ft_print_bg.c \
        ft_ps_utils.c
OBJ	= $(addprefix $(OBJDIR),$(SRC:.c=.o))
LIBFT = $(FTDIR)libft.a
LIBPRNT = $(PRNTDIR)libftprintf.a

.PHONY: all clean fclean count

all: $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(FTDIR) -I $(PRNTDIR)inc/ -o $@ -c $<

$(LIBFT):
	make -C $(FTDIR)

$(LIBPRNT):
	make -C $(PRNTDIR)

$(NAME): obj $(LIBFT) $(LIBPRNT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(LIBPRNT) -o $(NAME)

count:
	wc ./src/*.c ./inc/*.h

clean:
	rm -rf $(OBJDIR)
	make -sC $(FTDIR) clean
	make -sC $(PRNTDIR) clean

fclean: clean
	rm -f $(NAME)
	make -sC $(FTDIR) fclean
	make -sC $(PRNTDIR) fclean

re: fclean all
