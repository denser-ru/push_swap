/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/11/25 16:38:19 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int 			ft_ps_get_med(t_ps *ps, int d)
{
	ft_ps_sw_sort(ps, ps->st->end, d, ps->sort);
	return (ps->sort[ps->i / 2]);
}

void	ft_ps_check_chunk(t_ps *ps, t_swap *sw)
{
	if (*(sw->nb) != ps->sort2[ps->a->count + ps->b->count - 1])
		return ;
	while (sw && sw->next)
	{
		if (*(sw->next->nb) == sw->s)
			sw->chunk = 0;
		else
			return ;
		sw = sw->next;
	}
}

int			ft_check_duble(t_ps *ps, t_stack *st, t_swap *sw, int i)
{
	if (!st->end || !st->end->prev)
		return (0);
	while (sw)
	{
		sw = sw->prev;
		++i;
		if (i > 2 || (sw && sw->next->chunk != sw->chunk))
			break ;
	}
	if (i > 2)
		return (0);
	if ((ps->st == ps->a && (*(st->end->nb) > *(st->end->prev->nb))) ||
			((ps->st == ps->b) && (*(st->end->nb) < *(st->end->prev->nb))))
	{
		ft_add_cmd(ps, ps->st == ps->a ? "sa\n" : "sb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
	ft_lst_issorted(ps);
	return (1);
}

static void		ft_ps_step_f2(t_ps *ps, int m, int ab)
{
	while (ps->st->end && ps->i > 0 && ((!ab && ps->b->count) || (ab && (ps->st->count > 2))))
	{
		ft_check_duble(ps, ps->st, ps->st->end, 0);
		if ((ab && (*(ps->st->end->nb) < m)) || (!ab && *(ps->st->end->nb)) > m || ps->i == 1)
		{
			ps->st->end->chunk = ps->chunk;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2.1)ps->i: %-3d; ab: %-3c", m, ps->i, ab ? 'a' : 'b');
			usleep(ps->s);
		}
		else if (((!ab && *(ps->st->end->nb) > m) || (ab && (ps->st->count > 2) && ps->st->end->chunk)) && ps->i > 0)
		{
			ps->st->end->chunk = ab ? ps->st->end->chunk : ps->chunk;
			ft_add_cmd(ps, ab ? "ra\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2.2)ps->i: %-3d; ab: %-3c", m, ps->i, ab ? 'a' : 'b');
			usleep(ps->s);
		}
		else if ((!ab && *(ps->st->end->nb) <= m) && ps->i > 0)
		{
			ft_add_cmd(ps, "rb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2.2)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
		ft_check_duble(ps, ps->st, ps->st->end, 0);
	}
}

static void		ft_ps_step_f(t_ps *ps, int m, int ab)
{
	++ps->chunk;
	while ((ab && ps->st->end && ps->i > 0 && (ab && (ps->st->count > 2))
		&& *(ps->st->end->nb) < m) ||
			(!ab && ps->st->end && ps->i > 0 && *(ps->st->end->nb) > m))
	{
		ft_check_duble(ps, ps->st, ps->st->end, 0);
		ps->st->end->chunk = ps->chunk;
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f1.1)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		usleep(ps->s);
	}
	while (ps->st->start && ps->i > 0 && ((ab && ps->st->count > 2 && (*(ps->st->start->nb) < m) && ps->st->end->chunk) || (!ab && *(ps->st->start->nb) > m)))
	{
		ft_check_duble(ps, ps->st, ps->st->end, 0);
		ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
//		ps->st->end->chunk = ab ? ps->chunk : 1;
		ps->st->end->chunk = ps->chunk;
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f1.2)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		usleep(ps->s);
	}
	ft_ps_step_f2(ps, m, ab);
}

void	ft_ps_swap_ab(t_ps *ps, int m)
{
	while (1)
	{
		ft_ps_check_chunk(ps, ps->a->start);
		m = ft_ps_get_med(ps, 2);
		ft_check_duble(ps, ps->st, ps->st->end, 0);
		ps->i = (ps->i + 1) / 2;
		ft_ps_step_f(ps, m, ps->st == ps->a);
		if ((ps->st == ps->a && ps->a->count < 3) ||
			(!(ps->st == ps->a) && !ps->b->count) ||
			(ps->st->end && !ps->st->end->chunk))
			ps->st = ps->st == ps->a ? ps->b : ps->a;
	}
}

int				ft_push_swap(t_ps *ps, int m, int s)
{
	ps->s *= s;
	++ps->chunk;
	ft_ps_swap_ab(ps, 0);

	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');

	GOTOXY(54, 37);
	return (0);
}
