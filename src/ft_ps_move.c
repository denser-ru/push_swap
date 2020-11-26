/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ps_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:37:56 by cayako            #+#    #+#             */
/*   Updated: 2020/11/20 17:38:04 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_ps_ab_change(t_ps *ps)
{
	ps->a->start = ps->b->start;
	ps->a->end = ps->b->end;
	ps->b->start = NULL;
	ps->b->end = NULL;
}

void 	ft_ps_swaps_split(t_ps *ps)
{
	ps->a->end->next = ps->b->start;
	ps->b->start->prev = ps->a->end;
	ps->a->end = ps->b->end;
	ps->b->start = NULL;
	ps->b->end = NULL;
}

void	ft_ps_nb_list_reset(t_ps *ps, int s)
{
	t_swap	*sw;
	int 	*nb;

	nb = ps->nb;
	if (ps->a->start)
	{

		if (ps->b->start)
			ft_ps_swaps_split(ps);
	}
	else
		ft_ps_ab_change(ps);
	sw = ps->a->start;
	while (sw)
	{
		sw->nb = nb++;
		sw = sw->next;
	}
	ft_print_bg(ps->f);
	ft_print_sw(ps->a->start, 'a');
	ft_print_sw(ps->b->start, 'b');
	GOTOXY(27, 35);
	usleep(s * 2);
}

void 	ft_ps_print_stacks(t_ps *ps, t_list *cmd, int s)
{
	ft_do_cmd(ps, cmd->content);
	ft_put_cmd(ps, cmd, 1, 255);
	GOTOXY(54, 30);
	ft_printf("\e[38;5;251mps->i: %-3d", ps->i);
	GOTOXY(27, 35);
	usleep(s);
}

void 	ft_ps_move(t_ps *ps, int s)
{
	t_list	**cmdroot;
	t_list	*cmd;
	int i;
	int j;

	s = s ? s * 1000 : ps->s;
	ft_ps_nb_list_reset(ps, s);
	cmdroot = &(ps->cmds);
	if (!(cmd = *cmdroot))
		return;
	j = ps->count;
	ps->count = 0;
	usleep(ps->s);
	while (j--)
	{
		i = 0;
		while (cmd && ++i < j)
			cmd = cmd->next;
		ft_ps_print_stacks(ps, cmd, s);
		cmd = *cmdroot;
	}
	ps->cmds = *cmdroot;
}