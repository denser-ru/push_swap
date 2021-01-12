//
// Created by Cheyenne Ayako on 12/26/20.
//

#include "push_swap.h"

void	ft_ps_err(t_ps *ps, int err)
{
	(void)err;
	ft_memfree(ps);
	ft_putendl_fd("Error", 2);
	exit(err);
}

void 	ft_ps_check_uniq(t_ps *ps)
{
	int 	*nb;
	int 	i;

	nb = ps->sort;
	i = ps->a->count;
	while (--i)
	{
		if (*nb == *(nb + 1))
			ft_ps_err(ps, 3);
		++nb;
	}
}

int 	ft_ps_ckeck_argv(t_ps *ps, int i, char **argv)
{
	char 	**args;
	char 	*arg;

	args = argv;
	while (i--)
	{
		if (!(**args == '-' || **args == '+' || ft_isdigit(**args)))
			ft_ps_err(ps, 1);
		arg = *args;
		++arg;
		while (*arg)
		{
			if (!ft_isdigit(*arg))
				ft_ps_err(ps, 2);
			++arg;
		}
		++args;
	}
	return (0);
}