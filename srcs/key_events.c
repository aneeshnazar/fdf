/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:26:16 by anazar            #+#    #+#             */
/*   Updated: 2017/11/30 17:04:10 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int		key_event(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int		close_window(t_wf *view)
{
	mlx_destroy_window(view->mlx, view->win);
	exit(0);
	return (1);
}

int		expose_event(t_wf *wf)
{
	wf->draw = 1;
	return (0);
}
