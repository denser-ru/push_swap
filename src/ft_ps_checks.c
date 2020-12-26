//
// Created by Cheyenne Ayako on 12/26/20.
//

#include "push_swap.h"

void	ft_ps_err(int err)
{
	(void)err;
	ft_putendl_fd("Error", 2);
	exit(err);
}

int 	ft_ps_ckeck_argv(int i, char **argv)
{
	char 	**args;
	char 	*arg;

	args = argv;
	while (--i)
	{
		if (!(**args == '-' || **args == '+' || ft_isdigit(**args)))
			ft_ps_err(1);
		arg = *args;
		++arg;
		while (*arg)
		{
			if (!ft_isdigit(*arg))
				ft_ps_err(2);
			++arg;
		}
		++args;
	}
	ft_putendl(*argv);
	return (3);
}