/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_bg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:14:11 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:46:32 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_put_bug(int i)
{
	const char	*cmd[15] = {"s                       m",
						"   $m                mm            m",
						"    \"$mmmmm        m$\"    mmmmmmm$\"",
						"          \"\"\"$m   m$    m$\"\"\"\"\"\"",
						"        mmmmmmm$$$$$$$$$\"mmmm",
						"  mmm$$$$$$$$$$$$$$$$$$ m$$$$m  \"    m  \"",
						"$$$$$$$$$$$$$$$$$$$$$$  $$$$$$\"$$$",
						" mmmmmmmmmmmmmmmmmmmmm  $$$$$$$$$$",
						" $$$$$$$$$$$$$$$$$$$$$  $$$$$$$\"\"\"  m",
						" \"$$$$$$$$$$$$$$$$$$$$$ $$$$$$  \"      \"",
						"     \"\"\"\"\"\"\"$$$$$$$$$$$m \"\"\"\"",
						"       mmmmmmmm\"  m$   \"$mmmmm",
						"     $$\"\"\"\"\"\"      \"$     \"\"\"\"\"\"$$",
						"   m$\"               \"m           ",
						"                       \""
	};

	while (cmd[i] && i++ < 14)
	{
		GOTOXY(42, 2 + i);
		ft_putendl(cmd[i]);
	}
}

static void		ft_put_menu(int i)
{
	ft_printf(ESC "[%d;%dH\tкоманды перестановок:", i++, 42);
	++i;
	ft_printf(ESC "[%d;%dH\tsa ↩\t\t↪ sb", i++, 42);
	ft_printf(ESC "[%d;%dH\t     ss = sa + sb", i++, 42);
	++i;
	ft_printf(ESC "[%d;%dH\tpa: ↽\t\t ⇁ pb\t", i++, 42);
	++i;
	ft_printf(ESC "[%d;%dH\tra: ⇣\t\t⇣ rb", i++, 42);
	ft_printf(ESC "[%d;%dH\t     rr = ra + rb", i++, 42);
	++i;
	ft_printf(ESC "[%d;%dH\trra ⇡\t\t⇡ rrb", i++, 42);
	ft_printf(ESC "[%d;%dH\t   rrr: rra + rrb", i, 42);
	i += 3;
	ft_printf(ESC "[%d;%dH     0 или \"\" - ожидание ввода", i, 42);
	i += 2;
	ft_printf(ESC "[%d;%dHот 1 до 1000 - задержка в миллисекундах", i, 42);
	SET_DISP_2ATR(F_WHITE, B_BLACK);
	GOTOXY(10, F_HEIGHT + 3);
	ft_printf("ведите команду: ");
}

void			ft_print_bg(t_frame *f)
{
	SET_DISP_2ATR(F_WHITE, B_BLACK);
	CLRSRC();
	ft_put_bug(0);
	ft_put_menu(17);
	ft_frame(ft_get_param2(ft_get_param1(f, 5, 1, 20),
						F_HEIGHT, F_WHITE, B_RED));
	ft_frame(ft_get_param2(ft_get_param1(f, 100, 1, 20),
						F_HEIGHT, F_WHITE, B_BLUE));
	ft_frame(ft_get_param2(ft_get_param1(f, 27, F_HEIGHT, 67),
						2, F_WHITE, B_BLACK));
	ft_printf(ESC "[H");
	SET_DISP_2ATR(F_BLACK, B_WHITE);
	GOTOXY(40, 0);
	ft_printf("Проект Push Swap студента cayako \"Школы 21\"\n");
	SET_DISP_2ATR(F_WHITE, B_RED);
	GOTOXY(14, 1);
	ft_putnstr(" A ", 3);
	SET_DISP_2ATR(F_WHITE, B_BLUE);
	GOTOXY(108, 1);
	ft_putnstr(" B ", 3);
	RESETCOLOR();
	GOTOXY(10, 37);
	ft_putchar('\n');
}
