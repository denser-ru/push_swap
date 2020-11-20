//
// ft_ps_chunk.c Created by Cheyenne Ayako on 11/18/20.
//

#include "push_swap.h"

void			ft_ps_check_chunk_sort(t_ps *ps)
{
	if (ps->b->end && *(ps->b->end->nb) == ps->sort2[ps->end]
		&& (size_t)ps->end <= ps->nb_size)
	{
		ps->b->end->chunk = 0;
		ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		ft_add_cmd(ps, "ra\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		++ps->end;
	}
}