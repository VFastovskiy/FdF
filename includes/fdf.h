/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:47:56 by kcharlet          #+#    #+#             */
/*   Updated: 2020/01/30 21:26:43 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define _USE_MATH_DEFINES
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <math.h>
# include "mlx.h"
# define USAGE1 "usage:\t./fillit input_file\n"
# define USAGE2 "usage:\t./invalid file\n"

typedef struct	s_coord
{
	int		x;
	int		y;
}				t_coord;

typedef struct	s_dot
{
	t_coord		def;
	int			def_z;
	t_coord		rot;
	t_coord		iso;
	t_coord		par;
}				t_dot;

typedef struct	s_fdf
{
	void		*mlx;
	void		*window;
	t_coord		f_size;
	t_coord		w_size;
	t_dot		**dot_lst;
	t_coord		cur_coord;
	int			mode;
	int			scale;
	t_coord		shift;
	int			rotate;
}				t_fdf;

typedef struct	s_for_dl
{
	int		dx;
	int		dy;
	int		sign_x;
	int		sign_y;
	int		error;
	int		error2;
	int		color;
}				t_for_dl;

int				ft_open_file_and_count_field_size(char *av, t_coord *size);
int				**file_to_matrix(int fd, t_coord size);
t_dot			**file_to_dot_list(int fd, t_coord size);
t_dot			*ft_new_dot(int i, int j, int z, t_coord f_size);
void			make_iso_and_par(t_dot *dot);
void			rotation(t_fdf *fdf, int t);
void			draw_line(t_fdf *fdf, t_dot *dot1, t_dot *dot2);
void			draw_map(t_fdf *fdf);
void			free_int_matrix(int ***m, int num_of_strings);
void			free_fdf(t_fdf **fdf);
void			free_dot_list(t_dot ***list, int num_of_elements);
int				ft_reset_map(t_fdf *fdf);
void			ft_error(void);
void			print_tulbar(t_fdf *fdf);
int				ft_shift_map(int key, t_fdf *fdf);

#endif
