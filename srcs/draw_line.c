/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 00:00:40 by anazar            #+#    #+#             */
/*   Updated: 2017/11/27 20:39:21 by anazar           ###   ########.fr       */
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

void	draw_line(t_wf *wf, int i, int j)
{
	t_bres	inp;
	int		it;

	inp = init_bres(wf->flat_points[i], wf->flat_points[j]);
	it = 0;
	while (it <= inp.dx)
	{
//		place_at(wf, wf->midpoint.x + inp.p1.x, wf->midpoint.y + inp.p1.y);
		place_at(wf, inp.p1.x, inp.p1.y);
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
