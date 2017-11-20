/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bres.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 15:59:28 by anazar            #+#    #+#             */
/*   Updated: 2017/09/07 23:58:35 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_bres		init_bres(t_coord p1, t_coord p2)
{
	t_bres	ret;
	int		tmp;

	ret.p1 = min_c(p1, p2);
	ret.p2 = max_c(p1, p2);
	ret.dx = iabs(p2.x - p1.x);
	ret.dy = iabs(p2.y - p1.y);
	ret.sx = sign(p2.x - p1.x);
	ret.sy = sign(p2.y - p1.y);
	ret.swap = 0;
	if (ret.dy > ret.dx)
	{
		tmp = ret.dx;
		ret.dx = ret.dy;
		ret.dy = tmp;
		ret.swap = 1;
	}
	ret.err = 2 * ret.dy - ret.dx;
	return (ret);
}
