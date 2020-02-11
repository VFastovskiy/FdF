/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 04:50:58 by rczarfun          #+#    #+#             */
/*   Updated: 2020/01/30 21:22:43 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		for_dots_mode(t_fdf *fdf, t_coord *t, t_dot *dot)
{
	if (fdf->mode)
		*t = dot->iso;
	else
		*t = dot->par;
	(*t).x = (*t).x * fdf->scale + fdf->shift.x * 8;
	(*t).y = (*t).y * fdf->scale + fdf->shift.y * 8;
}

static void		for_dl_mode(t_for_dl *dl, t_coord t1, t_coord t2)
{
	(*dl).dx = abs(t2.x - t1.x);
	(*dl).dy = abs(t2.y - t1.y);
	(*dl).sign_x = t1.x < t2.x ? 1 : -1;
	(*dl).sign_y = t1.y < t2.y ? 1 : -1;
	(*dl).error = (*dl).dx - (*dl).dy;
	(*dl).color = 0x199EBD;
}

static void		put_pixel_if_you_can(t_fdf *fdf, t_coord t, t_for_dl dl)
{
	if ((t.x >= 0 && t.y >= 0) &&\
		(t.x / 8 <= fdf->w_size.x && t.y / 8 <= fdf->w_size.y) &&\
			(!(t.x <= 2000 && t.y <= 2000)))
		mlx_pixel_put(fdf->mlx, fdf->window, t.x / 8, t.y / 8, dl.color);
}

void			draw_line(t_fdf *fdf, t_dot *dot1, t_dot *dot2)
{
	t_coord		t1;
	t_coord		t2;
	t_for_dl	dl;

	for_dots_mode(fdf, &t1, dot1);
	for_dots_mode(fdf, &t2, dot2);
	for_dl_mode(&dl, t1, t2);
	if (dot1->def_z || dot2->def_z)
		dl.color = 0xCB4154;
	put_pixel_if_you_can(fdf, t2, dl);
	while (t1.x != t2.x || t1.y != t2.y)
	{
		put_pixel_if_you_can(fdf, t1, dl);
		dl.error2 = dl.error * 2;
		if (dl.error2 > -dl.dy)
		{
			dl.error -= dl.dy;
			t1.x += dl.sign_x;
		}
		if (dl.error2 < dl.dx)
		{
			dl.error += dl.dx;
			t1.y += dl.sign_y;
		}
	}
}

void			draw_map(t_fdf *fdf)
{
	int i;
	int w;

	i = 0;
	w = fdf->f_size.x;
	while (i < fdf->f_size.x * fdf->f_size.y)
	{
		if (i % fdf->f_size.x)
			draw_line(fdf, fdf->dot_lst[i], fdf->dot_lst[i - 1]);
		if (i / fdf->f_size.x)
			draw_line(fdf, fdf->dot_lst[i], fdf->dot_lst[i - w]);
		i++;
	}
}
