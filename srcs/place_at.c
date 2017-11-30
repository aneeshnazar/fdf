/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   place_at.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 19:17:02 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 19:17:12 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

void	place_at(t_wf *wf, int x, int y, unsigned int color)
{
	int	pos;

	pos = x + (y * wf->s_line / 4);
	if (pos >= 0 && pos < wf->win_height * wf->win_width)
		if ((x >= 0 && x < wf->win_width) && (y >= 0 && y < wf->win_height))
			wf->pic[pos] = color;
}
