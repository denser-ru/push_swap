//
// Created by Cheyenne Ayako on 12/26/20.
//

#include "push_swap.h"

void	    ft_ps_err(t_ps *ps, int err)
{
	(void)err;
	ft_memfree(ps);
	ft_putendl_fd("Error", 2);
	exit(err);
}

void 	    ft_ps_check_uniq(t_ps *ps)
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

static void  ft_ps_ckeck_arg(t_ps *ps, char *arg, int n)
{
    (void)n;
    if (ft_strlen(arg) > 11)
        ft_ps_err(ps, 3);
    if ((*arg == '-' && ft_atoi(arg) > 0) || (ft_isdigit(*arg) && ft_atoi(arg) < 0))
        ft_ps_err(ps, 4);
    if ((*arg == '-' && !ft_isdigit(*(arg + 1))) || (*arg == '+' && !ft_isdigit(*(arg + 1))))
        ft_ps_err(ps, 5);
}

int 	    ft_ps_ckeck_argv(t_ps *ps, int i, char **argv)
{
	char 	**args;
	char 	*arg;

	args = argv;
	while (i--)
	{
		if (!(**args == '-' || **args == '+' || ft_isdigit(**args)))
			ft_ps_err(ps, 1);
		arg = *args;
        ft_ps_ckeck_arg(ps, arg, 0);
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