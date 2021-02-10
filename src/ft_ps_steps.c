/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_steps.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:46:26 by cayako            #+#    #+#             */
/*   Updated: 2021/02/10 17:46:38 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		ft_ps_do_cmd(t_ps *ps, int ab, char *cmd1, char *cmd2)
{
	ft_add_cmd(ps, ab ? cmd1 : cmd2);
	ft_put_cmd(ps, ps->cmds, 0, 255);
}

void			ft_ps_step_f1(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->start && ps->st->start->chunk &&
		ps->st->start->chunk == ps->cur_chunk && ps->st->count > 1 &&
		((ab && *(ps->st->start->nb) < m) ||
		(!ab && *(ps->st->start->nb) >= m)))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f1.2");
		ft_ps_do_cmd(ps, ab, "rra\n", "rrb\n");
		ps->st->end->chunk = ab ? ps->chunk : 1;
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f1.2");
		ft_put_cmd(ps, ps->cmds, 0, 255);
	}
}

void			ft_ps_step_f(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->end && ps->st->end->chunk && ps->st->end->chunk ==
		ps->cur_chunk && ((ab && ps->st->count > 2 && *(ps->st->end->nb) < m) ||
		(!ab && *(ps->st->end->nb) > m)) &&
		((ab && ps->chunk_count > 1) || !ab))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f1.1");
		ps->st->end->chunk = ab ? ps->chunk : 1;
		if (!ps->st->end->chunk)
			break ;
		ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f1.1");
		ft_put_cmd(ps, ps->cmds, 0, 255);
	}
	ft_ps_step_f1(ps, m, ab);
}

void			ft_ps_step_f2(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->end && ps->st->end->chunk && ps->st->end->chunk ==
		ps->cur_chunk && ((ab && ps->chunk_count > 2) || !ab))
	{
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f2.1");
		if (((ab && *(ps->st->end->nb) >= m) || (!ab && *(ps->st->end->nb) <=
				m)) && ps->st->count > 1 && ps->chunk_count > 1)
			ft_ps_do_cmd(ps, ab, "ra\n", "rb\n");
		else if (ps->st->end->chunk && (!ab || (ab && ps->st->count > 1 &&
			ps->chunk_count > 1)))
		{
			ft_ps_check_chunk(ps, ps->a->start, m, "f2.2");
			ft_ps_check_duble(ps);
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start, m, "f2.2");
			ft_put_cmd(ps, ps->cmds, 0, 255);
		}
	}
}

void			ft_ps_step_f3(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->start && ((ab && ps->st->start->chunk &&
		*(ps->st->end->nb) >= m && ps->a->count > 2) ||
		(!ab && ps->b->start->chunk >= ps->b->end->chunk)))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start, m, "f3.1");
		if ((ab && ps->chunk_count < 3) || (ab && *(ps->a->start->nb) > m) ||
			(!ab && *(ps->b->start->nb) <= m))
		{
			if (!ps->st->start->chunk)
				break ;
			ft_ps_do_cmd(ps, ab, "rra\n", "rrb\n");
		}
		else if (ps->st->start->chunk)
		{
			ft_ps_check_chunk(ps, ps->a->start, m, "f3.2");
			if (!ps->st->start->chunk)
				break ;
			ft_ps_do_cmd(ps, ab, "rra\n", "rrb\n");
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_ps_do_cmd(ps, ab, "pb\n", "pa\n");
		}
	}
}
