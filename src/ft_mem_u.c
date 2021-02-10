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

void			ft_lst_swaps_del(t_swap *sw)
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
	if (ps->b->start)
		ft_lst_swaps_del(ps->b->start);
	ft_lstdel(&(ps->cmds), ft_lstdelcontent);
	free(ps->nb);
	ps->nb = NULL;
	free(ps->sort);
	ps->sort = NULL;
	free(ps->sort2);
	ps->sort2 = NULL;
}

void			ft_ps_print_sw(t_list *cmd)
{
	size_t	i;
	size_t	j;
	t_list	*root;

	i = ft_lstsize(cmd);
	root = cmd;
	while (i--)
	{
		j = i;
		cmd = root;
		while (j--)
			cmd = cmd->next;
		ft_putnstr(cmd->content, cmd->content_size);
		ft_putchar('\n');
		cmd = cmd->next;
	}
}

void			ft_ps_end(t_ps *ps)
{
	if (FT_DEV && !ps->checker)
	{
		GOTOXY(54, F_HEIGHT + 3);
		ft_putchar('\n');
	}
	else if (!ps->gui && !ps->checker)
		ft_ps_print_sw(ps->cmds);
	else if (!FT_DEV && ps->gui && !ps->checker)
		ft_ps_move(ps, ps->s);
	if (ps->checker)
		ft_printf("OK\n");
	ft_memfree(ps);
	exit(0);
}

void			ft_ps_dev(t_ps *ps, int m, char *dev)
{
	GOTOXY(44, 30);
	SET_DISP_2ATR(F_WHITE, B_BLACK);
	ft_printf("\e[38;5;251mмедиана: %-3d; (%s)ps->i: %-3d; ab: %-3c",
				m, dev, ps->i, ps->st == ps->a ? 'a' : 'b');
	GOTOXY(54, F_HEIGHT + 3);
	usleep(ps->s);
}
