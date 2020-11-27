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

void	ft_ps_check_chunk(t_ps *ps, t_swap *sw)
{
	if (*(sw->nb) != ps->sort2[ps->a->count + ps->b->count - 1] ||
			(ps->a->end && ps->a->end->chunk < 2))
		return ;
	while (sw && sw->next)
	{
//		if (*(sw->next->nb) == sw->s && *(sw->nb) !=
//				ps->sort2[ps->a->count + ps->b->count - 1])
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

void	ft_ps_step_f2(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->end && ps->st->count > 2 && ps->chunk_count > 2)
	{
		if ((ab && *(ps->st->end->nb) > m) || (!ab && *(ps->st->end->nb) < m))
		{
			ft_add_cmd(ps, ab ? "ra\n" : "rb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.1)ps->i: %-3d; ab: %-3c",
					  m, ps->i, ps->st == ps->a ? 'a' : 'b');
		}
		else
		{
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.2)ps->i: %-3d; ab: %-3c",
					  m, ps->i, ps->st == ps->a ? 'a' : 'b');
		}
	}
}

void	ft_ps_step_f(t_ps *ps, int m, int ab)
{
		while (ps->i && ps->st->end && ps->st->count > 2 && ps->chunk_count > 2 && ((ab && *(ps->st->end->nb) < m) || (!ab && *(ps->st->end->nb) > m)))
		{
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.1)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		}
		while (ps->i && ps->st->start && ps->st->count > 2 && ps->chunk_count > 2 && ((ab && *(ps->st->start->nb) < m) || (!ab && *(ps->st->start->nb) > m)))
		{
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.2)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		}
}

void	ft_ps_swap_ab2(t_ps *ps, int m)
{
	ps->st = ps->b;
	while (!ft_lst_issorted(ps))
	{
		ft_ps_check_chunk(ps, ps->a->start);
		m = ft_ps_get_med(ps, 2);
		ps->i = (ps->i + 1) / 2;
		ft_ps_step_f(ps, m, ps->st == ps->a);
//		ps->st = ps->st == ps->a ? ps->b : ps->a;
	}
}

void	ft_ps_swap_ab(t_ps *ps, int m)
{
	while (ps->a->count > 2)
	{
		ft_ps_check_chunk(ps, ps->a->start);
		m = ft_ps_get_med(ps, 2);
		ps->i = (ps->i + 1) / 2;
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ft_ps_chunk_count(ps->st->end, ps->sort, 0);
//		ps->st = ps->st == ps->a ? ps->b : ps->a;
	}
//	ft_ps_swap_ab2(ps, m);
}

int				ft_push_swap(t_ps *ps, int m, int s)
{
	ps->s *= s;
	++ps->chunk;
	ft_ps_swap_ab(ps, 0);

	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана: %-3d; (f1.2)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');

	GOTOXY(54, 37);
	return (0);
}
