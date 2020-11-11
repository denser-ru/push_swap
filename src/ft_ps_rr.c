#include "push_swap.h"

void	ft_ps_ra(t_ps *ps)
{
	t_swap	*end;

	if(!ps->a_end || !ps->a || ps->a == ps->a_end)
		return ;
	end = ps->a_end->prev;
	end->next = NULL;
	ps->a_end->next = ps->a;
	ps->a_end->prev = NULL;
	ps->a->prev = ps->a_end;
	ps->a_end = end;
	ps->a = ps->a->prev;
	ft_print_sw(ps->a, 'a');
}

void	ft_ps_rb(t_ps *ps)
{
	t_swap	*end;

	if(!ps->b_end || !ps->b || ps->b == ps->b_end)
		return ;
	end = ps->b_end->prev;
	end->next = NULL;
	ps->b_end->next = ps->b;
	ps->b_end->prev = NULL;
	ps->b->prev = ps->b_end;
	ps->b_end = end;
	ps->b = ps->b->prev;
	ft_print_sw(ps->b, 'b');
}

void	ft_ps_rra(t_ps *ps)
{
	t_swap	*start;

	if(!ps->a_end || !ps->a || ps->a == ps->a_end)
		return ;
	start = ps->a->next;
	start->prev = NULL;
	ps->a->prev = ps->a_end;
	ps->a->next = NULL;
	ps->a_end->next = ps->a;
	ps->a = start;
	ps->a_end = ps->a_end->next;
	ft_print_sw(ps->a, 'a');
}

void	ft_ps_rrb(t_ps *ps)
{
	t_swap	*start;

	if(!ps->b_end || !ps->b || ps->b == ps->b_end)
		return ;
	start = ps->b->next;
	start->prev = NULL;
	ps->b->prev = ps->b_end;
	ps->b->next = NULL;
	ps->b_end->next = ps->b;
	ps->b = start;
	ps->b_end = ps->b_end->next;
	ft_print_sw(ps->b, 'b');
}

void	ft_ps_rrr(t_ps *ps)
{
	ft_ps_rra(ps);
	ft_ps_rrb(ps);
}