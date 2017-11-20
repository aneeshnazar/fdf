/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 23:58:56 by anazar            #+#    #+#             */
/*   Updated: 2017/11/19 13:47:09 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	place_at(t_wf *wf, int x, int y)
{
	int	pos;

	pos = x + (y * wf->s_line / 4);
	if (pos >= 0 && pos < wf->win_height * wf->win_width)
		if (x >= 0 && x < wf->win_width)
			if (y >= 0 && y < wf->win_height)
				wf->pic[pos] = LINE_COLOR;
}

void	draw_wf(t_wf wf)
{
	for (int i = 0; i < wf.height * wf.width; ++i)
		//place_at(&wf, wf.flat_points[i].x, wf.flat_points[i].y);
		place_at(&wf, wf.midpoint.x + wf.flat_points[i].x, wf.midpoint.y + wf.flat_points[i].y);
/*	for (int j = 0; j < wf.height * wf.width; ++j)
	{
		if (j + 1 < wf.width * (wf.flat_points[j].y + 1))
			draw_line(&wf, j, j + 1);
		if (j + wf.width < wf.height * wf.width)
			draw_line(&wf, j, j + wf.width);
	}*/
}

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
			wf->points[i] = init_tricoord(x, y, wf->table[y][x]);
			wf->flat_points[i] = init_coord((x + 1) * wf->zoom - wf->midpoint.x, (y + 1) * wf->zoom - wf->midpoint.y);
			ft_putnbr(wf->flat_points[i].x);
			ft_putchar(':');
			ft_putnbr(wf->flat_points[i].y);
			ft_putchar('\n');
			++i;
			++x;
		}
		++y;
	}
}

static int        close_window(t_wf *view)
{
	mlx_destroy_window(view->mlx, view->win);
	exit(0);
	return (1);
}

int		zoom(int button, int x, int y, t_wf *param)
{
	(void) x;
	(void) y;
	if (button == 5)
		param->zoom -= 1;
	else if (button == 4)
		param->zoom += 1;
	init_points(param);
	init_img(param);
	draw_wf(*param);
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	mlx_destroy_image(param->mlx, param->img);
	return (1);
}

int		translate(int x_mov, int y_mov, t_wf *wf)
{
	for (int i = 0; i < wf->height * wf->width; ++i)
		wf->flat_points[i] = init_coord(wf->flat_points[i].x + x_mov, wf->flat_points[i].y + y_mov);
	init_img(wf);
	draw_wf(*wf);
	mlx_put_image_to_window(wf->mlx, wf->win, wf->img, 0, 0);
	mlx_destroy_image(wf->mlx, wf->img);
	return (0);
}

int		key_event(int keycode, t_wf *wf)
{
	int	x_mov;
	int	y_mov;

	x_mov = 0;
	y_mov = 0;
	if (keycode == 53)
		exit(0);
	x_mov = (keycode == 123 ? -wf->zoom/10 : x_mov);
	x_mov = (keycode == 124 ? wf->zoom/10 : x_mov);
	y_mov = (keycode == 126 ? -wf->zoom/10 : y_mov);
	y_mov = (keycode == 125 ? wf->zoom/10 : y_mov);
	translate(x_mov, y_mov, wf);
	return (0);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_wf	wf;
	int		num_lines;

	if (argc == 2)
	{
		num_lines = get_num_lines(argv[1]);
		fd = open(argv[1], O_RDONLY);
		wf = init_wf(fd, num_lines);
		init_points(&wf);
		draw_wf(wf);
		mlx_put_image_to_window(wf.mlx, wf.win, wf.img, 0, 0);
		mlx_destroy_image(wf.mlx, wf.img);
		mlx_mouse_hook(wf.win, zoom, &wf);
		mlx_key_hook(wf.win, key_event, &wf);
		mlx_hook(wf.win, 17, 0, close_window, &wf);
		mlx_loop(wf.mlx);
	}
}
