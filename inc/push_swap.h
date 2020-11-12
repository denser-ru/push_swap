/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:53:30 by cayako            #+#    #+#             */
/*   Updated: 2020/11/12 18:34:39 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include "term.h"
# include "ft_frame.h"

typedef struct		s_swap
{
	int				*nb;
	int				chunk;
	struct s_swap	*prev;
	struct s_swap	*next;
}					t_swap;

typedef struct		s_ps
{
	int				*nb;
	int				*sort;
	t_swap			*a;
	t_swap			*a_end;
	t_swap			*b;
	t_swap			*b_end;
	t_swap			prev;
	int 			count_a;
	int 			count_b;
	int				i;
	int				chunk;
	t_list			*cmds;
	int 			count;
}					t_ps;

t_swap				*ft_lstsw_new(int *nb);
t_swap				*ft_lstsw_add(t_swap *prev, int *nb);
void				ft_frame(t_frame *f);
t_frame 			*ft_get_param1(t_frame *f, int x, int y, int w);
t_frame 			*ft_get_param2(t_frame *f, int h, int fg, int bg);
int 				ft_ft_read_args(t_ps *ps, int argc, char **argv);
int 				ft_ft_read_in(t_ps *ps, char *buf);

void				ft_print_bg(t_frame *f);
void				ft_print_sw(t_swap *sw, char c);
void				ft_print_nb(int nb, int y, char c);
void				ft_clear_line(int x, int y, int fg, int bg);

int					ft_add_cmd(t_ps *ps, char *buf);
void			 	ft_put_cmd(t_ps *ps, int i, int c);
int					*ft_sort_nb_arr(int *nb, size_t size);
void				ft_ps_sa(t_ps *ps);
void				ft_ps_sb(t_ps *ps);
void				ft_ps_pa(t_ps *ps);
void				ft_ps_pb(t_ps *ps);
void				ft_ps_ra(t_ps *ps);
void				ft_ps_rb(t_ps *ps);
void				ft_ps_rra(t_ps *ps);
void				ft_ps_rrb(t_ps *ps);
void				ft_ps_rrr(t_ps *ps);
void				ft_ps_rr(t_ps *ps);
void				ft_ps_ss(t_ps *ps);

int					ft_push_swap(t_ps *ps, int mediana, int s);

#endif
