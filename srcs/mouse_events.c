/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:38:04 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 20:28:30 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	rotate(t_wf *wf, int x, int z)
{
	wf->rotation.x += (double)x;
	wf->rotation.z += (double)z;
}

int		mouse_event(int button, int x, int y, t_wf *wf)
{
	if (button == 1)
	{
		wf->lclicked = 1;
		wf->offset = init_coord(wf->midpoint.x - x, wf->midpoint.y - y);
	}
	else if (button == 2)
		wf->rclicked = 1;
	wf->last_mouse_pos = init_coord(x, y);
	zoom(button, wf);
	redraw(wf);
	return (0);
}

int		motion_event(int x, int y, t_wf *wf)
{
	int	x_rot;
	int	z_rot;

	x_rot = 0;
	z_rot = 0;
	if (x < wf->win_width && y < wf->win_height)
	{
		if (wf->rclicked)
		{
			z_rot = (x - wf->last_mouse_pos.x) / 2;
			x_rot = (wf->last_mouse_pos.y - y) / 2;
		}
		else if (wf->lclicked)
			wf->midpoint = init_coord(x + wf->offset.x, y + wf->offset.y);
		wf->last_mouse_pos = init_coord(x, y);
	}
	rotate(wf, x_rot, z_rot);
	zoom(0, wf);
	redraw(wf);
	return (0);
}

int		un_mouse_event(int button, int x, int y, t_wf *wf)
{
	if (button == 1)
		wf->lclicked = 0;
	else if (button == 2)
		wf->rclicked = 0;
	wf->last_mouse_pos = init_coord(x, y);
	zoom(button, wf);
	redraw(wf);
	return (0);
}
