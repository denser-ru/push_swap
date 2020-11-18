/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/11/18 00:30:29 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_ps_step1(t_ps *ps, int ab, int mediana, int s)
{
	while (*(ps->st->end->nb) < mediana && ps->i && ps->st->count > 2 && (ab || (!ab && ps->st->end->chunk > 0)))
	{
		if (ps->st->end)
			ps->st->end->chunk = ab ? ps->chunk : 1;
		ft_add_cmd(ps, ps->st == ps->a ? "pb\n" : "pa\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	ft_check_duble(ps, ps->st, mediana, s);
	}
	while (*(ps->st->start->nb) < mediana && ps->i && ps->st->count > 2 && ps->st->start->chunk > 0)
	{
		ft_add_cmd(ps, ps->st == ps->a ? "rra\n" : "rrb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
		if (ps->st->end)
			ps->st->end->chunk = ps->st == ps->a ? ps->chunk : 1;
		ft_add_cmd(ps, "pb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
		ft_check_duble(ps, ps->st, mediana, s);
	}
}

int				ft_check_chunk(t_ps *ps, int mediana)
{
	if (ps->st == ps->a)
		return (*(ps->st->end->nb) <= mediana);
	else
		return (ps->i != 1 ? *(ps->st->end->nb) > mediana :
			*(ps->st->end->nb) >= mediana);
}

void			ft_check_tail(t_ps *ps, int s, int ab)
{
	if (ps->st->end->prev && (!ps->st->end->prev->prev ||
		ps->st->end->prev->prev->chunk != ps->st->end->prev->chunk))
		if (!ft_check_chunk(ps, *(ps->st->end->prev->nb)) && (ab || (!ab && ps->st->end->chunk > 0)))
		{
			ft_add_cmd(ps, ps->st == ps->a ? "sa\n" : "sb\n");
			ft_put_cmd(ps, 1, 255);
			usleep(s);
		}
	if (ps->st->end->prev && ps->st->end->prev->chunk != ps->st->end->chunk
		&& *(ps->st->end->nb) < *(ps->st->end->prev->nb) && (ab || (!ab && ps->st->start->chunk > 0)))
	{
		ft_add_cmd(ps, "rb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
}

void			ft_check_tail2(t_ps *ps, int s, int ab)
{
	if (ps->a->end && ps->b->end && ps->a->end->prev && ps->b->end->prev &&
		*(ps->a->end->nb) > *(ps->a->end->prev->nb) &&
		*(ps->b->end->nb) < *(ps->b->end->prev->nb) && (ab || (!ab && ps->st->end->chunk > 0)))
	{
		ft_add_cmd(ps, "ss\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
	if (ps->b->end && ps->b->end->prev &&
		*(ps->b->end->nb) < *(ps->b->end->prev->nb) && (ab || (!ab && ps->st->end->chunk > 0)))
	{
		ft_add_cmd(ps, "sb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
	if (ps->st->end)
		ft_check_tail(ps, s, ab);
}

void			ft_ps_check_chunk_sort(t_ps *ps, int ab, int mediana, int s)
{
	if (!ab && ps->st->end && *(ps->st->end->nb) == *(ps->sort2 + ps->end)
		&& (size_t)ps->end <= ps->nb_size)
	{
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; end:%-3d", mediana, *(ps->sort2 + ps->end));
		ps->st->end->chunk = 0;
		ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, 1, 255);
		--ps->i;
		usleep(s * 2);
		ft_add_cmd(ps, "ra\n");
		ft_put_cmd(ps, 1, 255);
		++ps->end;
		usleep(s * 5);
	}
}

void			ft_ps_step2(t_ps *ps, int ab, int mediana, int s)
{
	ft_ps_check_chunk_sort(ps, ab, mediana, s);
	ft_check_tail2(ps, s, ab);
	while (ps->st->end && ps->i && ps->st->count > 2 * ab)
	{
	ft_ps_check_chunk_sort(ps, ab, mediana, s);
	ft_check_duble(ps, ps->st, mediana, s);
		if (ft_check_chunk(ps, mediana) && (ab || (!ab && ps->st->end->chunk > 0)))
		{
			if (ps->st->end)
				ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		}
		else if (ab || (!ab && ps->st->start->chunk > 0))
			ft_add_cmd(ps, ab ? "ra\n" : "rb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
		ft_ps_check_chunk_sort(ps, ab, mediana, s);
	}
}

int				ft_push_swap(t_ps *ps, int mediana, int s, int ab)
{
	s *= 1000;
	ps->i = ps->st->count > 1 ? ps->st->count / 2 : ps->st->count;
	while (!ft_lst_issorted(ps))
	{
		while (ps->st->end && ps->i && ps->st->count > 2 *
			(ab = ps->st == ps->a) && (ab || (!ab && ps->st->end->chunk > 0)))
		{
			if (ps->st == ps->a)
				++ps->chunk;
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; end:%-3d", mediana, *(ps->sort2 + ps->end));
			if (ps->st == ps->a && ps->a->count > 3)
				ft_ps_step1(ps, ps->st == ps->a, mediana, s);
			ft_ps_step2(ps, ps->st == ps->a, mediana, s);
			mediana = ft_ps_sw_sort(ps, ps->st->end, 0, ps->sort);
			GOTOXY(43, 35);
		}
		if (!ps->b->start || ps->a->count <= 2)
			ps->st = ps->st == ps->a ? ps->b : ps->a;
		ps->chunk = ps->st->end ? ps->st->end->chunk : 0;
		mediana = ft_ps_sw_sort(ps, ps->st->end, 0, ps->sort);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; end:%-3d", mediana, *(ps->sort2 + ps->end));
	}
	GOTOXY(54, 35);
	return (0);
}
