/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:25:07 by cayako            #+#    #+#             */
/*   Updated: 2020/11/08 01:16:59 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

static int 		*ft_create_nbarr(t_ps *ps, int argc, char **argv)
{
	int 	*nb;

	nb = (int*)malloc(sizeof(int) * --argc);
	ps->nb = nb;
	while (argc--)
	{
		*(nb++) = ft_atoi(*(++argv));
		++(ps->count_a);
	}
	return (ps->nb);
}

static void 	ft_init_ps(t_ps *ps, int argc, char **argv)
{
	t_swap	*new;
	int 	*nb;

	nb = ft_create_nbarr(ps, argc--, argv);
	ps->nb = ft_sort_nb_arr(nb, ps->count);
	ps->a = ft_lstsw_new(nb++);
	new = ps->a;
	while (--argc)
	{
		new->next = ft_lstsw_add(new, nb++);
		new = new->next;
	}
}

int 			main(int argc, char **argv)
{
	t_ps	ps;
	t_frame f;
	char 	buf[5];

	if (argc < 2)
		return (1);
	ft_bzero(&ps, sizeof(ps));
	ft_init_ps(&ps, argc, argv);
	ft_print_bg(&f);
	ft_print_sw(ps.a, 'a');
	ft_print_sw(ps.b, 'b');
	if(ft_ft_read_in(&ps, buf))
		return (1);
	ft_putchar('\n');
	return (0);
}
