//
// Created by Cheyenne Ayako on 11/7/20.
//

#include "push_swap.h"

int 		ft_add_cmd(t_ps *ps, char *buf)
{
	const char	*cmd[11] = {"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", "ra\n",
					   "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};
	int 		i;

	i = 0;
	while (cmd[i] && *buf && i < 11)
	{
		if (!ft_strcmp(cmd[i], buf))
			return (ft_lstpushf(&(ps->cmds), buf, ft_strlen(buf - 1)) != NULL);
		++i;
	}
	GOTOXY(0, 51);
	ft_printf(ESC "[0K");
	ft_putendl("Error");
	exit (1);
}