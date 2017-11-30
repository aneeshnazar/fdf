/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 23:58:56 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 17:48:51 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>
#define PI 3.141592653589793
#define RAD(x) (x * PI / 180)

#include <stdio.h> //remove

void	place_at(t_wf *wf, int x, int y, unsigned int color)
{
	int	pos;

	pos = x + (y * wf->s_line / 4);
	if (pos >= 0 && pos < wf->win_height * wf->win_width)
		if ((x >= 0 && x < wf->win_width) && (y >= 0 && y < wf->win_height))
			wf->pic[pos] = color;
}

void	draw_wf(t_wf *wf)
{
	int	x;
	int	y;
	int i;

	y = 0;
	i = 0;
	while (y < wf->height)
	{
		x = 0;
		while (x < wf->width)
		{
			if (x + 1 < wf->width)
				draw_line(wf, i, i + 1);
			if (y + 1 < wf->height)
				draw_line(wf, i, i + wf->width);
			++x;
			++i;
		}
		++y;
	}
//	for (int i = 0; i < wf->height * wf->width; ++i)
	//	place_at(&wf, wf.flat_points[i].x, wf.flat_points[i].y);
}

void	rotate(t_wf *wf, int x, int z)
{
	wf->rotation.x += (double)x;
	wf->rotation.z += (double)z;
}

