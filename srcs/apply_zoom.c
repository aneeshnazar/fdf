/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_zoom.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:06:30 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 20:08:07 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	apply_zoom(t_wf *wf)
{
	double	angle_x;
	double	angle_z;
	int		i;

	angle_x = wf->rotation.x;
	angle_z = wf->rotation.z;
	i = 0;
	while (i < wf->size)
	{
		FPX = (X * cos(RAD(angle_z)) - Y * sin(RAD(angle_z))) * wf->zoom;
		FPY = (X * sin(RAD(angle_z)) * cos(RAD(angle_x)) +
				Y * cos(RAD(angle_z)) * cos(RAD(angle_x)) -
				Z * sin(RAD(angle_x)) / 4) * wf->zoom;
		FPZ = (X * sin(RAD(angle_x)) * sin(RAD(angle_z)) +
				Y * sin(RAD(angle_x)) * cos(RAD(angle_z)) +
				Z * cos(RAD(angle_x)) / 4) * wf->zoom;
		FP_COL = wf->points[i].color;
		++i;
	}
}
