/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 19:22:13 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int 			ft_ps_get_med(t_ps *ps, int d)
{
	ft_ps_sw_sort(ps, ps->st->end, d, ps->sort);
	return (ps->sort[ps->i / 2]);
}

void			ft_check_duble(t_ps *ps, t_stack *st, t_swap *sw, int i)
{
	if (!st->end || !st->end->prev)
		return ;
	while (sw)
	{
		sw = sw->prev;
		++i;
		if (i > 2 && sw && sw->next->chunk != sw->chunk)
			return ;
	}
	if (i == 1 && ((ps->st == ps->a) * (*(st->end->nb) > *(st->end->nb)) ||
			(ps->st == ps->b) * (*(st->end->nb) < *(st->end->nb))))
	{
		ft_add_cmd(ps, ps->st == ps->a ? "sa\n" : "sb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
//	ft_lst_issorted(ps);
}

int			ft_ps_step_check_end(t_ps *ps, int i, int ab)
{
	if (i < 2)
	{
		sleep(1);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", -1, ps->i, ab ? 'a' : 'b');
//		if (ps->st->end)
//			ps->st->end->chunk = 0;
		if (!ab)
			ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		sleep(1);
		return (1);
	}
	if (i == 2)
	{
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", -2, ps->i, ab ? 'a' : 'b');
		sleep(1);
		if (ps->st->end && ps->st->end->prev &&
			(((ab && *(ps->st->end->nb) > *(ps->st->end->prev->nb)) ||
			  (!ab && *(ps->st->end->nb) < *(ps->st->end->prev->nb)))))
		{
//			ps->st->end->chunk = 0;
			ft_add_cmd(ps, ab ? "sa\n" : "sb\n");
//			ps->st->end->chunk = 0;
			ft_put_cmd(ps, ps->cmds, 1, 255);
			sleep(1);
		}
		return (1);
	}
	return (0);
}

static void		ft_ps_step_f2(t_ps *ps, int m, int ab)
{
	while (ps->st->end && ps->i > 0 && (!ab * ps->b->count || ab * (ps->st->count > 2)))
	{
		ft_check_duble(ps, ps->st, ps->st->end, 0);
		if (ab * (*(ps->st->end->nb) < m) || !ab * (*(ps->st->end->nb) > m || ps->i == 1))
		{
			ps->st->end->chunk = ps->chunk;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ab ? 'a' : 'b');
			usleep(ps->s);
		}
		else if ((((!ab && *(ps->st->end->nb) > m)) || (ab * (ps->st->count > 2) && ps->st->end->chunk)) && ps->i > 0)
		{
			ps->st->end->chunk = ab ? ps->st->end->chunk : ps->chunk;
			ft_add_cmd(ps, ab ? "ra\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2)ps->i: %-3d; ab: %-3c", m, ps->i, ab ? 'a' : 'b');
			usleep(ps->s);
		}
		else if ((!ab && *(ps->st->end->nb) < m) && ps->i > 0)
		{
			ft_add_cmd(ps, "rb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
	}
}

static void		ft_ps_step_f(t_ps *ps, int m, int ab)
{
	++ps->chunk;
	while (ab * (ps->st->end && ps->i > 0 && (ab * (ps->st->count > 2))
		&& *(ps->st->end->nb) < m) ||
			!ab * (ps->st->end && ps->i > 0 && *(ps->st->end->nb) > m))
	{
		ft_check_duble(ps, ps->st, ps->st->end, 0);
		ps->st->end->chunk = ps->chunk;
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		usleep(ps->s);
	}
	while (ps->st->start && ps->i > 0 && ab * ps->st->count > 2 && ((ab * (*(ps->st->start->nb) < m) && ps->st->end->chunk) || !ab * (*(ps->st->start->nb) > m)))
	{
		ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
		ps->st->end->chunk = ps->chunk;
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		usleep(ps->s);
	}
	ft_ps_step_f2(ps, m, ab);
}


void	ft_ps_swap_ab(t_ps *ps, int m)
{
	while (1)
	{
		ft_check_duble(ps, ps->st, ps->st->end, 0);
		m = ft_ps_get_med(ps, 2);
		if (ft_ps_step_check_end(ps, ps->i, ps->st == ps->a))
			m = ft_ps_get_med(ps, 2);
		ps->i = ++ps->i / 2;
		ft_ps_step_f(ps, m, ps->st == ps->a);
		if ((ps->st == ps->a) * (ps->a->count < 3) || !(ps->st == ps->a) * !ps->b->count)
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
