/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:42:22 by cayako            #+#    #+#             */
/*   Updated: 2021/02/10 16:42:25 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_check_sorted(t_ps *ps)
{
	if (ft_lst_issorted(ps))
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
}

static void		ft_ps_select(t_ps *ps, int argc, char **argv, char *buf)
{
	if (!ft_strcmp(argv[1], "-g"))
		ps->gui = 1;
	ft_init_ps(ps, argc - (ps->gui > 0), ++argv + (ps->gui > 0));
	if (ps->gui)
	{
		ft_print_bg(ps->f);
		ft_print_sw(ps->a->start, 'a');
		ft_ps_read_in(ps, buf);
	}
	else if (!ft_ps_read_stdin(ps, NULL))
		ft_ps_read_in_txt(ps, buf);
}

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
	ft_ps_select(&ps, argc, argv, buf);
	ft_check_sorted(&ps);
	return (0);
}
