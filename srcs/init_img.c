/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 18:56:53 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 18:57:10 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fdf.h>

int			init_img(t_wf *wf)
{
	int		img_w;
	int		img_h;

	img_w = wf->win_width;
	img_h = wf->win_height;
	wf->img = mlx_new_image(wf->mlx, img_w, img_h);
	wf->pic = (int *)mlx_get_data_addr(wf->img,
			&wf->bits,
			&wf->s_line,
			&wf->endian);
	return (img_w / (wf->width + 1));
}
