/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:44:22 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 20:29:48 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

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
}

void	redraw(t_wf *wf)
{
	init_img(wf);
	draw_wf(wf);
	mlx_put_image_to_window(wf->mlx, wf->win, wf->img, 0, 0);
	mlx_destroy_image(wf->mlx, wf->img);
}
