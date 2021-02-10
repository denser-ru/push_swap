/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:53:30 by cayako            #+#    #+#             */
/*   Updated: 2020/12/02 23:12:20 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include "libft.h"
# include "ft_printf.h"
# include "term.h"
# include "ft_frame.h"

# define F_HEIGHT		52
# define FT_DEV			0

typedef struct		s_swap
{
	int				*nb;
	int				l;
	int				s;
	int				chunk;
	struct s_swap	*prev;
	struct s_swap	*next;
}					t_swap;

typedef struct		s_stack
{
	t_swap			*start;
	t_swap			*end;
	int				count;
}					t_stack;

typedef struct		s_ps
{
	int				*nb;
	size_t			nb_size;
	int				*sort;
	int				*sort2;
	int				end;
	t_stack			*a;
	t_stack			*b;
	t_stack			*st;
	int				i;
	t_list			*cmds;
	int				count;
	int				chunk;
	int				chunk_count;
	int				cur_chunk;
	int				s;
	t_frame			*f;
	int				gui;
	int				wait;
	int				fix;
	int				checker;
}					t_ps;

void				ft_init_ps(t_ps *ps, int argc, char **argv);
void				ft_ps_dev(t_ps *ps, int m, char *dev);

t_swap				*ft_lstsw_new(int *nb);
t_swap				*ft_lstsw_add(t_swap *prev, int *nb);
void				ft_frame(t_frame *f);
void				ft_ps_move(t_ps *ps, int s);
t_frame				*ft_get_param1(t_frame *f, int x, int y, int w);
t_frame				*ft_get_param2(t_frame *f, int h, int fg, int bg);
int					ft_ps_read_in(t_ps *ps, char *buf);
int					ft_ps_read_in_txt(t_ps *ps, char *buf);
int					ft_ps_read_stdin(t_ps *ps, char *buf);

void				ft_print_bg(t_frame *f);
void				ft_print_sw(t_swap *sw, char c);
void				ft_clear_line(int x, int y, int fg, int bg);

int					ft_add_cmd(t_ps *ps, char *buf);
int					ft_add_cmd_in(t_ps *ps, char *buf);
void				ft_put_cmd(t_ps *ps, t_list *cmd, int i, int c);
void				ft_do_cmd(t_ps *ps, char *buf);
int					*ft_sort_nb_arr(int *nb, size_t size);
int					*ft_create_nbarr(t_ps *ps, int argc, char **argv);
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

int					ft_push_swap(t_ps *ps, int s);
void				ft_ps_step_f(t_ps *ps, int m, int ab);
void				ft_ps_step_f2(t_ps *ps, int m, int ab);
void				ft_ps_step_f3(t_ps *ps, int m, int ab);
void				ft_ps_swaps_split(t_ps *ps);
int					ft_ps_chunk_count(t_swap *sw, int *sort, int chunk, int i);
int					ft_ps_chunk_count_up(t_swap *sw, int *sort, int i);
void				ft_ps_check_chunk(t_ps *ps, t_swap *sw, int m, char *dev);
void				ft_ps_check_duble(t_ps *ps);
int					ft_ps_sw_sort(t_ps *ps, t_swap *sw, size_t i, int *sort);
int					ft_lst_issorted(t_ps *ps);
int					ft_ps_get_chunk(t_swap *sw, int chunk);
void				ft_ps_end(t_ps *ps);
int					ft_ps_mediana_chunk_count(t_swap *sw, int m, int chunk,
												int ab);

int					ft_ps_fix(t_ps *ps, t_list *cmd, int i);
void				ft_lst_swaps_del(t_swap *sw);

int					ft_ps_ckeck_argv(t_ps *ps, int i, char **argv, size_t n);
void				ft_ps_check_uniq(t_ps *ps);
void				ft_memfree(t_ps *ps);

#endif