//void	apply_zoom(t_wf *wf, int x, int y)
void	apply_zoom(t_wf *wf)
{
	double	angle_x;
	double	angle_z;

	angle_x = wf->rotation.x;
	angle_z = wf->rotation.z;
	for (int i = 0; i < wf->height * wf->width; ++i)
	{
		//wf->flat_points[i].x = (wf->points[i].x * cos(angle_z * PI / 180) - wf->points[i].y * sin(angle_z * PI / 180)) * wf->zoom;
		wf->flat_points[i].x = (wf->points[i].x * cos(RAD(angle_z)) - wf->points[i].y * sin(RAD(angle_z))) * wf->zoom;
		//wf->flat_points[i].y = (wf->points[i].x * sin(angle_z * PI / 180) * cos(angle_x * PI / 180) + wf->points[i].y * cos(angle_z * PI / 180) * cos(angle_x * PI / 180) - wf->points[i].z * sin(angle_x * PI / 180)) * wf->zoom;
		wf->flat_points[i].y = (wf->points[i].x * sin(RAD(angle_z)) * cos(RAD(angle_x)) + wf->points[i].y * cos(RAD(angle_z)) * cos(RAD(angle_x)) - wf->points[i].z * sin(RAD(angle_x)) / 4) * wf->zoom;
		//wf->flat_points[i].z = (wf->points[i].x * sin(angle_x * PI / 180) * sin(angle_z * PI / 180) + wf->points[i].y * sin(angle_x * PI / 180) * cos(angle_z * PI / 180) + wf->points[i].z * cos(angle_x * PI / 180)) * wf->zoom; 
		wf->flat_points[i].z = (wf->points[i].x * sin(RAD(angle_x)) * sin(RAD(angle_z)) + wf->points[i].y * sin(RAD(angle_x)) * cos(RAD(angle_z)) + wf->points[i].z * cos(RAD(angle_x)) / 4) * wf->zoom;
		wf->flat_points[i].color = wf->points[i].color;
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
			wf->points[i] = init_tricoord(x, y, wf->table[y][x], wf->table[y][x] <= 0 ? 0x32CD32 : 0xFFFFFF);
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
		wf->flat_points[i] = init_tricoord(wf->flat_points[i].x + x_mov, wf->flat_points[i].y + y_mov, wf->flat_points[i].z, wf->flat_points[i].color);
		//wf->flat_points[i] = init_coord(wf->flat_points[i].x + x_mov, wf->flat_points[i].y + y_mov);
//	wf->midpoint.x += x_mov;
//	wf->midpoint.y += y_mov;
	return (0);
}
/*
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
*/
/*
void	draw_axes(t_wf *param)
{
	t_bres	inp1;
	t_bres	inp2;

	inp1 = init_bres(init_tricoord((param->win_width) / 2, 0, 0), init_tricoord((param->win_width) / 2, param->win_height - 1, 0));
	//inp1 = init_bres(init_coord((param->win_width) / 2, 0), init_coord((param->win_width) / 2, param->win_height - 1));
	inp2 = init_bres(init_tricoord(0, (param->win_height) / 2, 0), init_tricoord(param->win_width - 1, (param->win_height) / 2, 0));
	//inp2 = init_bres(init_coord(0, (param->win_height) / 2), init_coord(param->win_width - 1, (param->win_height) / 2));
	draw_axis(param, inp1);
	draw_axis(param, inp2);
}
*/

void	redraw(t_wf *param)
{
	init_img(param);
	draw_wf(param);
//	draw_axes(param); 
	mlx_put_image_to_window(param->mlx, param->win, param->img, 0, 0);
	mlx_destroy_image(param->mlx, param->img);
}

void	recalc_mp(t_wf *param)
{
	//t_coord	ltc;
	t_ri_coord	ltc;
	//t_coord	rbc;
	t_ri_coord	rbc;
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
	if (button == 1)
	{
		param->lclicked = 1;
		param->offset = init_coord(param->midpoint.x - x, param->midpoint.y - y);
	}
	else if (button == 2)
		param->rclicked = 1;
	param->last_mouse_pos = init_coord(x, y);
	zoom(button, param);
	redraw(param);
	return (0);
}

int		motion_event(int x, int y, t_wf *param)
{
	int	x_rot;
	int	z_rot;

	x_rot = 0;
	z_rot = 0;
	if (x < param->win_width && y < param->win_height)
	{
		if (param->rclicked)
		{
			z_rot = (x - param->last_mouse_pos.x) / 2; 
			x_rot = (param->last_mouse_pos.y - y) / 2;
		}
		else if (param->lclicked)
			param->midpoint = init_coord(x + param->offset.x, y + param->offset.y);
		param->last_mouse_pos = init_coord(x, y);
	}
	rotate(param, x_rot, z_rot);
	zoom(0, param);
	redraw(param);
	return (0);
}

int		un_mouse_event(int button, int x, int y, t_wf *param)
{
	if (button == 1)
		param->lclicked = 0;
	else if (button == 2)
		param->rclicked = 0;
	param->last_mouse_pos = init_coord(x, y);
	zoom(button, param);
	redraw(param);
	return (0);
}
/*
int		key_event(int keycode, t_wf *wf)
{
	int	x_mov;
	int	y_mov;
	int	x_rot;
	int	z_rot;

	x_mov = 0;
	y_mov = 0;
	x_rot = 0;
	z_rot = 0;
	if (keycode == 53)
		exit(0);
	x_mov = (keycode == 123 ? -wf->zoom : x_mov);
	x_mov = (keycode == 124 ? wf->zoom : x_mov);
	y_mov = (keycode == 126 ? -wf->zoom : y_mov);
	y_mov = (keycode == 125 ? wf->zoom : y_mov);
	x_rot = (keycode == 13 ? 1 : x_rot);
	x_rot = (keycode == 1 ? -1 : x_rot);
	z_rot = (keycode == 0 ? 1 : z_rot);
	z_rot = (keycode == 2 ? -1 : z_rot);
	rotate(wf, x_rot, z_rot);
	wf->midpoint.x += x_mov;
	wf->midpoint.y += y_mov;
	center(wf);
	redraw(wf);
	return (0);
}
*/
/*
int		zoom_in(int num, int x, int y, t_wf *view)
{
	(void) num;
	(void) x;
	(void) y;
	view->zoom += 1;
	ft_putnbr(view->zoom);
	ft_putchar('\n');
center(view);
	redraw(view);
	return (0);
}

int		zoom_out(int num,int x, int y, t_wf *view)
{
	(void) num;
	(void) x;
	(void) y;
	view->zoom -= 1;
	ft_putnbr(view->zoom);
	ft_putchar('\n');
	center(view);
	redraw(view);
	return (0);
}
*/
int		key_event(int keycode)
{
	if (keycode == 53)
		exit (0);
	return (0);
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

	if (argc == 2)
	{
		num_lines = get_num_lines(argv[1]);
		fd = open(argv[1], O_RDONLY);
		wf = init_wf(fd, num_lines);
		init_points(&wf);
	/*	draw_wf(wf);
		mlx_put_image_to_window(wf.mlx, wf.win, wf.img, 0, 0);
		mlx_destroy_image(wf.mlx, wf.img);*/
		wf.lclicked = 0;
		wf.rclicked = 0;
		wf.rotation = init_tricoord(21,0,42,0);
		center(&wf);
		redraw(&wf);
//		mlx_mouse_hook(wf.win, mouse_event, &wf);
//		mlx_key_hook(wf.win, key_event, &wf);
//		mlx_loop_hook(wf.mlx, hooks, &wf);
		hooks(&wf);
		mlx_loop(wf.mlx);
	}
}
