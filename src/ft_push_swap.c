
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

int            ft_check_ckunk(t_ps *ps, int mediana)
{
	if (ps->st == ps->a)
		return (*(ps->st->end->nb) <= mediana);
	else
		return (*(ps->st->end->nb) >= mediana);
}

void	ft_ps_step2(t_ps *ps, int mediana, int s)
{
	while (ps->i && ps->st->count > 2)
	{
		if (ft_check_ckunk(ps, mediana))
		{
			if (ps->st->end)
				ps->st->end->chunk = ps->st == ps->a ? ps->chunk: 1;
			ft_add_cmd(ps, ps->st == ps->a ? "pb\n" : "pa\n");
		}
		else
			ft_add_cmd(ps, ps->st == ps->a ? "ra\n" : "rb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
}

int		ft_ps_sw_sort(t_ps *ps, t_swap *sw, size_t i, int *sort)
{
	while (sw && (!sw->prev || sw->chunk == sw->prev->chunk))
	{
		*(sort++) = *(sw->nb);
		sw = sw->prev;
		++i;
	}
	ft_sort_nb_arr(ps->sort, i);
	ps->i = i > 1 ? i / 2: i;
	return (sort[ps->i]);
}

int		ft_lst_issorted(t_ps *ps)
{
	t_swap	*cur;

	if (!ps->a->start)
		return (0);
	cur = ps->a->start;
	while (cur && cur->next)
	{
		if (*(cur->nb) > *(cur->next->nb))
			return (0);
		cur = cur->next;
	}
	return (!ps->b->start);
}

int		ft_push_swap(t_ps *ps, int mediana, int s)
{
	s *= 1000;
	ps->i = ps->st->count > 1 ? ps->st->count / 2 : ps->st->count;
	while (!ft_lst_issorted(ps))
	{
	while (ps->st->end && ps->i && ps->st->count > 2)
	{
		if (ps->st == ps->a)
			++ps->chunk;
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %d", mediana);
		if (ps->st == ps->a)
			ft_ps_step1(ps, mediana, s);
		GOTOXY(42, 31);
		ft_printf("\e[38;5;251msw: %c; chunk: %d; end->nb: %-2d; ps->i: %-2d", ps->st == ps->a ? 'a' : 'b', ps->chunk, *(ps->st->end->nb), ps->i);
		ft_ps_step2(ps, mediana, s);
		GOTOXY(42, 31);
		ft_printf("\e[38;5;251msw: %c; chunk: %d; end->nb: %-2d ps->i: %-2d", ps->st == ps->a ? 'a' : 'b', ps->chunk, *(ps->st->end->nb), ps->i);
		mediana = ft_ps_sw_sort(ps, ps->st->end, 0, ps->sort);
		GOTOXY(43, 35);
	}
	if (!ps->b->start || ps->a->count <= 2)
		ps->st = ps->st == ps->a ? ps->b : ps->a;
	ps->chunk = ps->st->end->chunk;
	mediana = ft_ps_sw_sort(ps, ps->st->end, 0, ps->sort);
	}
	return (0);
}
