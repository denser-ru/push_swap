/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:25:07 by cayako            #+#    #+#             */
/*   Updated: 2020/11/06 03:25:54 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

static int 		*ft_create_nbarr(t_ps *ps, int argc, char **argv)
{
	int 	*nb;

	nb = (int*)malloc(sizeof(int) * --argc);
	ps->nb = nb;
	while (--argc)
		*(nb--) = ft_atoi(*(++argv));
	return (ps->nb);
}

static void 	ft_init_ps(t_ps *ps, int argc, char **argv)
{
	t_swap	*new;
	int 	*nb;

	nb = ft_create_nbarr(ps, argc, argv);
	ps->a = ft_lstsw_new(nb++);
	new = ps->a;
	while (--argc && nb)
	{
		new->next = ft_lstsw_add(new, nb++);
		new = new->next;
	}
}

int 			main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (1);
	ft_init_ps(&ps, argc, argv);
	CLRSRC();
	ft_printf(ESC "[H");
	SET_DISP_ATR(B_BLUE);
	ft_frame("5, 5, 20, 5", F_WHITE, B_BLUE);
	GOTOXY(8, 7);
	ft_printf("LLlukapHo =)\n");
	RESETCOLOR();
	GOTOXY(10, 20);
	ft_putchar('\n');
	return (0);
}
