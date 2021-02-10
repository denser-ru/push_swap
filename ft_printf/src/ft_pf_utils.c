/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 14:12:39 by cayako            #+#    #+#             */
/*   Updated: 2020/10/18 14:13:23 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void				ft_putchar_n(char c, int i)
{
	while (i--)
		ft_putchar(c);
}

unsigned long long	ft_get_max_base(int base)
{
	unsigned long long int	i;

	i = 1;
	while (i * base > i)
		i *= base;
	return (i);
}

int					ft_get_nblen_base(unsigned long long nb, int base)
{
	unsigned long long int	i;

	i = 0;
	while ((nb /= base))
		++i;
	return (i);
}
