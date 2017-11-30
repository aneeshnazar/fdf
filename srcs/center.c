/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   center.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:57:47 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 20:17:10 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	recalc_mp(t_wf *wf)
{
	t_ri_coord	ltc;
	t_ri_coord	rbc;
	t_coord		mid;

	rbc = wf->flat_points[wf->width * wf->height - 1];
	ltc = wf->flat_points[0];
	mid = init_coord(ltc.x + (rbc.x - ltc.x) / 2, ltc.y + (rbc.y - ltc.y) / 2);
	wf->mid = mid;
}

void	center(t_wf *wf)
{
	int	x_mov;
	int	y_mov;

	apply_zoom(wf);
	recalc_mp(wf);
	x_mov = wf->midpoint.x - wf->mid.x;
	y_mov = wf->midpoint.y - wf->mid.y;
	translate(x_mov, y_mov, wf);
}
