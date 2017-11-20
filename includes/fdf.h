/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 23:52:38 by anazar            #+#    #+#             */
/*   Updated: 2017/11/18 20:52:05 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define LINE_COLOR	0x00FF00FF

# include <mlx.h>
# include <libft.h>
# include <fcntl.h>

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_ri_coord
{
	double		x;
	double		y;
	double		z;
}				t_ri_coord;

typedef struct	s_bres
{
	t_coord		p1;
	t_coord		p2;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			swap;
	int			err;
}				t_bres;

typedef struct	s_wf
{
	void		*mlx;
	void		*win;
	void		*img;
	int			endian;
	int			s_line;
	int			bits;
	int			width;
	int			height;
	int			zoom;
	int			margin;
	int			**table;
	int			*pic;
	int			win_width;
	int			win_height;
	t_coord		midpoint;
	t_coord		mid;
	t_ri_coord	*points;
	t_coord		*flat_points;
}				t_wf;

t_coord			max_c(t_coord p1, t_coord p2);
t_coord			min_c(t_coord p1, t_coord p2);
int				sign(int num);
int				iabs(int num);
t_bres			init_bres(t_coord p1, t_coord p2);
t_coord			init_coord(int x, int y);
t_ri_coord		init_tricoord(int x, int y, int z);
//void			draw_line(void *mlx, void *win, t_coord p1, t_coord p2);
void			draw_line(t_wf *wf, int i, int j);
int				init_img(t_wf *wf);
int				get_num_lines(char *str);
t_wf			init_wf(int fd, int num_lines);
void			place_at(t_wf *wf, int x, int y);
#endif
