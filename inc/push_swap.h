//
// Created by Cheyenne Ayako on 11/3/20.
//

#ifndef PUSH_SWAP_PUSH_SWAP_H
# define PUSH_SWAP_PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"

typedef struct		s_swap
{
	int 			*swap;
	int 			chunk;
	struct s_swap	*next;
}					t_swap;

typedef struct 		s_ps
{
	t_swap			*a;
	t_swap			*b;
	t_swap			*c;
}					t_ps;

#endif
