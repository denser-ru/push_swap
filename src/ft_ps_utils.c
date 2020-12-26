/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:15:03 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 12:59:07 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_do_cmd(t_ps *ps, char *buf)
{
	if (*buf == 's' && buf[1] == 'a')
		ft_ps_sa(ps);
	if (*buf == 's' && buf[1] == 'b')
		ft_ps_sb(ps);
	if (*buf == 's' && buf[1] == 's')
		ft_ps_ss(ps);
	if (*buf == 'p' && buf[1] == 'a')
		ft_ps_pa(ps);
	if (*buf == 'p' && buf[1] == 'b')
		ft_ps_pb(ps);
	if (*buf == 'r' && buf[1] == 'a')
		ft_ps_ra(ps);
	if (*buf == 'r' && buf[1] == 'b')
		ft_ps_rb(ps);
	if (*buf == 'r' && buf[1] == 'r' && buf[2] == 'a')
		ft_ps_rra(ps);
	if (*buf == 'r' && buf[1] == 'r' && buf[2] == 'b')
		ft_ps_rrb(ps);
	if (*buf == 'r' && buf[1] == 'r' && buf[2] == 'r')
		ft_ps_rrr(ps);
	if (*buf == 'r' && buf[1] == 'r' && buf[2] == '\n')
		ft_ps_rr(ps);
}

int			ft_add_cmd(t_ps *ps, char *buf)
{
	const char	*cmd[11] = {"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", "ra\n",
					"rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};
	int			i;

	i = 0;
	while (cmd[i] && *buf && i < 11)
	{
		if (!ft_strcmp(cmd[i], buf))
		{
			ft_do_cmd(ps, buf);
			return (ft_lstpushf(&(ps->cmds), buf, ft_strlen(buf) - 1) != NULL);
		}
		++i;
	}
	GOTOXY(0, 47);
	ft_printf(ESC "[0K");
	ft_putendl("Error");
	exit(1);
}

void		ft_print_nb(int nb, int y, char c)
{
	if (c == 'a')
	{
		SET_DISP_2ATR(F_WHITE, B_RED);
		GOTOXY(7, y);
	}
	else
	{
		SET_DISP_2ATR(F_WHITE, B_BLUE);
		GOTOXY(102, y);
	}
	ft_printf("%-16d", nb);
}

int 		ft_ps_find_bug(char *s1, char *s2, int i)
{
	const char	*cmd[12] = {"pb", "pa",
						   "pa", "pb",
						   "ra", "rra",
						   "rra", "ra",
						   "rb", "rrb",
						   "rrb", "rb"
	};
	while (i < 12)
	{
		if (!ft_strcmp(s1, cmd[i]) && !ft_strcmp(s2, cmd[i + 1]))
			return (1);
		i += 2;
	}
	return (0);
}

int 		ft_ps_fix(t_ps *ps, t_list *cmd, int i)
{
	while (cmd)
	{
		if (cmd->next && ft_ps_find_bug(cmd->content, cmd->next->content, 0))
		{
			ft_lstcut(&(ps->cmds), cmd, ft_lstdelcontent);
			ft_lstcut(&(ps->cmds), cmd->next, ft_lstdelcontent);
			ps->count -= 2;
			cmd = ps->cmds;
		}
		cmd = cmd->next;
		++i;
	}
	ps->fix = 1;
	return (i);
}