//
// Created by Cheyenne Ayako on 1/28/21.
//

#include "push_swap.h"

static int      *ft_atr_to_nbarr(t_ps *ps, int *nb, int argc, char *arg)
{
    t_list *nblst;
    t_list  *lst;
    int     len;
    int		*sort;

    nblst = ft_lststrsplit(arg, ' ');
    lst = nblst;
    len = ft_lstsize(nblst);
    ps->nb = (int*)malloc(sizeof(int) * (--argc + len));
    nb = ps->nb + (len - 1);
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

static int		*ft_create_nbarr(t_ps *ps, int argc, char **argv)
{
	int		*nb;
	int		*sort;

	nb = ft_atr_to_nbarr(ps, NULL, --argc, *argv);
    ps->sort2 = (int*)malloc(sizeof(int) * ps->a->count);
	ps->nb_size = ps->a->count;
	nb += ps->a->count - 1;
	sort = ps->sort + ps->a->count - 1;
	while (--argc)
	{
		*(nb) = ft_atoi(*(++argv));
		*(sort--) = *(nb--);
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
		sw->s = i > 0 ? ps->sort2[i - 1] : ps->sort2[ps->a->count - 1];
		sw->l = i < ps->a->count - 1 ? ps->sort2[i + 1] : ps->sort2[0];
		++i;
		sw = ps->a->end;
	}
}

void		ft_init_ps(t_ps *ps, int argc, char **argv)
{
	t_swap	*new;
	int		*nb;

	ft_bzero(ps->a, sizeof(t_stack));
	ft_bzero(ps->b, sizeof(t_stack));
    nb = ft_create_nbarr(ps, argc--, argv);
//	ft_ps_ckeck_argv(ps, argc, argv + 1);
	ps->st = ps->a;
	ps->nb = nb;
	ft_sort_nb_arr(ps->sort, ps->a->count);
//	ft_ps_check_uniq(ps);
	ft_ps_cp_sort2(ps->sort2, ps->sort, ps->a->count);
	ps->sorted = ps->sort2;
	ps->end = ps->a->count - 1;
	ps->a->start = ft_lstsw_new(nb++);
	new = ps->a->start;
	ps->s = 300000;
	ps->cmds = (t_list*)NULL;
	argc = ps->a->count;
	while (--argc)
	{
		new->next = ft_lstsw_add(new, nb++);
		new = new->next;
	}
	ps->a->end = new;
	ft_ps_nb_link(ps, ps->a->end, 0);
}
