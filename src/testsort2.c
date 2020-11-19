//
// Created by Cheyenne Ayako on 11/19/20.
//

#include <stdio.h>
#include "push_swap.h"

int				ft_ps_get_m(t_ps *ps, t_swap *sw, size_t i, int *sort)
{
	while (sw && sw->chunk == 0)
		sw = sw->prev;
	while (sw)
	{
		sort[i] = *(sw->nb);
		sw = sw->prev;
		++i;
		if (sw && sw->next->chunk != sw->chunk)
			break ;
	}
	ps->i =  i == 1 ? 1 : i / 2 ;
	ft_sort_nb_arr(ps->sort, i);
	return (sort[i / 2]);
}

void ft_ps_merge_sort(t_ps *ps, int i, int m, int ab)
{
	if (!ps->b->start && ft_lst_issorted(ps))
		exit(0);
	++ps->chunk;
	if (!ps->st->start || ps->st->count <= 2 * ab)
		ps->st = ps->st == ps->a ? ps->b : ps->a;
	//	if (!(ps->st->count * ab))
	m = ft_ps_get_m(ps, ps->st->end, 0, ps->sort);
	if (i < 1)
		return ;
	if (i < 2 && ((ab && ps->st->end->prev &&  *(ps->st->end->nb) > *(ps->st->end->prev->nb)) ||
		(!ab && ps->st->end->prev && *(ps->st->end->nb) < *(ps->st->end->prev->nb))))
	{
		ft_add_cmd(ps, ab ? "sa\n" : "sb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(ps->s);
	}
	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана>: %-3d; i: %-2d count: %3d", m, ps->i, ps->st->count);
	usleep(ps->s);
	while (ps->i && ps->st->end && (ab ? *(ps->st->end->nb) <= m : *(ps->st->end->nb) >= m))
	{
//		if (ps->st->end)
//			ps->st->end->chunk = ab ? ps->chunk : 1;
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_put_cmd(ps, 1, 255);
		usleep(ps->s);
	}
	while (ps->i && ps->st->start && ps->st->end->chunk == ps->st->start->chunk
		&& ps->st->start->chunk < 3 && (ab ? *(ps->st->start->nb) <= m :
		*(ps->st->start->nb) >= m))
	{
		ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(ps->s);
//		if (ps->st->end)
//			ps->st->end->chunk = ab ? ps->chunk : 1;
		ft_add_cmd(ps, "pb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(ps->s);
	}
	while (ps->i && ps->st->end)
	{

		if (ab ? *(ps->st->end->nb) <= m : *(ps->st->end->nb) >= m)
		{
			if (ps->st->end)
				ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		}
		else
			ft_add_cmd(ps, ab ? "ra\n" : "rb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(ps->s);
	}
	ps->i =  i == 1 ? 1 : i / 2 ;
	ft_ps_merge_sort(ps, ps->i, 0, ps->st == ps->a);

	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана>: %-3d; i: %-2d", m, ps->i);
	usleep(ps->s);
}

int				ft_push_swap(t_ps *ps, int mediana, int s)
{
	ps->s = s * 1000;
	ps->i = ps->a->count / 2;
	ps->chunk = 1;
	ft_ps_merge_sort(ps, ps->i, mediana, 1);
	GOTOXY(54, 35);
	return (0);
}
