/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_swaps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:30:47 by cayako            #+#    #+#             */
/*   Updated: 2020/11/05 04:30:54 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_swap		*ft_lstsw_new(int *nb)
{
	t_swap	*sw;

	sw = (t_swap*)malloc(sizeof(t_swap));
	sw->nb = nb;
	sw->chunk = 1;
	sw->next = NULL;
	return (sw);
}

t_swap		*ft_lstsw_add(t_swap *prev, int *nb)
{
	t_swap	*sw;

	sw = (t_swap*)malloc(sizeof(t_swap));
	prev->next = sw;
	sw->nb = nb;
	sw->chunk = 1;
	return (sw);
}
