/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:32:24 by cayako            #+#    #+#             */
/*   Updated: 2020/12/04 17:17:13 by cayako           ###   ########.fr       */
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
	while (i + 1 < (int)size)
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
	int		m;

	ps->cur_chunk = ft_ps_get_chunk(sw, 0);
	ps->i = ft_ps_chunk_count(sw, sort, ps->cur_chunk, 0);
	ps->chunk_count = ps->i;
	ft_sort_nb_arr(ps->sort, ps->i);
	m = sort[ps->i / d - (ps->i > 1 && ps->st == ps->b)];
	ps->i = ft_ps_mediana_chunk_count(ps->st->end, m, ps->cur_chunk,
				ps->st == ps->a);
	ps->i = ps->i ? ps->i : ps->chunk_count;
	return (m);
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
	ft_ps_fix(ps, ps->cmds, 0);
	ft_ps_end(ps);
	return (1);
}
