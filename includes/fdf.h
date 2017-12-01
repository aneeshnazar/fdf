/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 23:52:38 by anazar            #+#    #+#             */
/*   Updated: 2017/11/30 16:19:12 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define LINE_COLOR	0x0032CD32
# define PI 3.141592653589793
# define RAD(x) (x * PI / 180)
# define FPX wf->flat_points[i].x
# define FPY wf->flat_points[i].y
# define FPZ wf->flat_points[i].z
# define FP_COL wf->flat_points[i].color
# define X wf->points[i].x
# define Y wf->points[i].y
# define Z wf->points[i].z
# include <mlx.h>
# include <libft.h>
# include <fcntl.h>
# include <math.h>

typedef struct		s_coord
{
	int				x;
	int				y;
}					t_coord;

typedef struct		s_color
{
	int				r;
	int				g;
	int				b;
	unsigned int	val;
}					t_color;

typedef struct		s_ri_coord
{
	double			x;
	double			y;
	double			z;
	unsigned int	color;
}					t_ri_coord;

typedef struct		s_bres
{
	t_ri_coord		p1;
	t_ri_coord		p2;
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				swap;
	int				err;
}					t_bres;

typedef struct		s_wf
{
	void			*mlx;
	void			*win;
	void			*img;
	int				endian;
	int				s_line;
	int				bits;
	int				width;
	int				height;
	int				zoom;
	int				margin;
	int				**table;
	int				*pic;
	int				size;
	int				win_width;
	int				win_height;
	int				lclicked;
	int				rclicked;
	t_coord			midpoint;
	t_coord			mid;
	t_coord			last_mouse_pos;
	t_coord			offset;
	t_ri_coord		*points;
	t_ri_coord		rotation;
	t_ri_coord		*flat_points;
}					t_wf;

int					sign(int num);
int					iabs(int num);
t_bres				init_bres(t_ri_coord p1, t_ri_coord p2);
t_coord				init_coord(int x, int y);
t_ri_coord			init_tricoord(int x, int y, int z, unsigned int color);
void				draw_line(t_wf *wf, int i, int j);
int					init_img(t_wf *wf);
int					get_num_lines(int argc, char **argv);
t_wf				init_wf(int fd, int num_lines);
void				place_at(t_wf *wf, int x, int y, unsigned int color);
t_color				init_color(int r, int g, int b);

int					mouse_event(int button, int x, int y, t_wf *wf);
int					motion_event(int x, int y, t_wf *wf);
int					un_mouse_event(int button, int x, int y, t_wf *wf);
int					key_event(int keycode);
int					close_window(t_wf *view);

void				redraw(t_wf *wf);
int					zoom(int button, t_wf *wf);
void				center(t_wf *wf);
void				apply_zoom(t_wf *wf);
void				translate(int x_mov, int y_mov, t_wf *wf);
#endif
