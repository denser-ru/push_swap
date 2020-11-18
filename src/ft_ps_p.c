/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:14:24 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:47:39 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	ft_ps_count(t_ps *ps, int a, int b)
{
	--ps->i;
	ps->a->count += a;
	ps->b->count += b;
	ft_print_sw(ps->b->start, 'b');
	ft_print_sw(ps->a->start, 'a');
}

void			ft_ps_pa(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if (!ps->b->end)
		return ;
	c = ps->a->end;
	if ((prev = ps->b->end->prev))
		prev->next = NULL;
	ps->a->end = ps->b->end;
	ps->b->end = prev ? prev : NULL;
	ps->b->start = ps->b->end ? ps->b->start : NULL;
	if (c && (ps->a->end->prev = c))
		c->next = ps->a->end;
	else if (!c)
	{
		ps->a->start = ps->a->end;
		ps->a->start->prev = NULL;
	}
	if (ps->a->end)
		ps->a->end->next = NULL;
	if (!ps->b->start)
		ft_clear_line(102, 32, F_WHITE, B_BLUE);
	ft_ps_count(ps, 1, -1);
	ft_ps_check_chunk_sort(ps);
}

void			ft_ps_pb(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if (!ps->a->end)
		return ;
	c = ps->b->end;
	if ((prev = ps->a->end->prev))
		prev->next = NULL;
	ps->b->end = ps->a->end;
	ps->a->end = prev ? prev : NULL;
	ps->a->start = ps->a->end ? ps->a->start : NULL;
	if (c && (ps->b->end->prev = c))
		c->next = ps->b->end;
	else if (!c)
	{
		ps->b->start = ps->b->end;
		ps->b->start->prev = NULL;
	}
	if (ps->b->end)
		ps->b->end->next = NULL;
	if (!ps->a->start)
		ft_clear_line(7, 32, F_WHITE, B_RED);
	ft_ps_count(ps, -1, 1);
}
