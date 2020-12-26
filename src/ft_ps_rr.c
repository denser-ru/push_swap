/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_rr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:14:39 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:49:57 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ps_ra(t_ps *ps)
{
	t_swap	*end;

	if (!ps->a->end || !ps->a->start || ps->a->start == ps->a->end)
		return ;
	end = ps->a->end->prev;
	end->next = NULL;
	ps->a->end->next = ps->a->start;
	ps->a->end->prev = NULL;
	ps->a->start->prev = ps->a->end;
	ps->a->end = end;
	ps->a->start = ps->a->start->prev;
	if (FT_DEV || (ps->gui && ps->fix))
		ft_print_sw(ps->a->start, 'a');
}

void	ft_ps_rb(t_ps *ps)
{
	t_swap	*end;

	if (!ps->b->end || !ps->b->start || ps->b->start == ps->b->end)
		return ;
	end = ps->b->end->prev;
	end->next = NULL;
	ps->b->end->next = ps->b->start;
	ps->b->end->prev = NULL;
	ps->b->start->prev = ps->b->end;
	ps->b->end = end;
	ps->b->start = ps->b->start->prev;
	if (FT_DEV || (ps->gui && ps->fix))
		ft_print_sw(ps->b->start, 'b');
}

void	ft_ps_rra(t_ps *ps)
{
	t_swap	*start;

	if (!ps->a->end || !ps->a->start || ps->a->start == ps->a->end)
		return ;
	if (!(start = ps->a->start->next))
		return ;
	start->prev = NULL;
	ps->a->start->prev = ps->a->end;
	ps->a->start->next = NULL;
	ps->a->end->next = ps->a->start;
	ps->a->start = start;
	ps->a->end = ps->a->end->next;
	if (FT_DEV || (ps->gui && ps->fix))
		ft_print_sw(ps->a->start, 'a');
}

void	ft_ps_rrb(t_ps *ps)
{
	t_swap	*start;

	if (!ps->b->end || !ps->b->start || ps->b->start == ps->b->end)
		return ;
	start = ps->b->start->next;
	start->prev = NULL;
	ps->b->start->prev = ps->b->end;
	ps->b->start->next = NULL;
	ps->b->end->next = ps->b->start;
	ps->b->start = start;
	ps->b->end = ps->b->end->next;
	if (FT_DEV || (ps->gui && ps->fix))
		ft_print_sw(ps->b->start, 'b');
}

void	ft_ps_rrr(t_ps *ps)
{
	ft_ps_rra(ps);
	ft_ps_rrb(ps);
}
