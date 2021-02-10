//
// Created by Cheyenne Ayako on 1/28/21.
//

#include "push_swap.h"
#include "get_next_line.h"

static int		ft_ps_read_in_txt(t_ps *ps, char *buf)
{
	while (1)
	{
		if (!read(0, buf, 4))
			return (0);
		if (ft_isdigit(buf[0]))
			return (ft_push_swap(ps, ft_atoi(buf)));
		if (!ft_strcmp(buf, "exit"))
			return (0);
		if (!(ft_add_cmd(ps, buf)))
			return (1);
		buf[ft_strlen(buf) - 1] = '\0';
		ft_put_cmd(ps, ps->cmds, 1, 255);
	}
}

int			ft_add_cmd_in(t_ps *ps, char *buf)
{
    const char	*cmd[11] = {"sa\n", "sb\n", "ss\n", "pa\n", "pb\n", "ra\n",
                              "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n"};
    int			i;

    i = 0;
    while (cmd[i] && *buf && i < 11)
    {
        if (!ft_strcmp(cmd[i], buf))
            return (ft_lstpushb(&(ps->cmds), buf, ft_strlen(buf) - 1) != NULL);
        ++i;
    }
    GOTOXY(0, 47);
    ft_printf(ESC "[0K");
    ft_putendl("Error");
    exit(1);
}

static int		ft_ps_read_stdin(t_ps *ps, char *buf)
{
    int     i;
    t_list  *cmds;

    i = 0;
    while (get_next_line(0, &buf))
    {
        ft_putendl(buf);
        buf[ft_strlen(buf)] = '\n';
        ft_add_cmd_in(ps, buf);
        ft_bzero(buf, 5);
        ++i;
    }
    cmds = ps->cmds;
//    ft_putendl("-----");
    while (cmds)
    {
        ft_do_cmd(ps, (char*)cmds->content);
//        ft_putnstr((char*)cmds->content, cmds->content_size);
//        ft_putchar('\n');
        cmds = cmds->next;
    }
    return (i > 0);
}

static void     ft_check_sorted(t_ps *ps)
{
    if (ft_lst_issorted(ps))
        ft_printf("OK\n");
    else
        ft_printf("KO\n");
}

//void	ft_print_sw_tmp(t_swap *sw)
//{
//    int		n;
//
//    n = 10;
//    if (!sw)
//        return ;
//    while (sw && sw->nb && n > 1)
//    {
//        ft_printf("\e[38;5;%dm%-16d", 262 , *(sw->nb));
//        sw = sw->next;
//    }
//}

int				main(int argc, char **argv)
{
	t_ps	ps;
	t_stack	a;
	t_stack	b;
	t_frame f;
	char	buf[5];

	if (argc < 2)
		return (0);
	ft_bzero(&ps, sizeof(ps));
	ps.a = &a;
	ps.b = &b;
	ps.f = &f;
	ps.checker = 1;
	if (!ft_strcmp(argv[1], "-g"))
		ps.gui = 1;
	ft_init_ps(&ps, argc - (ps.gui > 0), ++argv + (ps.gui > 0));
	if (ps.gui)
	{
		ft_print_bg(&f);
		ft_print_sw(a.start, 'a');
		ft_ps_read_in(&ps, buf);
	}
	else if (!ft_ps_read_stdin(&ps, NULL))
        ft_ps_read_in_txt(&ps, buf);
//    ft_print_sw_tmp(ps.a->start);
//    ft_print_sw_tmp(ps.b->start);
    ft_check_sorted(&ps);
	return (0);
}
