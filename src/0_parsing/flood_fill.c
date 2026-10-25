/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:46:07 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 17:53:51 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

int	update_fill(int last_pos[2], char **file, int lim[2])
{
	int	mv;
	int	ij[2];

	mv = 0;
	ij[0] = last_pos[1];
	ij[1] = last_pos[0];
	while (file[ij[0]])
	{
		while (file[ij[0]][ij[1]])
		{
			if (is_player(file[ij[0]][ij[1]]))
			{
				check(ij[0], ij[1], lim, file);
				check_up(ij, file, &mv, last_pos);
				check_left(ij, file, &mv, last_pos);
				check_right(ij, file, &mv, last_pos);
				check_down(ij, file, &mv, last_pos);
			}
			ij[1]++;
		}
		ij[1] = 0;
		ij[0]++;
	}
	return (mv);
}

void	check_map_boundary(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == 'N' || map[0][i] == 'E' ||
				map[0][i] == 'S' || map[0][i] == 'W')
			parse_error(9, i, NULL);
		i++;
	}
}

void	flood_fill(int lim_h, int lim_b, t_data *data, char **file)
{
	int	last_pos[2];
	int	lim[2];
	int	moving;

	lim[0] = lim_h - 1;
	lim[1] = lim_b;
	last_pos[0] = data->player.x;
	last_pos[1] = data->player.y - 1;
	moving = update_fill(last_pos, file, lim);
	while (moving)
		moving = update_fill(last_pos, file, lim);
	check_map_boundary(file);
}
