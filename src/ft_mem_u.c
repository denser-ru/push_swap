/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:31:07 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 19:17:06 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_lst_swaps_del(t_swap *sw)
{
	if (sw->next)
		ft_lst_swaps_del(sw->next);
	sw->next = NULL;
	free(sw);
}

void			ft_memfree(t_ps *ps)
{
	ft_lst_swaps_del(ps->a->start);
}

void			ft_ps_end(t_ps *ps)
{
	ft_memfree(ps);
	GOTOXY(54, 35);
	ft_putchar('\n');
	exit (0);
}
