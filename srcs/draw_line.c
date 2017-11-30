/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 00:00:40 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 18:19:02 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

/*void	draw_line(void *mlx, void *win, t_coord p1, t_coord p2)
  {
  t_bres	inp;
  int		it;

  inp = init_bres(p1, p2);
  it = 0;
  while (it <= inp.dx)
  {
  mlx_pixel_put(mlx, win, inp.p1.x, inp.p1.y, LINE_COLOR);
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
  }*/

unsigned int	avg(unsigned int c1, unsigned int c2)
{
	t_color	new;

	new.r = (c1 / 0x10000 + c2 / 0x10000) / 2;
	new.g = ((c1 % 0x10000) / 0x100 + (c2 % 0x10000) / 0x100) / 2;
	new.b = (c1 % 0x100 + c2 % 0x100) / 2;
	new.val = new.r << 16 | new.g << 8 | new.b;
	return (new.val);
}

void	draw_line(t_wf *wf, int i, int j)
{
	t_bres	inp;
	int		it;

	inp = init_bres(wf->flat_points[i], wf->flat_points[j]);
	it = 0;
	while (it <= inp.dx)
	{
//		place_at(wf, wf->midpoint.x + inp.p1.x, wf->midpoint.y + inp.p1.y);
		place_at(wf, inp.p1.x, inp.p1.y, avg(inp.p1.color, inp.p2.color));
//		wf->pic[inp.p1.x + (inp.p1.y * wf->s_line / 4)] = LINE_COLOR;
//`		while (inp.err >= 0)
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
