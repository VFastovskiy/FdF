/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rczarfun <rczarfun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 20:03:20 by rczarfun          #+#    #+#             */
/*   Updated: 2020/01/30 21:11:41 by rczarfun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_int_matrix(int ***m, int num_of_strings)
{
	while (num_of_strings--)
	{
		if ((*m)[num_of_strings])
		{
			free((*m)[num_of_strings]);
			(*m)[num_of_strings] = NULL;
		}
	}
	if (m)
	{
		free(*m);
		*m = NULL;
	}
}

void	free_dot_list(t_dot ***list, int num_of_elements)
{
	while (num_of_elements--)
	{
		if ((*list)[num_of_elements])
		{
			free((*list)[num_of_elements]);
			(*list)[num_of_elements] = NULL;
		}
	}
	if (list)
	{
		free(*list);
		*list = NULL;
	}
}

void	free_fdf(t_fdf **fdf)
{
	free_dot_list(&((*fdf)->dot_lst), (*fdf)->f_size.x * (*fdf)->f_size.y);
	if (fdf)
	{
		free(*fdf);
		*fdf = NULL;
	}
}
