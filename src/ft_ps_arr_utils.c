/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_arr_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:55:23 by cayako            #+#    #+#             */
/*   Updated: 2021/02/10 16:55:28 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_check_lstnbr(t_ps *ps, t_list *nblst)
{
	while (nblst)
	{
		ft_ps_ckeck_argv(ps, 1, (char**)(&nblst->content));
		nblst = nblst->next;
	}
}

static int		*ft_atr_to_nbarr(t_ps *ps, int *nb, int argc, char *arg)
{
	t_list	*nblst;
	t_list	*lst;
	int		len;
	int		*sort;

	nblst = ft_lststrsplit(arg, ' ');
	ft_check_lstnbr(ps, nblst);
	lst = nblst;
	len = ft_lstsize(nblst);
	ps->nb = (int*)malloc(sizeof(int) * (--argc + len));
	nb = ps->nb + (argc + len - 1);
	ps->sort = (int*)malloc(sizeof(int) * (argc + len));
	ps->a->count = argc + len;
	sort = ps->sort + (len - 1);
	while (lst)
	{
		*(nb) = ft_atoi((char*)lst->content);
		*(sort--) = *(nb--);
		lst = lst->next;
	}
	ft_lstdel(&nblst, ft_lstdelcontent);
	return (ps->nb);
}

int				*ft_create_nbarr(t_ps *ps, int argc, char **argv)
{
	int		*nb;
	int		*sort;

	nb = ft_atr_to_nbarr(ps, NULL, --argc, *argv);
	ps->sort2 = (int*)malloc(sizeof(int) * ps->a->count);
	ps->nb_size = ps->a->count;
	nb += argc - 2;
	sort = ps->sort + ps->a->count - 1;
	while (--argc)
	{
		*(nb) = ft_atoi(*(++argv));
		*(sort--) = *(nb--);
	}
	return (ps->nb);
}
