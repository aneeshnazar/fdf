/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_wf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 19:41:19 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 19:00:35 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

static void	pexit(void)
{
	perror("The following error occurred:");
	exit(0);
}

static int	ft_intlen(int num)
{
	int		i;

	i = num <= 0 ? 1 : 0;
	while (num)
	{
		++i;
		num /= 10;
	}
	return (i);
}

static int	*str_to_ia(char *str, int *len)
{
	int		i;
	int		*out;

	i = 0;
	*len = ft_countif_f(str, &ft_iswhitespace);
	out = (int *)ft_memalloc(sizeof(int) * *len);
	while (*str)
	{
		if (!ft_iswhitespace(*str))
		{
			out[i] = ft_atoi(str);
			str += ft_intlen(out[i]);
			++i;
		}
		else
			++str;
	}
	return (out);
}

static void	fill_table(t_wf *wf, char **str)
{
	int		i;
	int		len;

	i = 0;
	wf->table = (int **)ft_memalloc(sizeof(int *) * wf->height);
	wf->width = 0;
	while (i < wf->height)
	{
		wf->table[i] = str_to_ia(str[i], &len);
		wf->width = ft_max(len, wf->width);
		++i;
	}
	wf->size = wf->height * wf->width;
	wf->points = (t_ri_coord *)ft_memalloc(sizeof(t_ri_coord) * wf->size);
	wf->flat_points = (t_ri_coord *)ft_memalloc(sizeof(t_ri_coord) * wf->size);
}

t_wf		init_wf(int fd, int num_lines)
{
	t_wf	out;
	char	**str;
	int		check;
	int		i;

	str = (char **)ft_memalloc(sizeof(char *) * num_lines);
	i = 0;
	while (i < num_lines)
	{
		check = get_next_line(fd, &str[i]);
		if (check == -1)
			pexit();
		++i;
	}
	out.height = num_lines;
	out.win_width = 1000;
	out.win_height = 1000;
	out.midpoint = init_coord(out.win_width / 2, out.win_height / 2);
	fill_table(&out, str);
	out.mlx = mlx_init();
	out.win = mlx_new_window(out.mlx, out.win_width, out.win_height, "fdf");
	out.zoom = init_img(&out);
	out.margin = out.zoom / 2;
	out.mid = init_coord(out.width * out.zoom / 2, out.height * out.zoom / 2);
	return (out);
}
