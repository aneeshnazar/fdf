/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 21:24:36 by anazar            #+#    #+#             */
/*   Updated: 2017/11/30 16:35:15 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

int		valid_file(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (str[len - 1] == 'f' &&
		str[len - 2] == 'd' &&
		str[len - 3] == 'f' &&
		str[len - 4] == '.')
		return (1);
	else
		return (0);
}

int		get_num_lines(int argc, char **argv)
{
	int		fd;
	int		count;
	char	*buf;

	if (argc != 2)
		ft_error("Incorrect number of parameters!");
	if (!valid_file(argv[1]))
		ft_error("Invalid filename!");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("file error!");
	count = 0;
	while (get_next_line(fd, &buf))
	{
		ft_strdel(&buf);
		++count;
	}
	return (count);
}
