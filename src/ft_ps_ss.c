/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_ss.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:14:50 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:44:04 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ps_sa(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if (!ps->a->end || !ps->a->end->prev)
		return ;
	c = ps->a->end;
	prev = ps->a->end->prev->prev;
	ps->a->end = ps->a->end->prev;
	ps->a->end->prev = c;
	ps->a->end->next = NULL;
	c->prev = prev;
	if (prev)
		prev->next = c;
	else
		ps->a->start = c;
	c->next = ps->a->end;
	if (FT_DEV)
		ft_print_sw(ps->a->start, 'a');
}

void	ft_ps_sb(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if (!ps->b->end || !ps->b->end->prev)
		return ;
	c = ps->b->end;
	prev = ps->b->end->prev->prev;
	ps->b->end = ps->b->end->prev;
	ps->b->end->prev = c;
	ps->b->end->next = NULL;
	c->prev = prev;
	if (prev)
		prev->next = c;
	else
		ps->b->start = c;
	c->next = ps->b->end;
	if (FT_DEV)
		ft_print_sw(ps->b->start, 'b');
}

void	ft_ps_ss(t_ps *ps)
{
	ft_ps_sa(ps);
	ft_ps_sb(ps);
}

void	ft_ps_rr(t_ps *ps)
{
	ft_ps_ra(ps);
	ft_ps_rb(ps);
}
