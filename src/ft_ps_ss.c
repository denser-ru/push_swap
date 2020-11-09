#include "push_swap.h"

void	ft_ps_sa(t_ps *ps)
{
	t_swap	*next;
	t_swap	*c;
	
	c = ps->a;
	next = ps->a->next->next;
	ps->a = ps->a->next;
	ps->a->next = c;
	ps->a->prev = NULL;
	c->next = next;
	c->prev = ps->a;
	ft_print_nb(*(ps->a->next->nb), 30 - ps->count_a - 1, 'a');
	ft_print_nb(*(ps->a->nb), 30 - ps->count_a, 'a');	
}

