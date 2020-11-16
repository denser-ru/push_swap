/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 01:15:07 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:43:36 by cayako           ###   ########.fr       */
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

t_frame			*ft_get_param1(t_frame *f, int x, int y, int w)
{
	f->x = x;
	f->y = y;
	f->w = w;
	return (f);
}

t_frame			*ft_get_param2(t_frame *f, int h, int fg, int bg)
{
	f->h = h;
	f->fg = fg;
	f->bg = bg;
	return (f);
}

void			ft_frame(t_frame *f)
{
	SET_DISP_2ATR(f->fg, f->bg);
	GOTOXY(f->x, f->y);
	ft_put_line(f->w - 2, "┌", "─", "┐");
	GOTOXY(f->x, f->y + (f->h)--);
	ft_put_line(f->w - 2, "└", "─", "┘");
	while (f->h > 0)
	{
		GOTOXY(f->x, f->y + (f->h)--);
		ft_put_line(f->w - 2, "│", " ", "│");
	}
	RESETCOLOR();
}

void			ft_clear_line(int x, int y, int fg, int bg)
{
	GOTOXY(x, y);
	SET_DISP_2ATR(fg, bg);
	ft_printf("                ");
}
