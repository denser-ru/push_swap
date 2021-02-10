# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/18 18:55:17 by cayako            #+#    #+#              #
#    Updated: 2020/10/18 18:55:25 by cayako           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
NAMETEST = ft_printf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -O3 -march=native

SRCDIR  = ./src/
INCDIR  = ./inc/
OBJDIR  = ./obj/
FTDIR   = ./libft/

SRC = ft_printf.c ft_parsing.c ft_putarg.c ft_pf_utils.c ft_put_digit.c \
		ft_put_src.c ft_put_oxup.c ft_put_f.c
FTSRC = ft_putchar.c ft_putstr.c ft_bzero.c ft_putnstr.c ft_strchr.c ft_atoi.c \
		ft_memchr.c ft_putnbr.c ft_strlen.c ft_memset.c ft_iswhitespace.c \
		ft_isdigit.c

OBJ	= $(addprefix $(OBJDIR),$(SRC:.c=.o))
FTOBJ	= $(addprefix $(FTDIR),$(FTSRC:.c=.o))
LIBFT = $(FTDIR)libft.a

all: $(NAME)

obj:
	mkdir -p $(OBJDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -I $(FTDIR) -o $@ -c $<

$(LIBFT):
	@make -C $(FTDIR)

$(NAME): obj $(LIBFT) $(OBJ) $(FTOBJ)
	ar rc $(NAME) $(OBJ) $(FTOBJ)
	ranlib $(NAME)

count:
	wc ./src/*.c ./inc/*.h

clean:
	make -C $(FTDIR) clean
	rm -f $(OBJDIR)*.o

fclean: clean
	@rm -f $(NAMETEST)
	@make -C $(FTDIR) fclean
	rm -f $(NAME)

re: fclean all

test: $(OBJDIR)main.o $(SRCDIR)main.c $(NAME)
	@$(CC) $(SRCDIR)main.c $(NAME) -I $(INCDIR) -I $(FTDIR) -o $(NAMETEST)

.PHONY: all clean fclean count
