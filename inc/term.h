/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <cayako@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 04:49:01 by cayako            #+#    #+#             */
/*   Updated: 2020/11/07 22:54:42 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TERM_H
# define FT_TERM_H

# define ESC "\033"

/*
** home() -  Move cursor to the indicated row, column (origin at 1,1)
** clrscr -  Clear the screen, move to (1,1)
*/
# define HOME()					ft_printf(ESC "[H");
# define CLRSRC()				ft_printf(ESC "[2J");
# define GOTOXY(x,y)			ft_printf(ESC "[%d;%dH", y, x);
# define VISIBLE_CURSOR()		ft_printf(ESC "[?251");

/* 
** Set Display Attribute Mode	<ESC>[{attr1};...;{attrn}m
*/
# define RESETCOLOR()			ft_printf(ESC "[0m")
# define SET_DISP_ATR(color)	ft_printf(ESC "[%dm",color)
# define SET_DISP_2ATR(fg, bg)	ft_printf(ESC "[%d;%dm",fg ,bg)

/*
** Format text
*/
# define RESET		0
# define BRIGHT		1
# define DIM		2
# define UNDERSCORE	3
# define BLINK		4
# define REVERSE	5
# define HIDDEN		6

/*
** Foreground Colours (text)
*/
# define F_BLACK	30
# define F_RED		31
# define F_GREEN	32
# define F_YELLOW	33
# define F_BLUE		34
# define F_MAGENTA	35
# define F_CYAN		36
# define F_WHITE	37

/*
** Background Colours
*/
# define B_BLACK	40
# define B_RED		41
# define B_GREEN	42
# define B_YELLOW	44
# define B_BLUE		44
# define B_MAGENTA	45
# define B_CYAN		46
# define B_WHITE	47

#endif
