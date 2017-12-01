/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 23:58:56 by anazar            #+#    #+#             */
/*   Updated: 2017/11/30 16:19:41 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	init_points(t_wf *wf)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	x = 0;
	y = 0;
	while (y < wf->height)
	{
		x = 0;
		while (x < wf->width)
		{
			wf->points[i] = init_tricoord(x, y,
					wf->table[y][x],
					wf->table[y][x] <= 0 ? 0x32CD32 : 0xFFFFFF);
			++i;
			++x;
		}
		++y;
	}
	apply_zoom(wf);
}

int		hooks(t_wf *wf)
{
	mlx_do_key_autorepeatoff(wf->mlx);
	mlx_hook(wf->win, 2, 0, key_event, wf);
	mlx_hook(wf->win, 4, 0, mouse_event, wf);
	mlx_hook(wf->win, 5, 0, un_mouse_event, wf);
	mlx_hook(wf->win, 6, 0, motion_event, wf);
	mlx_hook(wf->win, 17, 0, close_window, wf);
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_wf	wf;
	int		num_lines;

	num_lines = get_num_lines(argc, argv);
	fd = open(argv[1], O_RDONLY);
	wf = init_wf(fd, num_lines);
	init_points(&wf);
	wf.lclicked = 0;
	wf.rclicked = 0;
	wf.rotation = init_tricoord(21, 0, 42, 0);
	center(&wf);
	redraw(&wf);
	mlx_loop_hook(wf.mlx, hooks, &wf);
	mlx_loop(wf.mlx);
}
