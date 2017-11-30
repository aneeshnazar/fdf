/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anazar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/06 23:52:38 by anazar            #+#    #+#             */
/*   Updated: 2017/11/29 17:09:21 by anazar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define LINE_COLOR	0x0032CD32
# define DBG_COORD(c) ft_putchar('('); ft_putnbr(c.x); ft_putchar(','); ft_putnbr(c.y); ft_putchar(','); ft_putnbr(c.z); ft_putchar(')'); ft_putchar('\n'); 

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

//t_coord			max_c(t_coord p1, t_coord p2);
//t_ri_coord			max_c(t_ri_coord p1, t_ri_coord p2);
//t_coord			min_c(t_coord p1, t_coord p2);
//t_ri_coord			min_c(t_ri_coord p1, t_ri_coord p2);
int					sign(int num);
int					iabs(int num);
//t_bres			init_bres(t_coord p1, t_coord p2);
t_bres				init_bres(t_ri_coord p1, t_ri_coord p2);
t_coord				init_coord(int x, int y);
//t_ri_coord			init_tricoord(int x, int y, int z, t_color color);
t_ri_coord			init_tricoord(int x, int y, int z, unsigned int color);
//void			draw_line(void *mlx, void *win, t_coord p1, t_coord p2);
void				draw_line(t_wf *wf, int i, int j);
int					init_img(t_wf *wf);
int					get_num_lines(char *str);
t_wf				init_wf(int fd, int num_lines);
//void				place_at(t_wf *wf, int x, int y, t_color color);
void				place_at(t_wf *wf, int x, int y, unsigned int color);
t_color				init_color(int r, int g, int b);
#endif
