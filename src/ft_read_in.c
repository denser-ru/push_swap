//
// Created by Cheyenne Ayako on 11/6/20.
//

#include "push_swap.h"

int 	ft_ft_read_in(char *buf)
{
	GOTOXY(10, 50);
	ft_printf("ведите команду: ");
	GOTOXY(27, 50);
	while (ft_strcmp(buf, "exit"))
	{
		read(0, buf, 4);
		GOTOXY(30, 48);
		ft_printf("было ввдено: %s", buf);
		GOTOXY(27, 50);
		ft_printf(ESC "[0K");
		GOTOXY(0, 49);
		ft_printf(ESC "[0K");
		GOTOXY(27, 50);
	}
	return (0);
}

void	ft_print_sw(t_swap *sw)
{
	int 	n;

	n = 46;
	if (!sw)
		return ;
	while (sw && sw->nb && n > 4)
	{
		GOTOXY(7, n--);
		ft_printf("%d\n", *(sw->nb));
		sw = sw->next;
	}
}