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

int				ft_ps_sw_sort(t_ps *ps, t_swap *sw, size_t d, int *sort)
{
	int		i;

	i = 0;
	while (sw)
	{
		sort[i] = *(sw->nb);
		sw = sw->prev;
		++i;
		if (sw && sw->next->chunk != sw->chunk)
			break ;
	}
	ps->i = i;
	ft_sort_nb_arr(ps->sort, i);
	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана: %-3d; ps->i: %-3d; ab: %-3c", sort[i / d], ps->i, ps->st == ps->a ? 'a' : 'b');
	return (sort[i / d]);
}

int				ft_lst_issorted(t_ps *ps)
{
	t_swap	*cur;

	if (ps->b->start)
		return (0);
	cur = ps->a->start;
	while (cur && cur->next)
	{
		if (*(cur->nb) < *(cur->next->nb))
			return (0);
		cur = cur->next;
	}
		ft_ps_end(ps);
	return (0);
}
