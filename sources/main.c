/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:08:02 by rczarfun          #+#    #+#             */
/*   Updated: 2020/01/30 21:11:05 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord		win_size(t_coord f_size)
{
	t_coord w_size;

	w_size.x = sqrt((pow(f_size.x, 2) + pow(f_size.y, 2)) * 2500) + 200;
	w_size.y = sqrt((pow(f_size.x, 2) + pow(f_size.y, 2)) * 2500) + 200;
	w_size.x = (w_size.x > 1600) ? 1600 : w_size.x;
	w_size.y = (w_size.y > 900) ? 900 : w_size.y;
	return (w_size);
}

int			key_hook(int key, t_fdf *fdf)
{
	if (key == 124)
		rotation(fdf, fdf->rotate += 1);
	if (key == 123)
		rotation(fdf, fdf->rotate -= 1);
	if (key == 46)
		fdf->mode = !(fdf->mode);
	if (key == 0 || key == 1 || key == 2 || key == 13)
		ft_shift_map(key, fdf);
	if (key == 126)
		fdf->scale += 1;
	if (key == 125 && fdf->scale > 1)
		fdf->scale -= 1;
	if (key == 15)
		ft_reset_map(fdf);
	mlx_clear_window(fdf->mlx, fdf->window);
	draw_map(fdf);
	print_tulbar(fdf);
	if (key == 53)
		exit(1);
	return (0);
}

int			ft_reset_map(t_fdf *fdf)
{
	rotation(fdf, fdf->rotate = 0);
	fdf->shift.x = fdf->w_size.x / 2;
	fdf->shift.y = fdf->w_size.y / 2;
	fdf->scale = 8;
	return (0);
}

int			ft_shift_map(int key, t_fdf *fdf)
{
	if (key == 0)
		(fdf->shift.x) -= 300;
	if (key == 1)
		(fdf->shift.y) += 300;
	if (key == 2)
		(fdf->shift.x) += 300;
	if (key == 13)
		(fdf->shift.y) -= 300;
	return (0);
}

int			main(int ac, char **av)
{
	t_fdf	*fdf;
	int		fd;

	if (ac != 2)
		ft_error();
	if (!(fdf = (t_fdf*)ft_memalloc(sizeof(t_fdf))))
		return (0);
	fd = ft_open_file_and_count_field_size(av[1], &(fdf->f_size));
	if (fd < 0)
		ft_error();
	fdf->dot_lst = file_to_dot_list(fd, fdf->f_size);
	fdf->rotate = 0;
	fdf->mlx = mlx_init();
	fdf->w_size = win_size(fdf->f_size);
	fdf->window = mlx_new_window(fdf->mlx, fdf->w_size.x, fdf->w_size.y, av[1]);
	fdf->shift.x = (fdf->w_size.x) / 2;
	fdf->shift.y = (fdf->w_size.y) / 2;
	fdf->scale = 8;
	fdf->mode = 0;
	draw_map(fdf);
	print_tulbar(fdf);
	mlx_key_hook(fdf->window, key_hook, fdf);
	mlx_loop(fdf->mlx);
	free_fdf(&fdf);
	return (0);
}
