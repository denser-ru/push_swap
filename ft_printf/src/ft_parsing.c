/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 14:21:51 by cayako            #+#    #+#             */
/*   Updated: 2020/10/18 14:22:09 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_get_width(t_pf *pf, char **format)
{
	pf->width = ft_atoi(*format);
	while (ft_strchr("0123456789", **format))
		++(*format);
	--(*format);
}

static void		ft_get_precision(t_pf *pf, char **format)
{
	pf->flags = pf->flags | PF_PREC;
	++(*format);
	pf->precision = ft_atoi(*format);
	while (ft_strchr("0123456789", **format))
		++(*format);
	--(*format);
}

static void		ft_get_flag(t_pf *pf, char **format)
{
	if (**format == '0')
		pf->flags = pf->flags | PF_ZERO;
	else if (**format == '+')
		pf->flags = pf->flags | PF_PLUS;
	else if (**format == '-')
		pf->flags = pf->flags | PF_ALIGN;
	else if (**format == ' ')
		pf->flags = pf->flags | PF_SPACE;
	else if (**format == '#')
		pf->flags = pf->flags | PF_SHARP;
}

static void		ft_get_modifier(t_pf *pf, char **format)
{
	if (**format == 'h')
	{
		if (*((*format) + 1) == 'h' && *(++(*format)))
			pf->flags = pf->flags | PF_HH;
		else
			pf->flags = pf->flags | PF_H;
	}
	else if (**format == 'l')
	{
		if (*((*format) + 1) == 'l' && *(++(*format)))
			pf->flags = pf->flags | PF_LL;
		else
			pf->flags = pf->flags | PF_L;
	}
	else if (**format == 'L')
		pf->flags = pf->flags | PF_ML;
}

void			ft_parsing(t_pf *pf, char *format)
{
	while (*format && !ft_memchr("diouxXfcsp%", *format, 11))
	{
		if (ft_strchr("#0-+ ", *format))
			ft_get_flag(pf, &format);
		else if (ft_strchr("0123456789", *format))
			ft_get_width(pf, &format);
		else if (ft_strchr(".", *format))
			ft_get_precision(pf, &format);
		else if (ft_strchr("hlL", *format))
			ft_get_modifier(pf, &format);
		else
			break ;
		++format;
	}
	if (*format)
		pf->cur = format;
	ft_putarg(pf, format);
}
