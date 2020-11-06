/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:53:30 by cayako            #+#    #+#             */
/*   Updated: 2020/11/06 02:53:22 by cayako           ###   ########.fr       */
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
	struct s_swap	*next;
}					t_swap;

typedef struct		s_ps
{
	int				*nb;
	t_swap			*a;
	t_swap			*b;
	t_swap			*c;
	int				chunk;
}					t_ps;

t_swap				*ft_lstsw_new(int *nb);
t_swap				*ft_lstsw_add(t_swap *prev, int *nb);
void				ft_frame(char *param, int fg, int bg);

#endif
