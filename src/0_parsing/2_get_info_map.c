/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_get_info_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 13:26:20 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 18:00:49 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"

int	get_y(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

int	get_x(char **map, int y)
{
	int	i;
	int	x_temp;
	int	x;

	i = 0;
	x = -1;
	while (i < y)
	{
		map[i] = ft_strtrim(map[i], "\n");
		x_temp = ft_strlen(map[i]);
		if (x == -1)
			x = x_temp;
		i++;
	}
	return (x);
}

char	**clone_map(char **file, int start, int x_max, int y_max)
{
	char	**map;
	int		i;

	i = 0;
	map = ft_calloc(sizeof(char *), (y_max + 1));
	while (i < y_max)
	{
		map[i] = ft_calloc(x_max, sizeof(char));
		map[i] = ft_memcpy(map[i], file[start + i], ft_strlen(file[start + i]));
		i++;
	}
	return (map);
}
