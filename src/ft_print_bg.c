//
// Created by Cheyenne Ayako on 11/6/20.
//

#include "push_swap.h"

void	ft_print_bg(t_frame *f)
{
	CLRSRC();
	ft_frame(ft_get_param2(ft_get_param1(f, 5, 3, 20), 44, F_WHITE, B_RED));
	ft_frame(ft_get_param2(ft_get_param1(f, 100, 3, 20), 44, F_WHITE, B_BLUE));
	ft_printf(ESC "[H");
	SET_DISP_2ATR(F_BLACK, B_WHITE);
	GOTOXY(40, 1);
	ft_printf("Проект Push Swap студента cayako \"Школы 21\"\n");
	RESETCOLOR();
	GOTOXY(10, 50);
	ft_putchar('\n');
}