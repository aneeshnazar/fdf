/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 00:00:40 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 18:52:39 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

unsigned int	avg(unsigned int c1, unsigned int c2)
{
	t_color	new;

	new.r = (c1 / 0x10000 + c2 / 0x10000) / 2;
	new.g = ((c1 % 0x10000) / 0x100 + (c2 % 0x10000) / 0x100) / 2;
	new.b = (c1 % 0x100 + c2 % 0x100) / 2;
	new.val = new.r << 16 | new.g << 8 | new.b;
	return (new.val);
}

void			draw_line(t_wf *wf, int i, int j)
{
	t_bres	inp;
	int		it;

	inp = init_bres(wf->flat_points[i], wf->flat_points[j]);
	it = 0;
	while (it <= inp.dx)
	{
		place_at(wf, inp.p1.x, inp.p1.y, avg(inp.p1.color, inp.p2.color));
		while (inp.err > 0)
		{
			if (inp.swap)
				inp.p1.x += inp.sx;
			else
				inp.p1.y += inp.sy;
			inp.err -= 2 * inp.dx;
		}
		if (inp.swap)
			inp.p1.y += inp.sy;
		else
			inp.p1.x += inp.sx;
		inp.err += 2 * inp.dy;
		++it;
	}
}
