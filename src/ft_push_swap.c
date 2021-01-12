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

int 			ft_ps_get_med(t_ps *ps, int d)
{
	return (ft_ps_sw_sort(ps, ps->st->end, d, ps->sort));
}

int 			ft_ps_chunk_count_up(t_swap *sw, int *sort, int i)
{
	while (sw && sw->chunk)
	{
		sort[i] = *(sw->nb);
		sw = sw->prev;
		++i;
		if (sw && sw->next->chunk != sw->chunk)
			break ;
	}
	return (i);
}

void 	ft_ps_dev(t_ps *ps, int m, char *dev)
{

	GOTOXY(44, 30);
	SET_DISP_2ATR(F_WHITE, B_BLACK);
	ft_printf("\e[38;5;251mмедиана: %-3d; (%s)ps->i: %-3d; ab: %-3c", m, dev, ps->i, ps->st == ps->a ? 'a' : 'b');
	GOTOXY(54, F_HEIGHT + 3);
	usleep(ps->s);
}

void	ft_ps_check_chunk(t_ps *ps, t_swap *sw, int m, char *dev)
{
	if (FT_DEV)
		ft_ps_dev(ps, m, dev);
	if (*(sw->nb) != ps->sort2[ps->a->count + ps->b->count - 1])
		return ;
	while (sw && sw->next)
	{
		if (*(sw->next->nb) == sw->s)
		{
			sw->chunk = 0;
			sw->next->chunk = 0;
		}
		else
			return ;
		sw = sw->next;
	}
}

void 	ft_ps_check_duble(t_ps *ps)
{
	int		chunk;

	if (ps->a->end && ps->a->end->prev && ps->a->end->s == *(ps->a->end->prev->nb))
	{
		chunk = ps->a->end->prev->chunk;
		ps->a->end->prev->chunk = ps->a->end->chunk;
		ps->a->end->chunk = chunk;
		ft_add_cmd(ps, "sa\n");
		ft_put_cmd(ps, ps->cmds, 0, 255);
	}
	if (ps->b->end && ps->b->end->prev && ps->b->end->l == *(ps->b->end->prev->nb) && ps->b->end->prev->chunk == ps->b->end->chunk)
	{
		chunk = ps->b->end->prev->chunk;
		ps->b->end->prev->chunk = ps->b->end->chunk;
		ps->b->end->chunk = chunk;
		ft_add_cmd(ps, "sb\n");
		ft_put_cmd(ps, ps->cmds, 0, 255);
	}
}

void	ft_ps_step_f(t_ps *ps, int m, int ab)
{
		while (ps->i && ps->st->end && ps->st->end->chunk && ps->st->end->chunk == ps->cur_chunk &&
			((ab && ps->st->count > 2 && *(ps->st->end->nb) < m) || (!ab && *(ps->st->end->nb) > m)) && ((ab && ps->chunk_count > 1) || !ab))
		{
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start, m, "f1.1");
			ps->st->end->chunk = ab ? ps->chunk : 1;
			if (!ps->st->end->chunk)
				break ;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start, m, "f1.1");
			ft_put_cmd(ps, ps->cmds, 0, 255);
		}
		while (ps->i && ps->st->start && ps->st->start->chunk && ps->st->start->chunk == ps->cur_chunk && ps->st->count > 1 && ((ab && *(ps->st->start->nb) < m) || (!ab && *(ps->st->start->nb) >= m)))
		{
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start, m, "f1.2");
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 0, 255);
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start, m, "f1.2");
			ft_put_cmd(ps, ps->cmds, 0, 255);
		}
}


void	ft_ps_step_f2(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->end && ps->st->end->chunk && ps->st->end->chunk == ps->cur_chunk && ((ab && ps->chunk_count > 2) || !ab))
	{
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f2.1");
		if (((ab && *(ps->st->end->nb) >= m) || (!ab && *(ps->st->end->nb) <= m)) && ps->st->count > 1 && ps->chunk_count > 1)
		{
			ft_add_cmd(ps, ab ? "ra\n" : "rb\n");
			ft_put_cmd(ps, ps->cmds, 0, 255);
		}
		else if (ps->st->end->chunk && (!ab || (ab && ps->st->count > 1 && ps->chunk_count > 1)))
		{
			ft_ps_check_chunk(ps, ps->a->start, m, "f2.2");
			ft_ps_check_duble(ps);
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start, m, "f2.2");
			ft_put_cmd(ps, ps->cmds, 0, 255);
		}
	}
}

void	ft_ps_step_f3(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->start && ((ab && ps->st->start->chunk && *(ps->st->end->nb) >= m &&
		ps->a->count > 2) || (!ab && ps->b->start->chunk >= ps->b->end->chunk)))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f3.1");
		if ((ab && ps->chunk_count < 3) || (ab && *(ps->a->start->nb) > m) || (!ab && *(ps->b->start->nb) <= m))
		{
			if (!ps->st->start->chunk)
				break ;
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 0, 255);
		}
		else if (ps->st->start->chunk)
		{
			ft_ps_check_chunk(ps, ps->a->start, m, "f3.2");
			if (!ps->st->start->chunk)
				break ;
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 0, 255);
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 0, 255);
		}
	}
}

void	ft_ps_swap_ab2(t_ps *ps, int m)
{
	ps->st = ps->b;
	while (!ft_lst_issorted(ps))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f2.0");
		m = ft_ps_get_med(ps, 2);
		++ps->chunk;
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_check_duble(ps);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		if (ps->st->count && (ps->st->start->chunk > ps->st->end->chunk || ps->st->start->chunk == 1))
		{
			ft_ps_check_duble(ps);
			ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
			ft_ps_step_f3(ps, m, ps->st == ps->a);
		}
		if ((ps->st == ps->a && ps->chunk_count < 3 && !ps->a->start->chunk) ||
			(ps->st == ps->b && (ps->chunk_count > 2) && ft_ps_chunk_count(ps->st->end, ps->sort, ps->cur_chunk, 0)) ||
			(ps->st == ps->b && !ps->chunk_count))
		{
			ps->st = ps->st == ps->a ? ps->b : ps->a;
		}
		ps->chunk_count = ps->st->end ? ft_ps_chunk_count(ps->st->end, ps->sort, ps->st->end->chunk, 0) : 0;
	}
}

void	ft_ps_swap_ab(t_ps *ps, int m)
{
	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
	while (ps->a->count > 2 && (ps->st->end->chunk || ps->st->start->chunk))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f1.0");
		if (*(ps->a->end->nb) == m && ps->i == 1)
			break ;
		m = ft_ps_get_med(ps, 2);
		++ps->chunk;
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ft_ps_check_duble(ps);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f3(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count(ps->st->end, ps->sort, ps->st->end->chunk, 0);
	}
	ps->st = ps->b;
	ft_ps_swap_ab2(ps, m);
}

int				ft_push_swap(t_ps *ps, int s)
{
	ps->s *= s;
	++ps->chunk;
	ft_ps_swap_ab(ps, 0);
	GOTOXY(54, F_HEIGHT + 3);
	ft_putchar('\n');
	return (0);
}
