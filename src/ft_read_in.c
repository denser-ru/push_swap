//
// Created by Cheyenne Ayako on 11/6/20.
//

#include "push_swap.h"

void 	ft_put_cmd(t_ps *ps, int i, int c)
{
	t_list	*cmd;

	(void)c;
	GOTOXY(30, 41);
	cmd = ps->cmds;
	GOTOXY(30, 41);
	ft_printf(ESC "[38;5;250m[ %d ] команды: ", (ps->count)++);
	while (cmd && i < 43)
	{
		GOTOXY(43 + i, 41);
		ft_printf(ESC "[38;5;%dm", c);
		c -= c > 249 ? 1 : 2;
		ft_putchar(' ');
		ft_putnstr(cmd->content, cmd->content_size);
		i += cmd->content_size - 1;
		cmd = cmd->next;
	}
	GOTOXY(43 + i, 41);
	ft_putnstr("    ", 4);
}

int 	ft_ft_read_in(t_ps *ps, char *buf)
{
	SET_DISP_2ATR(F_WHITE, B_BLACK);
	GOTOXY(30, 41);
	ft_printf("[ %d ] команды: ", (ps->count)++);
	GOTOXY(10, 45);
	ft_printf("ведите команду: ");
	GOTOXY(27, 45);
	while (1)
	{
		ft_printf(ESC "[38;5;%dm", 255);
		if(!read(0, buf, 4))
			return (0);
		if (!ft_strcmp(buf, "exit"))
			return (0);
		if(!(ft_add_cmd(ps, buf)))
			return (1);
		GOTOXY(30, 41);
		buf[ft_strlen(buf) - 1] = '\0';
		ft_put_cmd(ps, 1, 255);
		GOTOXY(27, 45);
		ft_printf(ESC "[0K");
		GOTOXY(27, 45);
	}
}

void	ft_print_sw(t_swap *sw)
{
	int 	n;

	n = 41;
	if (!sw)
		return ;
	while (sw && sw->nb && n > 4)
	{
		GOTOXY(7, n--);
		SET_DISP_2ATR(F_WHITE, B_RED);
		ft_printf("%d\n", *(sw->nb));
		sw = sw->next;
	}
}