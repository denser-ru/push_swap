/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:25:07 by cayako            #+#    #+#             */
/*   Updated: 2020/12/03 11:45:37 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int				main(int argc, char **argv)
{
	t_ps	ps;
	t_stack	a;
	t_stack	b;
	t_frame f;
	char	buf[5];

	if (argc < 2)
		return (1);
	ft_bzero(&ps, sizeof(ps));
	ps.a = &a;
	ps.b = &b;
	ps.f = &f;
	if (!ft_strcmp(argv[1], "-g"))
		ps.gui = 1;
	ft_init_ps(&ps, argc - (ps.gui > 0), ++argv + (ps.gui > 0));
	if (FT_DEV)
	{
		ft_print_bg(&f);
		ft_print_sw(a.start, 'a');
	}
	if (FT_DEV && ft_ps_read_in(&ps, buf))
		return (1);
	else
		ft_push_swap(&ps, 0);
	ft_putchar('\n');
	return (0);
}
