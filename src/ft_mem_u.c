//
// Created by Cheyenne Ayako on 11/4/20.
//

#include "push_swap.h"

static void		ft_lst_swaps_del(t_swap *sw)
{
	if (sw->next)
		ft_lst_swaps_del(sw->next);
	free(sw);
	sw = NULL;
}

void	ft_memfree(t_ps *ps)
{
	ft_lst_swaps_del(ps->a);
}