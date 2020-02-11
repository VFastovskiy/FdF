/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dots_manipulations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 17:40:16 by rczarfun          #+#    #+#             */
/*   Updated: 2020/01/29 19:22:57 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_dot	*ft_new_dot(int i, int j, int z, t_coord f_size)
{
	t_dot	*dot;

	if (!(dot = (t_dot *)ft_memalloc(sizeof(t_dot))))
		return (0);
	dot->def.x = (2 * i - (f_size.x - 1)) * 30;
	dot->def.y = (2 * j - (f_size.y - 1)) * 30;
	dot->def_z = 4 * z;
	dot->rot.x = dot->def.x;
	dot->rot.y = dot->def.y;
	make_iso_and_par(dot);
	return (dot);
}

void	make_iso_and_par(t_dot *dot)
{
	dot->iso.x = (dot->rot.x - dot->rot.y) * cos(M_PI / 6);
	dot->iso.y = (dot->rot.x + dot->rot.y) * sin(M_PI / 6) - dot->def_z;
	dot->par.x = dot->rot.x + dot->def_z / sqrt(2.);
	dot->par.y = dot->rot.y - dot->def_z / sqrt(2.);
}

void	rotation(t_fdf *fdf, int t)
{
	t_dot		*dot;
	int			num_of_dots;
	double		ang;

	ang = M_PI / 16;
	num_of_dots = fdf->f_size.x * fdf->f_size.y;
	while (num_of_dots--)
	{
		dot = fdf->dot_lst[num_of_dots];
		dot->rot.x = dot->def.x * cos(ang * t) - dot->def.y * sin(ang * t);
		dot->rot.y = dot->def.x * sin(ang * t) + dot->def.y * cos(ang * t);
		make_iso_and_par(dot);
	}
}
