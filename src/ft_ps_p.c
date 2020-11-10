#include "push_swap.h"

void	ft_ps_pa(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if(!ps->b_end)
		return ;
	c = ps->a_end;
	if ((prev = ps->b_end->prev))
		prev->next = NULL;
	ps->a_end = ps->b_end;
	ps->b_end = prev ? prev : NULL;
	ps->b = ps->b_end ? ps->b : NULL;
	if (c && (ps->a_end->prev = c))
		c->next = ps->a_end;
	else if (!c)
	{
		ps->a = ps->a_end;
		ps->a->prev = NULL;
	}
	if (ps->a_end)
		ps->a_end->next = NULL;
	if (!ps->b)
		ft_clear_line(102, 32, F_WHITE, B_BLUE);
	ft_print_sw(ps->b, 'b');
	ft_print_sw(ps->a, 'a');
}

void	ft_ps_pb(t_ps *ps)
{
	t_swap	*prev;
	t_swap	*c;

	if(!ps->a_end)
		return ;
	c = ps->b_end;
	if ((prev = ps->a_end->prev))
		prev->next = NULL;
	ps->b_end = ps->a_end;
	ps->a_end = prev ? prev : NULL;
	ps->a = ps->a_end ? ps->a : NULL;
	if (c && (ps->b_end->prev = c))
		c->next = ps->b_end;
	else if (!c)
	{
		ps->b = ps->b_end;
		ps->b->prev = NULL;
	}
	if (ps->b_end)
		ps->b_end->next = NULL;
	if (!ps->a)
		ft_clear_line(7, 32, F_WHITE, B_RED);
	ft_print_sw(ps->b, 'b');
	ft_print_sw(ps->a, 'a');
}
