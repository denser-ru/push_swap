/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_digit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 14:23:44 by cayako            #+#    #+#             */
/*   Updated: 2020/10/18 14:23:49 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long	ft_digit_modifer(t_pf *pf)
{
	if (pf->flags & PF_H)
		return ((short)va_arg(*(pf->arg), long long));
	if (pf->flags & PF_HH)
		return ((char)va_arg(*(pf->arg), long long));
	if (pf->flags & PF_L)
		return ((long)va_arg(*(pf->arg), long long));
	if (pf->flags & PF_LL)
		return (va_arg(*(pf->arg), long long));
	return ((int)va_arg(*(pf->arg), long long));
}

void		ft_digit_prefix(t_pf *pf, int prec, int sgn)
{
	char	c;

	if (!(pf->flags & PF_ALIGN) && (!(pf->flags & PF_ZERO)
			|| (pf->flags & PF_PREC)))
		ft_putchar_n(' ', pf->width);
	c = (pf->flags & PF_SPACE) ? ' ' : 0;
	if ((pf->flags & PF_PLUS) || sgn)
		c = sgn ? '-' : '+';
	ft_putchar_n(c, (pf->flags & PF_PLUS) || sgn || (pf->flags & PF_SPACE));
	if (!(pf->flags & PF_ALIGN) && (pf->flags & PF_ZERO)
			&& !(pf->flags & PF_PREC))
		ft_putchar_n('0', pf->width);
	ft_putchar_n('0', prec);
}

void		ft_put_digit(t_pf *pf, long long nb, int size, int prec)
{
	int		sgn;
	int		z;

	nb = ft_digit_modifer(pf);
	sgn = nb < 0 ? 1 : 0;
	nb = sgn ? -nb : nb;
	z = ((pf->flags & PF_PREC) && !(pf->precision) && !sgn && !nb);
	size = z ? 0 : ft_get_nblen_base(nb, 10) + 1;
	prec = (pf->precision - size) > 0 ? pf->precision - size : 0;
	size += ((pf->flags & PF_PLUS) || sgn || (pf->flags & PF_SPACE));
	pf->width = pf->width - size - prec > 0 ? pf->width - size - prec : 0;
	ft_digit_prefix(pf, prec, sgn);
	pf->i += pf->width + prec + size;
	if (!z)
		ft_put_atoi_base(nb, 10, 'd');
	ft_putchar_n(' ', (pf->width) * !(!(pf->flags & PF_ALIGN)));
}
