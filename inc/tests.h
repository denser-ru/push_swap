/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:15:46 by cayako            #+#    #+#             */
/*   Updated: 2020/11/15 01:15:49 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_print_nb_arr(int *arr, size_t size)
{
	ft_putnendl("ok", 2);
	while (size--)
		ft_printf("nb[%d]: %d\n", size, arr[size]);
}
