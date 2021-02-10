/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_chunk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:30:40 by cayako            #+#    #+#             */
/*   Updated: 2021/02/10 16:30:43 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				ft_ps_chunk_count(t_swap *sw, int *sort, int chunk, int i)
{
	while (sw)
	{
		if (sw->chunk && sw->chunk == chunk)
			sort[i++] = *(sw->nb);
		sw = sw->prev;
	}
	return (i);
}

int				ft_ps_chunk_count_up(t_swap *sw, int *sort, int i)
{
	while (sw && sw->chunk)
	{
		sort[i] = *(sw->nb);
		sw = sw->prev;
		++i;
		if (sw && sw->next->chunk != sw->chunk)
			break ;
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
		if ((ab && *(sw->nb) < m && sw->chunk == chunk) ||
				(!ab && *(sw->nb) > m && sw->chunk == chunk))
			++i;
		sw = sw->prev;
	}
	return (i);
}

void			ft_ps_check_chunk(t_ps *ps, t_swap *sw, int m, char *dev)
{
	if (FT_DEV)
		ft_ps_dev(ps, m, dev);
	if (*(sw->nb) != ps->sort2[ps->a->count + ps->b->count - 1])
		return ;
	while (sw && sw->next)
	{
		if (*(sw->next->nb) == sw->s)
		{
			sw->chunk = 0;
			sw->next->chunk = 0;
		}
		else
			return ;
		sw = sw->next;
	}
}
