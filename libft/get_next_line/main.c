/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cayako <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:17:50 by cayako            #+#    #+#             */
/*   Updated: 2019/10/26 01:34:03 by cayako           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void	get_next_one(int fd, char *line, int result)
{
	if (fd == -1)
	{
		ft_putstr("error opening: ");
		ft_putendl(path);
		return (1);
	}
	while ((result = get_next_line(fd, &line)))
	{
		if (result == -1)
		{
			ft_putstr("error getting next line in: ");
			ft_putendl(path);
			return (1);
		}
		ft_putstr(line);
		ft_putendl(" - 1");
		free(line);
	}
}

int		get_next(char *path)
{
	int		fd;
	char	*line;
	int		result;

	fd = open(path, O_RDONLY);
	get_next_one(fd, line, result);
	if (!result)
	{
		ft_putstr(line);
		ft_putendl(" - 0");
		free(line);
	}
	if (close(fd) == -1)
	{
		ft_putstr("error closing file: ");
		ft_putendl(path);
		return (1);
	}
	return (0);
}

int		main(int ac, char **av)
{
	int i;

	i = 1;
	if (ac < 2)
		ft_putendl("usage: printfile source_files");
	while (i < ac)
	{
		if (get_next(av[i++]))
			return (1);
	}
	return (0);
}
