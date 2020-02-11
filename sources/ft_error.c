/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcharlet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:24:36 by kcharlet          #+#    #+#             */
/*   Updated: 2020/01/29 20:24:39 by kcharlet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		ft_error(void)
{
	ft_putstr(USAGE1);
	ft_putstr(" or ");
	ft_putstr(USAGE2);
	exit(1);
}

void		print_tulbar(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*tulbar;

	y = 0;
	mlx = fdf->mlx;
	tulbar = fdf->window;
	mlx_string_put(mlx, tulbar, 75, y += 20, 0xb8f581, "How to Use");
	mlx_string_put(mlx, tulbar, 15, y += 35, 0xEAEAEA, "Zoom: ^/-^");
	mlx_string_put(mlx, tulbar, 15, y += 30, 0xEAEAEA, "Move: A D/W S Keys");
	mlx_string_put(mlx, tulbar, 15, y += 30, 0xEAEAEA, "Rotate: <-/->");
	mlx_string_put(mlx, tulbar, 15, y += 30, 0xEAEAEA, "Reset: R Key");
	mlx_string_put(mlx, tulbar, 70, y += 35, 0xb8f581, "Projections");
	mlx_string_put(mlx, tulbar, 15, y += 35, 0xEAEAEA, "Change mode: M Key");
	y = 0;
	while (y <= 250)
	{
		mlx_pixel_put(mlx, tulbar, 250, y, 0xEAEAEA);
		mlx_pixel_put(mlx, tulbar, y, 250, 0xEAEAEA);
		y++;
	}
}
