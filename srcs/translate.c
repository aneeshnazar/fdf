/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 20:15:21 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 20:15:38 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	translate(int x_mov, int y_mov, t_wf *wf)
{
	int	i;

	i = 0;
	while (i < wf->size)
	{
		wf->flat_points[i] = init_tricoord(FPX + x_mov,
				FPY + y_mov, FPZ, FP_COL);
		++i;
	}
}
