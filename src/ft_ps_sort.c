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

void		ft_print_nb_arr2(int *arr, size_t size)
{
	ft_putnendl("ok", 2);
	while (size--)
		ft_printf("nb[%d]: %-3d\n", size, arr[size]);
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

int 			ft_ps_chunk_count(t_swap *sw, int *sort, int chunk, int i)
{
	while (sw)
	{
		if (sw->chunk && sw->chunk == chunk)
			sort[i++] = *(sw->nb);
		sw = sw->prev;
	}
	return (i);
}

int				ft_ps_get_chunk(t_swap *sw, int chunk)
{
	while (sw)
	{
		if (sw->chunk > chunk)
			chunk = sw->chunk;
		sw = sw->prev;
	}
	return (chunk);
}

int				ft_ps_mediana_chunk_count(t_swap *sw, int m, int chunk, int ab)
{
	int		i;

	i = 0;
	while (sw)
	{
		if ((ab && *(sw->nb) < m && sw->chunk == chunk) || (!ab && *(sw->nb) > m && sw->chunk == chunk))
			++i;
		sw = sw->prev;
	}
	return (i);
}

int				ft_ps_sw_sort(t_ps *ps, t_swap *sw, size_t d, int *sort)
{
	int		m;

	ps->cur_chunk = ft_ps_get_chunk(sw, 0);
	ps->i = ft_ps_chunk_count(sw, sort, ps->cur_chunk, 0);
//	GOTOXY(0, 2);
//		ft_print_nb_arr2(ps->sort, ps->nb_size);
	ps->chunk_count = ps->i;
	ft_sort_nb_arr(ps->sort, ps->i);
	m = sort[ps->i / d - (ps->st == ps->b)];
	ps->i = ft_ps_mediana_chunk_count(ps->st->end, m, ps->cur_chunk, ps->st == ps->a);
//	ps->i = ps->chunk_count % 2 ? ps->i +1 : ps->i;
	ps->i = ps->i ? ps->i : ps->chunk_count;
	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана: %-3d; (f2.2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
//		read(0, ps->sort, 1);
//	GOTOXY(0, 20);
//		ft_print_nb_arr2(ps->sort, ps->nb_size);
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
		ft_ps_end(ps);
	return (0);
}
