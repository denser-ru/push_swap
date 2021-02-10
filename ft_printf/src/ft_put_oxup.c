/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_oxup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 14:24:33 by cayako            #+#    #+#             */
/*   Updated: 2020/10/18 14:24:40 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_put_atoi_base(unsigned long long int nb, int base, char f)
{
	unsigned long long		hex;
	unsigned long long		div;
	unsigned long long		nb2;
	const char				*abc = "0123456789abcdef0123456789ABCDEF";

	if (nb < (unsigned long long)base)
	{
		ft_putchar(abc[nb + (f == 'X' ? 16 : 0)]);
		return ;
	}
	hex = nb / base;
	nb2 = nb / base;
	nb -= nb2 * base;
	div = 1;
	while ((hex /= base))
		div *= base;
	div *= base;
	while ((div /= base))
	{
		hex = nb2 / div;
		ft_putchar(abc[hex + (f == 'X' ? 16 : 0)]);
		nb2 -= hex * div;
	}
	ft_putchar(abc[nb + (f == 'X' ? 16 : 0)]);
}

void		ft_put_prefix(t_pf *pf, char f, int *width, unsigned long long nb)
{
	if (!(pf->flags & PF_ALIGN) && !(pf->flags & PF_ZERO))
		ft_putchar_n(' ', *width);
	ft_putchar_n(f == 'p' && !(pf->flags & PF_PLUS) ? ' ' : '+',
				((pf->flags & PF_PLUS) || (pf->flags & PF_SPACE)) && f == 'p');
	if ((pf->flags & PF_SHARP) && f == 'o' && nb)
		ft_putchar('0');
	else if ((pf->flags & PF_SHARP) && f != 'u' && nb)
		ft_putnstr(f == 'X' ? "0X" : "0x", 2);
	*width = *width < 0 ? 0 : *width;
	if (!(pf->flags & PF_ALIGN) && (pf->flags & PF_ZERO))
		ft_putchar_n('0', *width);
}

void		ft_put_x(t_pf *pf, char f, int base, unsigned long long int nb)
{
	int		size;
	int		width;
	int		prec;
	int		z;

	size = 1;
	z = ((pf->flags & PF_PREC) && !(pf->precision) && !nb
			&& !((pf->flags & PF_SHARP) && f == 'o'));
	size += z ? -1 : ft_get_nblen_base(nb, base);
	if ((pf->flags & PF_SHARP) && (f == 'o' || f == 'x' || f == 'X'
			|| f == 'p') && nb)
		size = f == 'o' ? size + 1 : size + 2;
	prec = (pf->precision - size) > 0 ? pf->precision - size : 0;
	width = pf->width - size - prec > 0 ? pf->width - size - prec : 0;
	ft_put_prefix(pf, f, &width, nb);
	pf->i += width + size + prec;
	if ((pf->flags & PF_PREC) && prec)
		ft_putchar_n('0', prec);
	if (!z)
		ft_put_atoi_base(nb, base, f);
	if (width && (pf->flags & PF_ALIGN))
		ft_putchar_n(' ', width);
}

void		ft_put_oxup(t_pf *pf, char f, int base)
{
	if (f == 'p')
		pf->flags = pf->flags | PF_LL | PF_SHARP;
	if (pf->flags & PF_LL)
		ft_put_x(pf, f, base, va_arg(*(pf->arg), unsigned long long int));
	else if (pf->flags & PF_L)
		ft_put_x(pf, f, base, va_arg(*(pf->arg), unsigned long int));
	else
		ft_put_x(pf, f, base, va_arg(*(pf->arg), unsigned int));
}
