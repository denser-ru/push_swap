/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_frame.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 01:23:50 by cayako            #+#    #+#             */
/*   Updated: 2020/11/06 02:52:50 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FRAME_H
# define FT_FRAME_H

typedef struct	s_frame
{
	int			x;
	int			y;
	int			w;
	int			h;
	int			fg;
	int			bg;
}				t_frame;

#endif
