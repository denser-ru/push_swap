/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 19:22:13 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

//static void		ft_ps_step1(t_ps *ps, int mediana, int s)
//{
//
//}
//
//
//
//void			ft_ps_step2(t_ps *ps, int ab, int mediana, int s)
//{
//
//}
//
int				ft_push_swap(t_ps *ps, int mediana, int s)
{
	ft_ps_move(ps, s);
	ps->i = mediana + s;
	return (0);
}
