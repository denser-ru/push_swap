/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/11/26 19:00:43 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int 			ft_ps_get_med(t_ps *ps, int d)
{
	ft_ps_sw_sort(ps, ps->st->end, d, ps->sort);
	return (ps->sort[ps->i / 2]);
}

void 	ft_ps_check_2x2(t_ps *ps, t_swap *sw)
{
	if (!sw || !sw->prev || ps->st->count < 4 || sw->chunk != sw->prev->chunk)
		return ;
	sw = sw->prev->prev;
	if (sw->chunk != sw->prev->chunk || sw->next->chunk == sw->chunk ||
			!sw->prev->prev || sw->prev->prev->chunk == sw->chunk)
		return ;
	sw->next->chunk = sw->chunk;
	sw->next->next->chunk = sw->chunk;
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

void	ft_ps_check_chunk2(t_ps *ps, int ab)
{
	t_swap	*sw;

	if (ps->a->count && !ps->a->end->chunk && !ps->a->start->chunk)
	{
		ps->chunk = ps->b->start->chunk;
		sw = ps->b->start;
		while (sw)
		{
			sw->chunk = ps->chunk;
			sw = sw->next;
		}
	}
	if (ab && ps->a->count > 2 && !ps->a->start->chunk && ps->a->end->chunk && ft_ps_chunk_count_up(ps->st->end, ps->sort, 0) < 3 && !ps->a->end->prev->prev->chunk && ps->b->end)
	{
//		ab = ps->b->end->prev && ps->b->end->chunk == ps->b->end->prev->chunk ?
//			 ps->b->end->chunk : ps->b->end->prev->chunk;
//		ps->b->end->chunk = ab;
		if (ps->a->end->prev->chunk)
		{
//			ps->a->end->chunk = ab;
			ft_add_cmd(ps, "pb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
//			ps->a->end->chunk = ab;
			ft_add_cmd(ps, "pb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
		}
		else
		{
//			ps->a->end->chunk = ab;
			ft_add_cmd(ps, "pb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
		}
	}
}

void	ft_ps_check_chunk(t_ps *ps, t_swap *sw)
{
//	ft_ps_check_2x2(ps, ps->st->end);
	ft_ps_check_chunk2(ps, ps->st == ps->a);
	if (*(sw->nb) != ps->sort2[ps->a->count + ps->b->count - 1] ||
			(ps->a->end && ps->a->end->chunk < 2))
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

void 	ft_ps_check_tail(t_ps *ps, int ab)
{
	if (!ab && ps->b->count == 2 && ps->b->end->s == *(ps->b->end->prev->nb))
	{
		ps->a->end->chunk = ps->b->end->chunk;
		ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
		ps->a->end->chunk = ps->b->end->chunk;
		ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
		ft_lst_issorted(ps);
	}
	ft_ps_check_chunk(ps, ps->a->start);
	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
	if (ab && ps->a->end->chunk != ps->a->start->chunk && ps->chunk_count == 1)
	{
		ps->a->end->chunk = ps->b->end->chunk;
		ft_add_cmd(ps, "pb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
}

void 	ft_ps_check_duble(t_ps *ps)
{
	if (ps->a->end && ps->a->end->prev && ps->a->end->s == *(ps->a->end->prev->nb) && ps->a->end->prev->chunk == ps->a->end->chunk)
	{
		ft_add_cmd(ps, "sa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
	if (ps->b->end && ps->b->end->prev && ps->b->end->l == *(ps->b->end->prev->nb) && ps->b->end->prev->chunk == ps->b->end->chunk)
	{
		ft_add_cmd(ps, "sb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
	ft_ps_check_tail(ps, ps->st == ps->a);
}

void	ft_ps_step_f2(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->end && ps->st->end->chunk && ((ab && ps->st->count > 2) || !ab))
	{
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start);
		if ((ab && *(ps->st->end->nb) > m) || (!ab && *(ps->st->end->nb) < m))
		{
			if (!ps->st->end->chunk)
				break ;
			ft_add_cmd(ps, ab ? "ra\n" : "rb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2.1)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
		else if (ps->st->end->chunk)
		{
			ft_ps_check_chunk(ps, ps->a->start);
			if (!ps->st->end->chunk)
				break ;
			ps->st->end->chunk = ps->chunk;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2.2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
		if (ps->chunk_count < 2)
			break ;
	}
}

void	ft_ps_step_f(t_ps *ps, int m, int ab)
{
		while (ps->i && ps->st->end && ps->st->end->chunk && ((ab && ps->st->count > 2 && *(ps->st->end->nb) < m) || (!ab && *(ps->st->end->nb) > m)))
		{
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start);
			ps->st->end->chunk = ps->chunk;
			if (!ps->st->end->chunk)
				break ;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.1)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
			ft_ps_check_chunk(ps, ps->a->start);
		}
		while (ps->i && ps->st->start && ps->st->end->chunk && ps->st->count > 2 && ((ab && *(ps->st->start->nb) < m) || (!ab && *(ps->st->start->nb) > m)))
		{
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start);
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			ps->st->end->chunk = ps->chunk;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
}

void	ft_ps_step_f3(t_ps *ps)
{
	while (ps->a->start && ps->a->start->chunk)
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start);
		ft_add_cmd(ps, "rra\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
		ft_ps_check_tail(ps, ps->st == ps->a);
	}
}

void	ft_ps_swap_ab2(t_ps *ps, int m)
{
	ps->st = ps->b;
	while (!ft_lst_issorted(ps))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start);
		m = ft_ps_get_med(ps, 2);
		ps->i = (ps->i + 1) / 2;
		++ps->chunk;
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		if (ps->st == ps->a && !ps->a->end->chunk && ps->a->start->chunk)
			ft_ps_step_f3(ps);
		ps->st = ps->st == ps->a ? ps->b : ps->a;
		ps->chunk_count = ft_ps_chunk_count(ps->st->end, ps->sort, ps->st->end->chunk, 0);
	}
}

void	ft_ps_swap_ab(t_ps *ps, int m)
{
	while (ps->a->count > 2)
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start);
		m = ft_ps_get_med(ps, 2);
		ps->i = (ps->i + 1) / 2;
		++ps->chunk;
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f1)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count(ps->st->end, ps->sort, ps->st->end->chunk, 0);
//		ps->st = ps->st == ps->a ? ps->b : ps->a;
	}
	ft_ps_swap_ab2(ps, m);
}

int				ft_push_swap(t_ps *ps, int m, int s)
{
	ps->s *= s;
	++ps->chunk;
	ft_ps_swap_ab(ps, 0);

	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана: %-3d; (f0)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');

	GOTOXY(54, 37);
	return (0);
}
