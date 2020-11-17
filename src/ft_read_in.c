/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_in.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:48:59 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:58:20 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_put_cmd(t_ps *ps, int i, int c)
{
	t_list	*cmd;

	(void)c;
	cmd = ps->cmds;
	GOTOXY(30, 33);
	ft_printf(ESC "[40;37m[ %d ] команды: ", (ps->count)++);
	while (cmd && i < 43)
	{
		GOTOXY(43 + i, 33);
		ft_printf(ESC "[38;5;%dm\e[40m", c);
		c -= c > 249 ? 1 : 2;
		ft_putchar(' ');
		ft_putnstr(cmd->content, cmd->content_size);
		i += cmd->content_size + 1;
		cmd = cmd->next;
	}
	GOTOXY(43, 35);
}

int		ft_ft_read_in(t_ps *ps, char *buf)
{
	SET_DISP_2ATR(F_WHITE, B_BLACK);
	GOTOXY(30, 33);
	ft_printf("[ %d ] команды: ", (ps->count)++);
	GOTOXY(10, 35);
	ft_printf("ведите команду: ");
	GOTOXY(27, 35);
	while (1)
	{
		ft_printf(ESC "[38;5;%d;m\e[48;5;16m", 255);
		if (!read(0, buf, 4))
			return (0);
		if (ft_isdigit(buf[0]))
			return (ft_push_swap(ps, ps->sort[ps->a->count / 2], ft_atoi(buf)));
		if (!ft_strcmp(buf, "exit"))
			return (0);
		if (!(ft_add_cmd(ps, buf)))
			return (1);
		GOTOXY(30, 33);
		buf[ft_strlen(buf) - 1] = '\0';
		ft_put_cmd(ps, 1, 255);
		GOTOXY(27, 35);
		ft_printf(ESC "[40;97m\e[0K");
		GOTOXY(27, 35);
	}
}

void	ft_print_sw(t_swap *sw, char c)
{
	int		n;

	n = 32;
	if (!sw)
		return ;
	while (sw && sw->nb && n > 4)
	{
		if (c == 'b')
		{
			ft_clear_line(102, n - 1, F_WHITE, B_BLUE);
			GOTOXY(102, n--);
		}
		else
		{
			ft_clear_line(7, n - 1, F_WHITE, B_RED);
			GOTOXY(7, n--);
		}
		ft_printf("\e[38;5;%dm%-12d%4d", 262 - 7 * sw->chunk, *(sw->nb), sw->chunk);
		sw = sw->next;
	}
}
