#include "push_swap.h"

void	ft_ps_sa(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if(!ps->a_end || !ps->a_end->prev)
		return ;
	c = ps->a_end;
	prev = ps->a_end->prev->prev;
	ps->a_end = ps->a_end->prev;
	ps->a_end->prev = c;
	ps->a_end->next = NULL;
	c->prev = prev;
	if (prev)
		prev->next = c;
	else
		ps->a = c;
	c->next = ps->a_end;
	ft_print_sw(ps->a, 'a');
}

void	ft_ps_sb(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if(!ps->b_end || !ps->b_end->prev)
		return ;
	c = ps->b_end;
	prev = ps->b_end->prev->prev;
	ps->b_end = ps->b_end->prev;
	ps->b_end->prev = c;
	ps->b_end->next = NULL;
	c->prev = prev;
	if (prev)
		prev->next = c;
	else
		ps->b = c;
	c->next = ps->b_end;
	ft_print_sw(ps->b, 'b');
}

void	ft_ps_ss(t_ps *ps)
{
	ft_ps_sa(ps);
	ft_ps_sb(ps);
}

void	ft_ps_rr(t_ps *ps)
{
	ft_ps_ra(ps);
	ft_ps_rb(ps);
}