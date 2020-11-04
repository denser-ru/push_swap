//
// Created by Cheyenne Ayako on 11/4/20.
//

#include "push_swap.h"

t_swap		*ft_lstsw_new(t_ps *ps, int *nb)
{
	t_swap	*sw;

	sw = (t_swap*)malloc(sizeof(t_swap));
	sw->nb = nb;
	sw->chunk = 1;
	sw->next = NULL;
	return (sw);
}

t_swap		*ft_lstsw_add(t_ps *ps, t_swap *prev, int *nb)
{
	t_swap	*sw;

	sw = (t_swap*)malloc(sizeof(t_swap));
	prev->next = sw;
	sw->nb = nb;
	sw->chunk = 1;
	return (sw);
}