/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 21:24:36 by anazar            #+#    #+#             */
/*   Updated: 2017/11/30 19:52:11 by anazar           ###   ########.fr       */
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

int		valid_line(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (!ft_is_in(str[i], "0123456789 \t-"))
			return (0);
		if (ft_is_in(str[i], "0123456789"))
			++len;
		else if (str[i] == '-' && !ft_is_in(str[i + 1], "0123456789"))
			return (0);
		else if (str[i] == '-' && i > 0 && str[i - 1] != ' ')
			return (0);
		else
		{
			if (len >= 10)
				return (0);
			len = 0;
		}
		++i;
	}
	return (len < 10);
}

int		init_validation(int argc, char **argv, int *n_numbers)
{
	int		fd;
	char	*buf;

	if (argc != 2)
		ft_error("Incorrect number of parameters!");
	if (!valid_file(argv[1]))
		ft_error("Invalid filename!");
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		ft_error("file error!");
	get_next_line(fd, &buf);
	*n_numbers = ft_countif_f(buf, &ft_iswhitespace);
	if (!buf)
		ft_error("Empty File!");
	if (!valid_line(buf))
		ft_error("Invalid line!");
	ft_strdel(&buf);
	return (fd);
}

int		get_num_lines(int argc, char **argv)
{
	int		fd;
	int		count;
	int		n_numbers;
	char	*buf;

	fd = init_validation(argc, argv, &n_numbers);
	count = 1;
	while (get_next_line(fd, &buf))
	{
		if (!valid_line(buf))
			ft_error("Invalid characters!");
		if (n_numbers != ft_countif_f(buf, &ft_iswhitespace))
			ft_error("Invalid number of columns!");
		ft_strdel(&buf);
		++count;
	}
	close(fd);
	if (n_numbers == 1 && count == 1)
		ft_error("You can't draw a wireframe with one point!");
	return (count);
}
