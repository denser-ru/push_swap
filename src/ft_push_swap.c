/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/12/04 18:57:41 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			ft_ps_check_duble(t_ps *ps)
{
	int		chunk;

	if (ps->a->end && ps->a->end->prev && ps->a->end->s ==
		*(ps->a->end->prev->nb))
	{
		chunk = ps->a->end->prev->chunk;
		ps->a->end->prev->chunk = ps->a->end->chunk;
		ps->a->end->chunk = chunk;
		ft_add_cmd(ps, "sa\n");
		ft_put_cmd(ps, ps->cmds, 0, 255);
	}
	if (ps->b->end && ps->b->end->prev && ps->b->end->l ==
		*(ps->b->end->prev->nb) && ps->b->end->prev->chunk == ps->b->end->chunk)
	{
		chunk = ps->b->end->prev->chunk;
		ps->b->end->prev->chunk = ps->b->end->chunk;
		ps->b->end->chunk = chunk;
		ft_add_cmd(ps, "sb\n");
		ft_put_cmd(ps, ps->cmds, 0, 255);
	}
}

static void		ft_ps_swap_ab2_check(t_ps *ps, int m)
{
	if (ps->st->count && (ps->st->start->chunk > ps->st->end->chunk ||
		ps->st->start->chunk == 1))
	{
		ft_ps_check_duble(ps);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f3(ps, m, ps->st == ps->a);
	}
	if ((ps->st == ps->a && ps->chunk_count < 3 && !ps->a->start->chunk) ||
		(ps->st == ps->b && (ps->chunk_count > 2) &&
		ft_ps_chunk_count(ps->st->end, ps->sort, ps->cur_chunk, 0)) ||
		(ps->st == ps->b && !ps->chunk_count))
	{
		ps->st = ps->st == ps->a ? ps->b : ps->a;
	}
}

void			ft_ps_swap_ab2(t_ps *ps, int m)
{
	ps->st = ps->b;
	while (!ft_lst_issorted(ps))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f2.0");
		m = ft_ps_sw_sort(ps, ps->st->end, 2, ps->sort);
		++ps->chunk;
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_check_duble(ps);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_swap_ab2_check(ps, m);
		ps->chunk_count = ps->st->end ? ft_ps_chunk_count(ps->st->end, ps->sort,
			ps->st->end->chunk, 0) : 0;
	}
}

void			ft_ps_swap_ab(t_ps *ps, int m)
{
	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
	while (ps->a->count > 2 && (ps->st->end->chunk || ps->st->start->chunk))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f1.0");
		if (*(ps->a->end->nb) == m && ps->i == 1)
			break ;
		m = ft_ps_sw_sort(ps, ps->st->end, 2, ps->sort);
		++ps->chunk;
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ft_ps_check_duble(ps);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f3(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count(ps->st->end, ps->sort,
			ps->st->end->chunk, 0);
	}
	ps->st = ps->b;
	ft_ps_swap_ab2(ps, m);
}

int				ft_push_swap(t_ps *ps, int s)
{
	ps->s = s * 1000;
	++ps->chunk;
	ft_ps_swap_ab(ps, 0);
	GOTOXY(54, F_HEIGHT + 3);
	ft_putchar('\n');
	return (0);
}
