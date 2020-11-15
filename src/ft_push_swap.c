/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/11/15 13:03:09 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ps_step1(t_ps *ps, int mediana, int s)
{
	while (*(ps->st->end->nb) < mediana && ps->i && ps->st->count > 2)
	{
		if (ps->st->end)
			ps->st->end->chunk = ps->st == ps->a ? ps->chunk: 1;
		ft_add_cmd(ps, ps->st == ps->a ? "pb\n" : "pa\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
	while (*(ps->st->start->nb) < mediana && ps->i && ps->st->count > 2)
	{
		ft_add_cmd(ps, ps->st == ps->a ? "rra\n" : "rrb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
		if (ps->st->end)
			ps->st->end->chunk = ps->st == ps->a ? ps->chunk: 1;
		ft_add_cmd(ps, "pb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
}

int            ft_check_chunk(t_ps *ps, int mediana)
{
	if (ps->st == ps->a)
		return (*(ps->st->end->nb) <= mediana);
	else
		return (*(ps->st->end->nb) >= mediana);
}

void	ft_check_tail(t_ps *ps, int s)
{
	if (ps->st->end->prev && (!ps->st->end->prev->prev ||
							 ps->st->end->prev->prev->chunk != ps->st->end->prev->chunk))
	if (!ft_check_chunk(ps, *(ps->st->end->prev->nb)))
	{
		ft_add_cmd(ps, ps->st == ps->a ? "sa\n" : "sb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
}

void	ft_ps_step2(t_ps *ps, int mediana, int s)
{
	while (ps->st->end && ps->i && ps->st->count > 2 * (ps->st == ps->a))
	{
		if (ft_check_chunk(ps, mediana))
		{
			if (ps->st->end)
				ps->st->end->chunk = ps->st == ps->a ? ps->chunk: 1;
			ft_add_cmd(ps, ps->st == ps->a ? "pb\n" : "pa\n");
		}
		else
			ft_add_cmd(ps, ps->st == ps->a ? "ra\n" : "rb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
		if (ps->st->end)
			ft_check_tail(ps, s);
	}
}

int		ft_ps_sw_sort(t_ps *ps, t_swap *sw, size_t i, int *sort)
{
	while (sw)
	{
		sort[i] = *(sw->nb);
		sw = sw->prev;
		++i;
		if (sw && sw->next->chunk != sw->chunk)
			break ;
	}
	ps->i = i > 1 ? i / 2 : i;
	ft_sort_nb_arr(ps, ps->sort, i);
			GOTOXY(70, 29);
			ft_printf("\e[38;5;251mi: %-2d; sort: %-2d", i, sort[i / 2]);
		sleep(1);

	return (sort[i / 2]);
}

int		ft_lst_issorted(t_ps *ps)
{
	t_swap	*cur;

	cur = ps->a->start;
			GOTOXY(54, 29);
			ft_printf("\e[38;5;251m???");
		sleep(1);
	while (cur && cur->next)
	{
		if (*(cur->nb) < *(cur->next->nb))
		{
			GOTOXY(54, 29);
			ft_printf("\e[38;5;251mHET: %-2d < %-2d", *(cur->nb), *(cur->next->nb));
		sleep(1);
			GOTOXY(54, 29);
			ft_printf("\e[38;5;251m           ");
			return (0);
		}
		cur = cur->next;
	}
			GOTOXY(54, 29);
			ft_printf("\e[38;5;251mВозможно");
		sleep(1);
			GOTOXY(54, 29);
			ft_printf("\e[38;5;251m         ");
	return (!ps->b->start);
}

int		ft_push_swap(t_ps *ps, int mediana, int s)
{
	s *= 1000;
	ps->i = ps->st->count > 1 ? ps->st->count / 2 : ps->st->count;
	while (!ft_lst_issorted(ps))
	{
		while (ps->st->end && ps->i && ps->st->count > 2 * (ps->st == ps->a))
		{
			if (ps->st == ps->a)
				++ps->chunk;
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d", mediana);
			if (ps->st == ps->a)
				ft_ps_step1(ps, mediana, s);
			ft_ps_step2(ps, mediana, s);
			mediana = ft_ps_sw_sort(ps, ps->st->end, 0, ps->sort);
			GOTOXY(43, 35);
		}
	if (!ps->b->start || ps->a->count <= 2)
		ps->st = ps->st == ps->a ? ps->b : ps->a;
	ps->chunk = ps->st->end ? ps->st->end->chunk: 0;
	mediana = ft_ps_sw_sort(ps, ps->st->end, 0, ps->sort);
		usleep(s * 3);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d", mediana);
	}
	GOTOXY(54, 35);
	return (0);
}
