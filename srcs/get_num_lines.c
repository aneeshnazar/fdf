/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_num_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 21:24:36 by anazar            #+#    #+#             */
/*   Updated: 2017/09/08 21:26:25 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		get_num_lines(char *str)
{
	int		fd;
	int		count;
	char	*buf;

	fd = open(str, O_RDONLY);
	count = 0;
	while (get_next_line(fd, &buf))
	{
		ft_strdel(&buf);
		++count;
	}
	return (count);
}
