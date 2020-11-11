//
// Created by Cheyenne Ayako on 11/7/20.
//

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

int 		ft_add_cmd(t_ps *ps, char *buf)
{
	const char	*cmd[11] = {"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", "ra\n",
					   "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};
	int 		i;

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
	exit (1);
}

void		ft_swap_nb(int *a, int *b)
{
	int		i;

	i = *a;
	*a = *b;
	*b = i;
}

int			*ft_sort_nb_arr(int *nb, size_t size)
{
	int		i;

	i = 0;
	--size;
	while (i < (int)size)
	{
		if (nb[i] > nb[i + 1])
		{
			ft_swap_nb(&nb[i], &nb[i + 1]);
			i = 0;
		}
		++i;
	}
	return (nb);
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
		SET_DISP_2ATR(F_WHITE, B_RED);		
		GOTOXY(102, y);
	}
	ft_printf("%-16d", nb);
}

