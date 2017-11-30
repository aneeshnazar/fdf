/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tricoord.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 18:02:36 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 17:08:17 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

t_color		init_color(int r, int g, int b)
{
	t_color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	color.val = r << 16 | g << 8 | b;
	return (color);
}

t_ri_coord	init_tricoord(int x, int y, int z, unsigned int color)
{
	t_ri_coord	t;

	t.x = x;
	t.y = y;
	t.z = z;
//	t.color = flag > 0 ? init_color(0x32, 0xcd, 0x32) : init_color(0xFF, 0xFF, 0xFF);
/*	if (flag > 0)
		t.color = init_color(0x32,0xcd,0x32);
	else 
		t.color = init_color(0xFF, 0xFF, 0xFF);*/
	t.color = color;
	return (t);
}
