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
	GOTOXY(27, F_HEIGHT + 3);
	usleep(s * 2);
}

void	ft_ps_nb_list_reset2(t_ps *ps, int *nb, int i)
{
	t_swap	*new;

//	ft_lst_swaps_del(ps->a->start);
//	ft_lst_swaps_del(ps->b->start);
	ps->a->start = ft_lstsw_new(nb++);
	ps->b->start = NULL;
	ps->b->end = NULL;
	new = ps->a->start;
	while (i < (int)ps->nb_size)
	{
		new->next = ft_lstsw_add(new, nb++);
		new = new->next;
		++i;
	}
	ps->a->end = new;
	ft_print_bg(ps->f);
	ft_print_sw(ps->a->start, 'a');
}

void 	ft_ps_print_stacks(t_ps *ps, t_list *cmd, int s)
{
	if (cmd)
	{
		ft_do_cmd(ps, cmd->content);
		ft_put_cmd(ps, cmd, 1, 255);
	}
//	GOTOXY(54, F_HEIGHT - 2);
//	ft_printf("\e[38;5;251mps->i: %-3d", ps->i);
	GOTOXY(27, F_HEIGHT + 3);
	read(0, ps->sort, 1);
	usleep(s);
}
void 	ft_ps_move(t_ps *ps, int s)
{
	t_list	**cmdroot;
	t_list	*cmd;
	int i;
	int j;

	s = s ? s * 1000 : ps->s;
	if (ps->gui)
		ft_ps_nb_list_reset2(ps, ps->nb, 1);
	else
		ft_ps_nb_list_reset(ps, s);
	cmdroot = &(ps->cmds);
	if (!(cmd = *cmdroot))
		return ;
	j = ps->count + 1;
	ps->count = 1;
	usleep(ps->s);
	while (j--)
	{
		i = 0;
		while (cmd && i++ < j)
			cmd = cmd->next;
		ft_ps_print_stacks(ps, cmd, s);
		cmd = *cmdroot;
	}
	ps->cmds = *cmdroot;
}