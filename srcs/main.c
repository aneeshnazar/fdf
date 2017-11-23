/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 23:58:56 by anazar            #+#    #+#             */
/*   Updated: 2017/11/22 21:11:28 by anazar           ###   ########.fr       */
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
		place_at(&wf, wf.flat_points[i].x, wf.flat_points[i].y);
}

//void	apply_zoom(t_wf *wf, int x, int y)
void	apply_zoom(t_wf *wf)
{
	for (int i = 0; i < wf->height * wf->width; ++i)
	{
		wf->flat_points[i].x = (wf->points[i].x) * wf->zoom;
		wf->flat_points[i].y = (wf->points[i].y) * wf->zoom;
	}
//	(void)x;
//	(void)y;
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
			++i;
			++x;
		}
		++y;
	}
	apply_zoom(wf);
}

static int        close_window(t_wf *view)
{
	mlx_destroy_window(view->mlx, view->win);
	exit(0);
	return (1);
}

int		translate(int x_mov, int y_mov, t_wf *wf)
{
	for (int i = 0; i < wf->height * wf->width; ++i)
		wf->flat_points[i] = init_coord(wf->flat_points[i].x + x_mov, wf->flat_points[i].y + y_mov);
//	wf->midpoint.x += x_mov;
//	wf->midpoint.y += y_mov;
	return (0);
}

void	draw_axis(t_wf *param, t_bres inp)
{
	int		it;
	
	it = 0;
	while (it <= inp.dx)
	{
		place_at(param, inp.p1.x, inp.p1.y);
		while (inp.err >= 0)
		{
			if (inp.swap)
				inp.p1.x += inp.sx;
			else
			{
				inp.p1.y += inp.sy;
				inp.err -= 2 * inp.dx;
			}
		}
		if (inp.swap)
			inp.p1.y += inp.sy;
		else
			inp.p1.x += inp.sx;
		inp.err += 2 * inp.dy;
		++it;
	}
}

void	draw_axes(t_wf *param)
{
	t_bres	inp1;
	t_bres	inp2;

	inp1 = init_bres(init_coord((param->win_width) / 2, 0), init_coord((param->win_width) / 2, param->win_height - 1));
	inp2 = init_bres(init_coord(0, (param->win_height) / 2), init_coord(param->win_width - 1, (param->win_height) / 2));
	draw_axis(param, inp1);
	draw_axis(param, inp2);
}
void	redraw(t_wf *param)
{
	init_img(param);
	draw_wf(*param);
//	draw_axes(param); 
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	mlx_destroy_image(param->mlx, param->img);
}

void	recalc_mp(t_wf *param)
{
	t_coord	ltc;
	t_coord	rbc;
	t_coord	mid;

	rbc = param->flat_points[param->width * param->height - 1];
	ltc = param->flat_points[0];
	mid = init_coord(ltc.x + (rbc.x - ltc.x) / 2, ltc.y + (rbc.y - ltc.y) / 2);
	param->mid = mid;
}

void	center(t_wf *param)
{
	int	x_mov;
	int	y_mov;

	apply_zoom(param);
	recalc_mp(param);
	x_mov = param->midpoint.x - param->mid.x;
	y_mov = param->midpoint.y - param->mid.y;
	translate(x_mov, y_mov, param);
}

int		zoom(int button, t_wf *param)
{
	if (button == 5)
		param->zoom -= 1;
	else if (button == 4)
		param->zoom += 1;
	center(param);
	return (1);
}

int		mouse_event(int button, int x, int y, t_wf *param)
{
	(void) x;
	(void) y;
	zoom(button, param);
	redraw(param);
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
	x_mov = (keycode == 123 ? -wf->zoom : x_mov);
	x_mov = (keycode == 124 ? wf->zoom : x_mov);
	y_mov = (keycode == 126 ? -wf->zoom : y_mov);
	y_mov = (keycode == 125 ? wf->zoom : y_mov);
	translate(x_mov, y_mov, wf);
	wf->midpoint.x += x_mov;
	wf->midpoint.y += y_mov;
	redraw(wf);
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
	/*	draw_wf(wf);
		mlx_put_image_to_window(wf.mlx, wf.win, wf.img, 0, 0);
		mlx_destroy_image(wf.mlx, wf.img);*/
		center(&wf);
		redraw(&wf);
		mlx_mouse_hook(wf.win, mouse_event, &wf);
		mlx_key_hook(wf.win, key_event, &wf);
		mlx_hook(wf.win, 17, 0, close_window, &wf);
		mlx_loop(wf.mlx);
	}
}
