/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:25:07 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 18:31:05 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

void		ft_print_nb_arr(int *arr, size_t size)
{
	ft_putnendl("ok", 2);
	while (size--)
		ft_printf("nb[%d]: %d\n", size, arr[size]);
}

static int		*ft_create_nbarr(t_ps *ps, int argc, char **argv)
{
	int		*nb;
	int		*sort;
	int 	*sort2;

	nb = (int*)malloc(sizeof(int) * argc);
	sort = (int*)malloc(sizeof(int) * argc);
	sort2 = (int*)malloc(sizeof(int) * argc--);
	ps->nb = nb;
	ps->nb_size = argc;
	ps->sort = sort;
	ps->sort2 = sort2;
	nb += argc - 1;
	sort += argc - 1;
	while (argc--)
	{
		*(nb) = ft_atoi(*(++argv));
		*(sort--) = *(nb--);
		++(ps->a->count);
	}
	return (ps->nb);
}

void 			ft_ps_cp_sort2(int *sort2, int *sort1, size_t i)
{
	while (i--)
		*(sort2++) = *(sort1++);
}

void 			ft_ps_nb_link(t_ps *ps, t_swap *sw, int i)
{
	while (i < ps->a->count)
	{
		while (sw && ps->sort2[i] != *(sw->nb))
			sw = sw->prev;
		sw->s = i > 0 ? ps->sort2[i - 1] : ps->sort2[i];
		sw->l = i < ps->a->count ? ps->sort2[i + 1] : ps->sort2[i];
		++i;
		sw = ps->a->end;
	}
}

static void		ft_init_ps(t_ps *ps, int argc, char **argv)
{
	t_swap	*new;
	int		*nb;

	ft_bzero(ps->a, sizeof(t_stack));
	ft_bzero(ps->b, sizeof(t_stack));
	ps->st = ps->a;
	nb = ft_create_nbarr(ps, argc--, argv);
	ps->nb = nb;
	ft_sort_nb_arr(ps->sort, ps->a->count);
	ft_ps_cp_sort2(ps->sort2, ps->sort, ps->a->count);
//	ft_print_nb_arr(ps->sort, ps->nb_size);
//	ft_print_nb_arr(ps->sort2, ps->nb_size);
//	exit(0);
	ps->sorted = ps->sort2;
	ps->a->start = ft_lstsw_new(nb++);
	new = ps->a->start;
	ps->s = 300000;
	ps->cmds = (t_list*)NULL;
	while (--argc)
	{
		new->next = ft_lstsw_add(new, nb++);
		new = new->next;
	}
	ps->a->end = new;
	ft_ps_nb_link(ps, ps->a->end, 0);
}

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
	ft_init_ps(&ps, argc, argv);
	ft_print_bg(&f);
	ft_print_sw(a.start, 'a');
	if (ft_ft_read_in(&ps, buf))
		return (1);
	ft_putchar('\n');
	return (0);
}