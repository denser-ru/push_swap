/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_swap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/15 01:13:28 by cayako            #+#    #+#             */
/*   Updated: 2020/12/04 18:57:41 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int 			ft_ps_get_med(t_ps *ps, int d)
{
	return (ft_ps_sw_sort(ps, ps->st->end, d, ps->sort));
}

void 	ft_ps_check_2x2(t_ps *ps, t_swap *sw)
{
	if (!sw || !sw->prev || ps->st->count < 4 || sw->chunk != sw->prev->chunk)
		return ;
	sw = sw->prev->prev;
	if (sw->chunk != sw->prev->chunk || sw->next->chunk == sw->chunk ||
			!sw->prev->prev || sw->prev->prev->chunk == sw->chunk)
		return ;
	sw->next->chunk = sw->chunk;
	sw->next->next->chunk = sw->chunk;
}

int 			ft_ps_chunk_count_up(t_swap *sw, int *sort, int i)
{
	while (sw && sw->chunk)
	{
		sort[i] = *(sw->nb);
		sw = sw->prev;
		++i;
		if (sw && sw->next->chunk != sw->chunk)
			break ;
	}
	return (i);
}

void	ft_ps_check_chunk2(t_ps *ps, int ab)
{
	if (!ab && ps->chunk_count < 3)
	{
		if (ps->chunk_count == 2)
		{
			ft_add_cmd(ps, "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			read(0, ps->sort, 1);
		}
		ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
}

void	ft_ps_check_chunk(t_ps *ps, t_swap *sw)
{
//	ft_ps_check_2x2(ps, ps->st->end);
//	ft_ps_check_chunk2(ps, ps->st == ps->a);
	if (*(sw->nb) != ps->sort2[ps->a->count + ps->b->count - 1])
		return ;
	while (sw && sw->next)
	{
		if (*(sw->next->nb) == sw->s)
		{
			sw->chunk = 0;
			sw->next->chunk = 0;
		}
		else
			return ;
		sw = sw->next;
	}
}

void 	ft_ps_check_tail(t_ps *ps, int ab)
{
	if (!ab && ps->b->count == 2 && ps->b->end->s == *(ps->b->end->prev->nb))
	{
		ps->a->end->chunk = ps->b->end->chunk;
		ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
		read(0, ps->sort, 1);
		ps->a->end->chunk = ps->b->end->chunk;
		ft_add_cmd(ps, "pa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
		ft_lst_issorted(ps);
	}
	ft_ps_check_chunk(ps, ps->a->start);
	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
	if (ab && ps->a->end->chunk != ps->a->start->chunk && ps->chunk_count == 1)
	{
		ps->a->end->chunk = ps->b->end->chunk;
		ft_add_cmd(ps, "pb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
}

void 	ft_ps_check_duble(t_ps *ps)
{
	int		chunk;

	if (ps->a->end && ps->a->end->prev && ps->a->end->s == *(ps->a->end->prev->nb))
	{
		chunk = ps->a->end->prev->chunk;
		ps->a->end->prev->chunk = ps->a->end->chunk;
		ps->a->end->chunk = chunk;
		ft_add_cmd(ps, "sa\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
	if (ps->b->end && ps->b->end->prev && ps->b->end->l == *(ps->b->end->prev->nb) && ps->b->end->prev->chunk == ps->b->end->chunk)
	{
		chunk = ps->b->end->prev->chunk;
		ps->b->end->prev->chunk = ps->b->end->chunk;
		ps->b->end->chunk = chunk;
		ft_add_cmd(ps, "sb\n");
		ft_put_cmd(ps, ps->cmds, 1, 255);
		usleep(ps->s);
	}
//	ft_ps_check_tail(ps, ps->st == ps->a);
}

void	ft_ps_step_f5(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->b->end && ps->b->end->chunk && ps->b->end->chunk == ps->cur_chunk && !ab)
	{
		read(0, ps->sort, 1);
		ps->chunk_count = ft_ps_chunk_count_up(ps->b->end, ps->sort, 0);
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->b->start);
		if ((!ab && *(ps->b->end->nb) <= m) && ps->b->count > 1)
		{
			ft_add_cmd(ps, "rrb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f5.1)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
		else if (ps->b->end->chunk)
		{
			ft_ps_check_chunk(ps, ps->b->start);
			ft_ps_check_duble(ps);
			ps->st->start->chunk = 1;
			ft_add_cmd(ps, "rrb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f5.2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
			ft_add_cmd(ps, "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->b->start);
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f5.2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
		if (ps->chunk_count < 3)
			break ;
	}
}

void	ft_ps_step_f(t_ps *ps, int m, int ab)
{
		while (ps->i && ps->st->end && ps->st->end->chunk && ps->st->end->chunk == ps->cur_chunk &&
			((ab && ps->st->count > 2 && *(ps->st->end->nb) < m) || (!ab && *(ps->st->end->nb) > m)) && ((ab && ps->chunk_count > 1) || !ab))
		{
			if (ps->count > FT_DEV_STOP)
				read(0, ps->sort, 1);
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start);
			ps->st->end->chunk = ab ? ps->chunk : 1;
			if (!ps->st->end->chunk)
				break ;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start);
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.1)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
			ft_ps_check_chunk(ps, ps->a->start);
		}
		while (ps->i && ps->st->start && ps->st->start->chunk && ps->st->start->chunk == ps->cur_chunk && ps->st->count > 1 && ((ab && *(ps->st->start->nb) < m) || (!ab && *(ps->st->start->nb) >= m)))
		{
			if (ps->count > FT_DEV_STOP)
				read(0, ps->sort, 1);
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start);
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			usleep(ps->s);
			if (ps->count > FT_DEV_STOP)
				read(0, ps->sort, 1);
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start);
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f1.2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
}


void	ft_ps_step_f2(t_ps *ps, int m, int ab)
{
//	if (ab && ps->chunk_count < 3 && ps->a->end->chunk && !ps->a->start->chunk)
//		return ;
	while (ps->i && ps->st->end && ps->st->end->chunk && ps->st->end->chunk == ps->cur_chunk && ((ab && ps->chunk_count > 2) || !ab))
	{
		if (ps->count > FT_DEV_STOP)
			read(0, ps->sort, 1);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start);
		if (((ab && *(ps->st->end->nb) >= m) || (!ab && *(ps->st->end->nb) <= m)) && ps->st->count > 1 && ps->chunk_count > 1)
		{
//			if (!ps->st->end->chunk || ps->st->end->chunk != ps->cur_chunk)
//				break ;
			ft_add_cmd(ps, ab ? "ra\n" : "rb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2.1)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
		else if (ps->st->end->chunk)
		{
			ft_ps_check_chunk(ps, ps->a->start);
			ft_ps_check_duble(ps);
//			if (!ps->st->end->chunk || ps->st->end->chunk != ps->cur_chunk || (ab && ps->chunk_count < 3))
//				break ;
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_ps_check_duble(ps);
			ft_ps_check_chunk(ps, ps->a->start);
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f2.2)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
//		if (ab && ps->chunk_count < 3)
//			break ;
	}
}

void	ft_ps_step_f3(t_ps *ps, int m, int ab)
{
	while (ps->i && ps->st->start && ((ab && ps->st->start->chunk && *(ps->st->end->nb) >= m &&
		ps->a->count > 2) || (!ab && ps->b->start->chunk >= ps->b->end->chunk)))
	{
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f3.0)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
		if (ps->count > FT_DEV_STOP)
			read(0, ps->sort, 1);
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->st->start);
		if ((ab && ps->chunk_count < 3) || (ab && *(ps->a->start->nb) > m) || (!ab && *(ps->b->start->nb) <= m))
		{
			if (!ps->st->start->chunk)
				break ;
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f3.1)ps->i: %-3d; ab: %-3c; ch:%-2d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
		else if (ps->st->start->chunk)
		{
			ft_ps_check_chunk(ps, ps->a->start);
			if (!ps->st->start->chunk)
				break ;
			ft_add_cmd(ps, ab ? "rra\n" : "rrb\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f3.2)ps->i: %-3d; ab: %-3c; ch:%-3d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
			if (ps->count > FT_DEV_STOP)
				read(0, ps->sort, 1);
			ps->st->end->chunk = ab ? ps->chunk : 1;
			ft_add_cmd(ps, ab ? "pb\n" : "pa\n");
			ft_put_cmd(ps, ps->cmds, 1, 255);
			GOTOXY(54, 30);
			ft_printf("\e[38;5;251mмедиана: %-3d; (f3.2)ps->i: %-3d; ab: %-3c; ch:%-3d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
			usleep(ps->s);
		}
	}
}

void	ft_ps_swap_ab2(t_ps *ps, int m)
{
	ps->st = ps->b;
	while (!ft_lst_issorted(ps))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start);
		m = ft_ps_get_med(ps, 2);
		++ps->chunk;
		if (ps->count > FT_DEV_STOP)
			read(0, ps->sort, 1);
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f2  )ps->i: %-3d; ab: %-3c; ch:%-3d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_check_duble(ps);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		if (ps->st->count && (ps->st->start->chunk > ps->st->end->chunk || ps->st->start->chunk == 1))
		{
			ft_ps_check_duble(ps);
			ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
			ft_ps_step_f3(ps, m, ps->st == ps->a);
		}
//		ps->cur_chunk = ft_ps_get_chunk(ps->st->end, 0);
//		ps->chunk_count = ft_ps_chunk_count(ps->st->end, ps->sort, ps->cur_chunk, 0);
//		if ((ps->st == ps->a && ps->chunk_count < 3 && !ps->a->start->chunk) || (ps->st == ps->b && !ps->i))
		if ((ps->st == ps->a && ps->chunk_count < 3 && !ps->a->start->chunk) || (ps->st == ps->b && (ps->chunk_count > 2 || !ps->chunk_count) && ft_ps_chunk_count(ps->st->end, ps->sort, ps->cur_chunk, 0)))
		{
//			GOTOXY(44, 30);
//			ft_printf("\e[38;5;251mмедиана: %-3d; (>< )ps->i: %-3d; ab: %-3c; ch:%-3d с_ch:%-3d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count, ps->cur_chunk);
//			if (ps->count > FT_DEV_STOP)
//				read(0, ps->sort, 1);
			ps->st = ps->st == ps->a ? ps->b : ps->a;
//			GOTOXY(54, 30);
//			ft_printf("\e[38;5;251mмедиана: %-3d; (>< )ps->i: %-3d; ab: %-3c; ch:%-3d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
//			if (ps->count > FT_DEV_STOP)
//				read(0, ps->sort, 1);
		}
//		if (ps->st == ps->a && ps->b->end)
//		{
////			ps->chunk = ps->b->end->chunk;
//			ps->chunk = ft_ps_get_chunk(ps->b->end, 0) - 1;
//		}
		ps->chunk_count = ps->st->end ? ft_ps_chunk_count(ps->st->end, ps->sort, ps->st->end->chunk, 0) : 0;
//		if (ps->chunk_count < 4)
//			sleep(1);
	}
//	ft_ps_check_duble(ps);
//	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
//	ft_ps_step_f3(ps, m, ps->st == ps->a);
}

void	ft_ps_swap_ab(t_ps *ps, int m)
{
	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
	while (ps->a->count > 2 && (ps->st->end->chunk || ps->st->start->chunk))
	{
		ft_ps_check_duble(ps);
		ft_ps_check_chunk(ps, ps->a->start);
		m = ft_ps_get_med(ps, 2);
//		if (ps->chunk_count < 3)
//			break ;
		++ps->chunk;
		GOTOXY(54, 30);
		ft_printf("\e[38;5;251mмедиана: %-3d; (f1  )ps->i: %-3d; ab: %-3c; ch:%-3d", m, ps->i, ps->st == ps->a ? 'a' : 'b', ps->chunk_count);
		ft_ps_step_f(ps, m, ps->st == ps->a);
		ft_ps_step_f2(ps, m, ps->st == ps->a);
		ft_ps_check_duble(ps);
		ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
		ft_ps_step_f3(ps, m, ps->st == ps->a);
		ps->chunk_count = ft_ps_chunk_count(ps->st->end, ps->sort, ps->st->end->chunk, 0);
	}
//	ft_ps_end(ps);
//	ft_ps_check_duble(ps);
//	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
//	ft_ps_step_f3(ps, m, ps->st == ps->a);
//	ft_ps_check_duble(ps);
//	ps->chunk_count = ft_ps_chunk_count_up(ps->st->end, ps->sort, 0);
//	ft_ps_step_f2(ps, m, ps->st == ps->a);
//	ps->a->start->chunk = 0;
//	ps->a->end->chunk = 0;
	ps->st = ps->b;
	ft_ps_swap_ab2(ps, m);
}

int				ft_push_swap(t_ps *ps, int m, int s)
{
	ps->s *= s;
	++ps->chunk;
	ft_ps_swap_ab(ps, 0);

	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mмедиана: %-3d; (f0)ps->i: %-3d; ab: %-3c", m, ps->i, ps->st == ps->a ? 'a' : 'b');

	GOTOXY(54, 37);
	return (0);
}
