/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:46:57 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 17:53:41 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

void	check(int i, int j, int lim[2], char **file)
{
	if (i - 1 == lim[0] || file[i - 1][j] == 0)
		parse_error(9, i, NULL);
	if (i + 1 == lim[1] || file[i + 1][j] == 0)
		parse_error(9, i, NULL);
	if (j - 1 == -1 || file[i][j - 1] == 0)
		parse_error(9, i, NULL);
	if (file[i][j + 1] == '\0')
		parse_error(9, i, NULL);
}

void	check_up(int ij[2], char **file, int *mv, int last_pos[2])
{
	if (is_through(file[ij[0] - 1][ij[1]]))
	{
		(file[ij[0] - 1][ij[1]]) = AUTHORIZED_PLAYER[0];
		if (*mv == 0)
		{
			last_pos[1] = ij[0] - 1;
			last_pos[0] = ij[1];
		}
		*mv = *mv + 1;
	}
}

void	check_down(int ij[2], char **file, int *mv, int last_pos[2])
{
	if (is_through(file[ij[0] + 1][ij[1]]))
	{
		(file[ij[0] + 1][ij[1]]) = AUTHORIZED_PLAYER[0];
		if (*mv == 0)
		{
			last_pos[1] = ij[0] + 1;
			last_pos[0] = ij[1];
		}
		*mv = *mv + 1;
	}
}

void	check_left(int ij[2], char **file, int *mv, int last_pos[2])
{
	if (is_through(file[ij[0]][ij[1] -1]))
	{
		(file[ij[0]][ij[1] - 1]) = AUTHORIZED_PLAYER[0];
		if (*mv == 0)
		{
			last_pos[1] = ij[0];
			last_pos[0] = ij[1] - 1;
		}
		*mv = *mv + 1;
	}
}

void	check_right(int ij[2], char **file, int *mv, int last_pos[2])
{
	if (is_through(file[ij[0]][ij[1] + 1]))
	{
		(file[ij[0]][ij[1] + 1]) = AUTHORIZED_PLAYER[0];
		if (*mv == 0)
		{
			last_pos[1] = ij[0];
			last_pos[0] = ij[1] + 1;
		}
		*mv = *mv + 1;
	}
}
