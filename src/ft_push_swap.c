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

int			ft_ps_step_check_end(t_ps *ps, int i, int ab)
{
	if (i < 2)
		return (1);
	if (i == 2)
	{
		if (ps->st->end && ps->st->end->prev &&
			(((ab && *(ps->st->end->nb) > *(ps->st->end->prev->nb)) ||
			  (!ab && *(ps->st->end->nb) < *(ps->st->end->prev->nb)))))
		{
			ft_add_cmd(ps, ab ? "sa\n" : "sb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
		}
		return (1);
	}
	return (0);
}

static void		ft_ps_step_f2(t_ps *ps, int m, int ab)
{
	while (ps->st->end && ps->i > 0 && (!ab || ab * (ps->st->count > 2)))
	{
		if (ab * (*(ps->st->end->nb) < m) || !ab * (*(ps->st->end->nb) >= m))
		{
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
		else if ((((!ab && *(ps->st->end->nb) > m)) || (ab * (ps->st->count > 2) && ps->st->end->chunk)) && ps->i > 0)
		{
			ft_add_cmd(ps, ab ? "ra\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
		else if ((!ab && *(ps->st->end->nb) < m) && ps->i > 0)
		{
			ft_add_cmd(ps, "rb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
	}
}

static void		ft_ps_step_f(t_ps *ps, int m, int ab)
{
	while (ab * (ps->st->end && ps->i > 0 && (!ab || ab * (ps->st->count > 2))
		&& *(ps->st->end->nb) < m) ||
			!ab * (ps->st->end && ps->i > 0 && *(ps->st->end->nb) > m))
	{
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		usleep(ps->s);
	}
	while (ps->st->start && ps->i > 0 && ps->st->count > 2 && ((ab * (*(ps->st->start->nb) < m) && ps->st->end->chunk) || !ab * (*(ps->st->start->nb) > m)))
	{
		ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
		usleep(ps->s);
	}
	ft_ps_step_f2(ps, m, ab);
}

static void		ft_ps_step_b(t_ps *ps, int m, int i, int ab)
{
	ps->i = i;
	if (i < 4)
	{
		if (!ab)
		{
			ps->st->end->chunk = 0;
			ft_add_cmd(ps, "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
		else if (ps->a->count > 2 && ps->st->end->chunk)
		{
			ft_add_cmd(ps, "ra\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
	}
	else
	{
		if (!ab)
		{
			ps->st->end->chunk = 0;
			ft_add_cmd(ps, "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
		else if (ps->a->count > 2 && ps->st->end->chunk)
		{
			ft_add_cmd(ps, "ra\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
		if (!ab)
		{
			ps->st->end->chunk = 0;
			ft_add_cmd(ps, "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
		else if (ps->a->count > 2 && ps->st->end->chunk)
		{
			ft_add_cmd(ps, "ra\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
			usleep(ps->s);
		}
	}
}


void	ft_ps_swap_ab(t_ps *ps, int m, int i, int ab)
{
	ps->i = i;
	if (ft_ps_step_check_end(ps, i, ab))
		return;
	m = ft_ps_get_med(ps, 2);
	ps->i = i / 2;
//	!ps->isread ? ft_ps_step_f(ps, m, 1) : ft_ps_step_f2(ps, m, 1);
	ft_ps_step_f(ps, m, ab);
	ps->isread = 1;
	ft_ps_swap_ab(ps, m, i / 2, ab);
	ps->st = ps->st == ps->a ? ps->b : ps->a;
	ab = ps->st == ps->a;
	ps->i = ab ? ps->a->count : ps->b->count;
	m = ft_ps_get_med(ps, 2);
	ps->i = i / 2;
	ft_ps_step_b(ps, m, i, ab);
}
int				ft_push_swap(t_ps *ps, int m, int s)
{
	ft_ps_swap_ab(ps, 0, ps->a->count, 1);

	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');
	ps->s *= 5;
	usleep(ps->s * 2);


	ft_ps_swap_ab(ps, 0, ps->b->count, 0);
	//ft_ps_move(ps, s);
	ps->i = m + s;
	GOTOXY(54, 35);
	return (0);
}
