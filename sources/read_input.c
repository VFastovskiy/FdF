/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 16:47:35 by rczarfun          #+#    #+#             */
/*   Updated: 2020/01/30 21:00:31 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_open_file_and_count_field_size(char *av, t_coord *size)
{
	int		fd;
	char	*line;
	int		x_curr;

	fd = open(av, O_RDONLY);
	if (fd < 0)
		return (-1);
	(*size).y = 0;
	(*size).x = -1;
	while (get_next_line(fd, &line))
	{
		(*size).y++;
		if (((*size).x) < 0)
			(*size).x = ft_num_ammount(line);
		x_curr = ft_num_ammount(line);
		ft_strdel(&line);
		if ((((*size).x) != x_curr) || (!(x_curr > 0)))
			return (-2);
	}
	close(fd);
	fd = open(av, O_RDONLY);
	return (fd);
}

int		**file_to_matrix(int fd, t_coord size)
{
	char	*line;
	int		**matrix;
	int		i;

	if (!(matrix = (int **)ft_memalloc(sizeof(int *) * size.y)))
		return (NULL);
	i = 0;
	while (get_next_line(fd, &line))
	{
		matrix[i++] = ft_num_split(line);
		ft_strdel(&line);
	}
	return (matrix);
}

t_dot	**file_to_dot_list(int fd, t_coord size)
{
	int		**matrix;
	int		i;
	int		j;
	t_dot	**dot_list;

	matrix = file_to_matrix(fd, size);
	if (!(dot_list = (t_dot **)ft_memalloc(sizeof(t_dot *) * size.x * size.y)))
		return (0);
	j = 0;
	while (j < size.y)
	{
		i = 0;
		while (i < size.x)
		{
			dot_list[i + j * (int)size.x] = \
			ft_new_dot(i, j, matrix[j][i], size);
			i++;
		}
		j++;
	}
	free_int_matrix(&matrix, size.y);
	return (dot_list);
}
