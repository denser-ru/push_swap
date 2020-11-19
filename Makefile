# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/21 22:11:50 by cayako            #+#    #+#              #
#    Updated: 2020/11/16 12:33:11 by cayako           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR  = ./src/
INCDIR  = ./inc/
OBJDIR  = ./obj/
FTDIR   = ./libft/
PRNTDIR  = ./ft_printf/
INCL		= $(wildcard $(INCDIR)*.h)

SRC = main.c ft_lst_swaps.c  ft_mem_u.c ft_frame.c ft_read_in.c ft_print_bg.c \
        ft_ps_utils.c ft_ps_ss.c ft_ps_p.c ft_ps_rr.c \
		ft_ps_sort.c ft_ps_chunk.c testsort2.c

#ft_push_swap.c \

OBJ	= $(addprefix $(OBJDIR),$(SRC:.c=.o))
LIBFT = $(FTDIR)libft.a
LIBPRNT = $(PRNTDIR)libftprintf.a

.PHONY: all clean fclean count

all: $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCL) | obj
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(FTDIR) -I $(PRNTDIR)inc/ -o $@ -c $<

$(LIBFT):
	make -C $(FTDIR)

$(LIBPRNT):
	make -C $(PRNTDIR)

$(NAME): $(LIBFT) $(LIBPRNT) $(OBJ)
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
