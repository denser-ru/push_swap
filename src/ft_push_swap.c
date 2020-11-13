
#include "push_swap.h"

void	ft_ps_step1(t_ps *ps, int mediana, int s, t_stak *d)
{
	while (*(ps->st->end->nb) < mediana && ps->i && ps->st->count > 2)
	{
		ft_add_cmd(ps, "pb\n");
		if (d->end)
			d->end->chunk = ps->chunk;
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
	while (*(ps->st->start->nb) < mediana && ps->i && ps->st->count > 2)
	{
		ft_add_cmd(ps, "rra\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
		ft_add_cmd(ps, "pb\n");
		if (d->end)
			d->end->chunk = ps->chunk;
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
}

void	ft_ps_step2(t_ps *ps, int mediana, int s, t_stak *d)
{
	while (ps->i && ps->st->count > 2)
	{
		if (*(ps->st->end->nb) <= mediana)
		{
			ft_add_cmd(ps, "pb\n");
			if (d->end)
				d->end->chunk = ps->chunk;
		}
		else
			ft_add_cmd(ps, "ra\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
}

int		ft_ps_sw_sort(t_ps *ps, t_swap *sw, int mediana, int *sort)
{
	while (sw)
	{
		*(sort++) = *(sw->nb);
		sw = sw->next;
	}
	mediana = sort[ps->st->count / 2];
	return (mediana);
}

int		ft_push_swap(t_ps *ps, int mediana, int s)
{
	s *= 1000;
	ps->i = ps->st->count / 2;
	while (ps->st->end && ps->i && ps->st->count > 2)
	{
		++ps->chunk;
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %d", mediana);
		ft_ps_step1(ps, mediana, s, ps->st == ps->a ? ps->b : ps->a);
		ft_ps_step2(ps, mediana, s, ps->st == ps->a ? ps->b : ps->a);
		mediana = ft_ps_sw_sort(ps, ps->st->start, 0, ps->sort);
		ps->i = ps->st->count / 2;
		GOTOXY(43, 35);
	}
	return (0);
}
