/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:30:17 by cayako            #+#    #+#             */
/*   Updated: 2021/02/10 16:30:24 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_ps_err(t_ps *ps, int err)
{
	(void)err;
	ft_memfree(ps);
	ft_putendl_fd("Error", 2);
	exit(err);
}

void		ft_ps_check_uniq(t_ps *ps)
{
	int		*nb;
	int		i;

	nb = ps->sort;
	i = ps->a->count;
	while (--i)
	{
		if (*nb == *(nb + 1))
			ft_ps_err(ps, 6);
		++nb;
	}
}

static void	ft_ps_ckeck_arg(t_ps *ps, char *arg, size_t n)
{
	n = !n ? ft_strlen(arg) : n;
	if (n > 11)
		ft_ps_err(ps, 3);
	if ((*arg == '-' && ft_atoi_n(arg, n) > 0) ||
			(ft_isdigit(*arg) && ft_atoi_n(arg, n) < 0))
		ft_ps_err(ps, 4);
	if ((*arg == '-' && !ft_isdigit(*(arg + 1))) ||
			(*arg == '+' && !ft_isdigit(*(arg + 1))))
		ft_ps_err(ps, 5);
}

int			ft_ps_ckeck_argv(t_ps *ps, int i, char **argv, size_t n)
{
	char	**args;
	char	*arg;
	size_t	nn;

	args = argv;
	while (*argv && i--)
	{
		if (!(**args == '-' || **args == '+' || ft_isdigit(**args)))
			ft_ps_err(ps, 1);
		arg = *args;
		if (!(*arg))
			return (0);
		nn = !n ? ft_strlen(arg) : n;
		ft_ps_ckeck_arg(ps, arg, nn);
		++arg;
		while (--nn && *arg)
		{
			if (!ft_isdigit(*arg))
				ft_ps_err(ps, 2);
			++arg;
		}
		++args;
	}
	return (0);
}
