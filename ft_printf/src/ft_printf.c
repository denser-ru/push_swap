/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 14:22:27 by cayako            #+#    #+#             */
/*   Updated: 2020/10/18 14:22:34 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_clear_args(t_pf *pf)
{
	pf->width = 0;
	pf->precision = 0;
	pf->flags = 0;
}

int				ft_printf(const char *format, ...)
{
	va_list		arg;
	t_pf		pf_s;
	t_pf		*pf;

	pf = &pf_s;
	ft_bzero(pf, sizeof(t_pf));
	pf->arg = &arg;
	pf->start = (char*)format;
	pf->cur = pf->start;
	va_start(arg, format);
	while ((pf->next = ft_strchr(pf->cur, '%')))
	{
		pf->i += pf->next - pf->cur;
		ft_putnstr(pf->cur, pf->next - pf->cur);
		pf->cur = pf->next + 1;
		ft_parsing(pf, pf->cur);
		ft_clear_args(pf);
	}
	ft_putnstr(pf->cur, ft_strchr(pf->cur, '\0') - pf->cur);
	return (pf->i + ft_strchr(pf->cur, '\0') - pf->cur);
}
