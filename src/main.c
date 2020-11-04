//
// Created by Cheyenne Ayako on 11/3/20.
//

#include "push_swap.h"

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
	ps->a = ft_lstsw_new(ps, nb++);
	new = ps->a;
	while (--argc && nb)
	{
		new->next = ft_lstsw_add(ps, new, nb++);
		new = new->next;
	}
}

int 			main(int argc, char **argv)
{
	t_ps	ps;

	if (argc < 2)
		return (1);
	ft_init_ps(&ps, argc, argv);
	ft_printf("LLluKapHo =)\n");

	return (0);
}
