//
// Created by Cheyenne Ayako on 11/3/20.
//

#ifndef PUSH_SWAP_PUSH_SWAP_H
# define PUSH_SWAP_PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"

typedef struct		s_swap
{
	int 			*nb;
	int 			chunk;
	struct s_swap	*next;
}					t_swap;

typedef struct 		s_ps
{
	int 			*nb;
	t_swap			*a;
	t_swap			*b;
	t_swap			*c;
	int 			chunk;
}					t_ps;

t_swap				*ft_lstsw_new(t_ps *ps, int *nb);
t_swap				*ft_lstsw_add(t_ps *ps, t_swap *prev, int *nb);

#endif
