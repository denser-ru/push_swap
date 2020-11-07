//
// Created by Cheyenne Ayako on 11/6/20.
//

#include "push_swap.h"

void	ft_put_bug(int i)
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
		GOTOXY(42, 5 + i);
		ft_putendl(cmd[i]);
	}
}

void 	ft_put_menu(int i)
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
}

void	ft_print_bg(t_frame *f)
{
	CLRSRC();
	ft_put_bug(0);
	ft_put_menu(23);
	ft_frame(ft_get_param2(ft_get_param1(f, 5, 3, 20), 40, F_WHITE, B_RED));
	ft_frame(ft_get_param2(ft_get_param1(f, 100, 3, 20), 40, F_WHITE, B_BLUE));
	ft_frame(ft_get_param2(ft_get_param1(f, 27, 41, 71), 2, F_WHITE, 90));
	ft_printf(ESC "[H");
	SET_DISP_2ATR(F_BLACK, B_WHITE);
	GOTOXY(40, 2);
	ft_printf("Проект Push Swap студента cayako \"Школы 21\"\n");
	SET_DISP_2ATR(F_WHITE, B_RED);
	GOTOXY(14, 3);
	ft_putnstr(" A ", 3);
	SET_DISP_2ATR(F_WHITE, B_BLUE);
	GOTOXY(108, 3);
	ft_putnstr(" B ", 3);
	RESETCOLOR();
	GOTOXY(10, 51);
	ft_putchar('\n');
}