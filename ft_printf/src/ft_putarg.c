/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putarg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 14:23:12 by cayako            #+#    #+#             */
/*   Updated: 2020/10/18 14:23:21 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_putarg(t_pf *pf, char *format)
{
	if (*format == '%')
		ft_put_percent(pf);
	else if (*format == 'd' || *format == 'i')
		ft_put_digit(pf, 0, pf->width, pf->precision);
	else if (*format == 'c')
		ft_put_pf_char(pf, 0);
	else if (*format == 's')
		ft_put_pf_str(pf, NULL);
	else if (*format == 'x' || *format == 'X' || *format == 'p')
		ft_put_oxup(pf, *format, 16);
	else if (*format == 'o')
		ft_put_oxup(pf, *format, 8);
	else if (*format == 'u')
		ft_put_oxup(pf, *format, 10);
	else if (*format == 'f')
		ft_put_f(pf);
	else
	{
		ft_putchar('%');
		++(pf->i);
		return ;
	}
	pf->cur = ++format;
}
