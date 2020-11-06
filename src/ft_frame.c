/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 01:15:07 by cayako            #+#    #+#             */
/*   Updated: 2020/11/06 03:22:04 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_put_line(int w, char *l, char *m, char *r)
{
	ft_putstr(l);
	while (w-- > 0)
		ft_putstr(m);
	ft_putstr(r);
}

void			ft_get_param(t_frame *f, char *p, int fg, int bg)
{
	f->x = ft_atoi(p);
	while (*p && *p != ',')
		++p;
	f->y = ft_atoi(++p);
	while (*p && *p != ',')
		++p;
	f->w = ft_atoi(++p);
	while (*p && *p != ',')
		++p;
	f->h = ft_atoi(++p);
	f->fg = fg;
	f->bg = bg;
}

void			ft_frame(char *param, int fg, int bg)
{
	t_frame		f;

	GOTOXY(10, 3);
	ft_get_param(&f, param, fg, bg);
	ft_printf("x=%d, y=%d, w=%d, h=%d\n", f.x, f.y, f.w, f.h);
	SET_DISP_ATR(f.bg);
	GOTOXY(f.x, f.y);
	ft_put_line(f.w - 2, "┌", "─", "┐");
	GOTOXY(f.x, f.y + (f.h)--);
	ft_put_line(f.w - 2, "└", "─", "┘");
	while (f.h > 0)
	{
		GOTOXY(f.x, f.y + (f.h)--);
		ft_put_line(f.w - 2, "│", " ", "│");
	}
	RESETCOLOR();
}
