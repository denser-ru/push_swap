/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_swaps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:30:47 by cayako            #+#    #+#             */
/*   Updated: 2020/11/09 15:27:55 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_swap		*ft_lstsw_new(int *nb)
{
	t_swap	*sw;

	sw = (t_swap*)malloc(sizeof(t_swap));
	ft_bzero(sw, sizeof(t_swap));
	sw->nb = nb;
	sw->chunk = 1;
	return (sw);
}

t_swap		*ft_lstsw_add(t_swap *prev, int *nb)
{
	t_swap	*sw;

	sw = (t_swap*)malloc(sizeof(t_swap));
	ft_bzero(sw, sizeof(t_swap));
	prev->next = sw;
	sw->prev = prev;
	sw->nb = nb;
	sw->chunk = 1;
	return (sw);
}

void		ft_ps_swaps_split(t_ps *ps)
{
	ps->a->end->next = ps->b->start;
	ps->b->start->prev = ps->a->end;
	ps->a->end = ps->b->end;
	ps->b->start = NULL;
	ps->b->end = NULL;
}
