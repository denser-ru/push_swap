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
CHECKER = checker
CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCDIR  = ./src/
INCDIR  = ./inc/
OBJDIR  = ./obj/
FTDIR   = ./libft/
PRNTDIR  = ./ft_printf/
INCL		= $(wildcard $(INCDIR)*.h)

SRC = ft_ps_init.c ft_lst_swaps.c  ft_mem_u.c ft_frame.c \
        ft_ps_utils.c ft_ps_ss.c ft_ps_p.c ft_ps_rr.c ft_ps_move.c \
		ft_ps_sort.c ft_ps_chunk.c ft_push_swap.c ft_ps_checks.c ft_read_in.c \
		ft_print_bg.c
SRC_PS = push_swap.c
SRC_CH = checker.c

OBJ	= $(addprefix $(OBJDIR),$(SRC:.c=.o))
OBJ_PS = $(addprefix $(OBJDIR),$(SRC_PS:.c=.o))
OBJ_CH = $(addprefix $(OBJDIR),$(SRC_CH:.c=.o))
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

$(NAME): $(LIBFT) $(LIBPRNT) $(OBJ) $(OBJ_PS) $(OBJ_CH)
	$(CC) $(OBJ_PS) $(OBJ) $(LIBFT) $(LIBPRNT) -o $(NAME)
	$(CC) $(OBJ_CH) $(OBJ) $(LIBFT) $(LIBPRNT) -o $(CHECKER)

count:
	wc ./src/*.c ./inc/*.h

clean:
	rm -rf $(OBJDIR)
	make -sC $(FTDIR) clean
	make -sC $(PRNTDIR) clean

fclean: clean
	rm -f $(NAME) $(CHECKER)
	make -sC $(FTDIR) fclean
	make -sC $(PRNTDIR) fclean

re: fclean all
