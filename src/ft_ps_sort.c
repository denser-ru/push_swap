/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:32:24 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 19:10:00 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void			ft_check_duble(t_ps *ps, t_stack *st, int mediana, int s)
{
	int		*sort;

	if (st == ps->b || !st->end || !st->end->prev || *(st->end->nb) > mediana ||
		*(st->end->prev->nb) > mediana || *(st->end->nb) < *(st->end->prev->nb))
		return ;
	sort = ps->sort;
	while (*sort != *(st->end->nb))
		++sort;
	if (*(sort - 1) == *(st->end->prev->nb))
	{
		ft_add_cmd(ps, ps->st == ps->a ? "sa\n" : "sb\n");
		ft_put_cmd(ps, 1, 255);
		usleep(s);
	}
		ft_lst_issorted(ps);
}

static void		ft_swap_nb(int *a, int *b)
{
	int		i;

	i = *a;
	*a = *b;
	*b = i;
}

int				*ft_sort_nb_arr(int *nb, size_t size)
{
	int		i;

	i = 0;
	--size;
	while (i < (int)size)
	{
		if (nb[i] > nb[i + 1])
		{
			ft_swap_nb(&nb[i], &nb[i + 1]);
			i = -1;
		}
		++i;
	}
	return (nb);
}

int				ft_ps_sw_sort(t_ps *ps, t_swap *sw, size_t i, int *sort)
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
	ft_sort_nb_arr(ps->sort, i);
	return (sort[i / 2]);
}

int				ft_lst_issorted(t_ps *ps)
{
	t_swap	*cur;

	cur = ps->a->start;
	while (cur && cur->next)
	{
		if (*(cur->nb) < *(cur->next->nb))
			return (0);
		cur = cur->next;
	}
	if (!ps->b->start)
		ft_ps_end(ps);
	return (0);
}
