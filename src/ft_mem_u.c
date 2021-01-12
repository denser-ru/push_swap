/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:31:07 by cayako            #+#    #+#             */
/*   Updated: 2020/11/16 19:17:06 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void		ft_lst_swaps_del(t_swap *sw)
{
	if (sw->next)
		ft_lst_swaps_del(sw->next);
	sw->next = NULL;
	free(sw);
}

void			ft_memfree(t_ps *ps)
{
	if (ps->a->start)
		ft_lst_swaps_del(ps->a->start);
	ft_lstdel(&(ps->cmds), ft_lstdelcontent);
	free(ps->nb);
	ps->nb = NULL;
	free(ps->sort);
	ps->sort = NULL;
	free(ps->sort2);
	ps->sort2 = NULL;
}

void 			ft_ps_print_sw(t_list *cmd)
{
	while (cmd)
	{
		ft_putnstr(cmd->content, cmd->content_size);
		ft_putchar('\n');
		cmd = cmd->next;
	}
}

void			ft_ps_end(t_ps *ps)
{
	if (FT_DEV)
	{
		GOTOXY(54, F_HEIGHT + 3);
		ft_putchar('\n');
	}
	else if (!ps->gui)
		ft_ps_print_sw(ps->cmds);
	else
		ft_ps_move(ps, ps->s);
	ft_memfree(ps);
	exit (0);
}
