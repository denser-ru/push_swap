//
// ft_ps_chunk.c Created by Cheyenne Ayako on 11/18/20.
//

#include "push_swap.h"

void			ft_ps_check_chunk_sort(t_ps *ps, int ab, int mediana, int s)
{
	if (!ab && ps->b->end && *(ps->b->end->nb) == *(ps->sort2 + ps->end)
		&& (size_t)ps->end <= ps->nb_size)
	{
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; end:%-3d", mediana, *(ps->sort2 + ps->end));
		ps->st->end->chunk = 0;
		++ps->end;
	}
}