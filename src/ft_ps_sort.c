/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:32:24 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:44:38 by cayako           ###   ########.fr       */
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

int				*ft_sort_nb_arr(t_ps *ps, int *nb, size_t size)
{
	int		i;

	i = 0 * ps->count;
	--size;
	while (i < (int)size)
	{
		if (nb[i] > nb[i + 1])
		{
			ft_swap_nb(&nb[i], &nb[i + 1]);
			i = 0;
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
	ft_sort_nb_arr(ps, ps->sort, i);
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
	return (!ps->b->start);
}
