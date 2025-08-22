/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_parse_wall.c                                    :+:      :+:    :+:    */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:56:24 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 14:41:16 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

static void	count_walls_at_position(t_data *data, int x, int y)
{
	int	direction;
	int	is_wall_boundary;

	direction = 0;
	while (direction < 4)
	{
		if (direction == 0)
			is_wall_boundary = (x == 0 || data->map[y][x - 1] != '1');
		else if (direction == 1)
			is_wall_boundary = (x == data->map_width - 1 || data->map[y][x
					+ 1] != '1');
		else if (direction == 2)
			is_wall_boundary = (y == 0 || data->map[y - 1][x] != '1');
		else if (direction == 3)
			is_wall_boundary = (y == data->map_height - 1 || data->map[y
					+ 1][x] != '1');
		if (is_wall_boundary)
			data->wall_count++;
		direction++;
	}
}

static t_wall	define_walls(int x, int y, int direction)
{
	t_wall	wall;

	if (direction == 0)
		wall = (t_wall){.x1 = x * TILE_SIZE, .y1 = y * TILE_SIZE, .x2 = x
			* TILE_SIZE, .y2 = (y + 1) * TILE_SIZE, .nx = -1, .ny = 0};
	else if (direction == 1)
		wall = (t_wall){.x1 = (x + 1) * TILE_SIZE, .y1 = y * TILE_SIZE, .x2 = (x
				+ 1) * TILE_SIZE, .y2 = (y + 1) * TILE_SIZE, .nx = 1, .ny = 0};
	else if (direction == 2)
		wall = (t_wall){.x1 = x * TILE_SIZE, .y1 = y * TILE_SIZE, .x2 = (x + 1)
			* TILE_SIZE, .y2 = y * TILE_SIZE, .nx = 0, .ny = -1};
	else
		wall = (t_wall){.x1 = x * TILE_SIZE, .y1 = (y + 1) * TILE_SIZE, .x2 = (x
				+ 1) * TILE_SIZE, .y2 = (y + 1) * TILE_SIZE, .nx = 0, .ny = 1};
	return (wall);
}

static void	create_walls_at_position(t_data *data, int x, int y,
		int *wall_index)
{
	int	direction;
	int	is_wall_boundary;

	direction = 0;
	while (direction < 4)
	{
		if (direction == 0)
			is_wall_boundary = (x == 0 || data->map[y][x - 1] != '1');
		else if (direction == 1)
			is_wall_boundary = (x == data->map_width - 1 || data->map[y][x
					+ 1] != '1');
		else if (direction == 2)
			is_wall_boundary = (y == 0 || data->map[y - 1][x] != '1');
		else if (direction == 3)
			is_wall_boundary = (y == data->map_height - 1 || data->map[y
					+ 1][x] != '1');
		if (is_wall_boundary)
		{
			data->walls[*wall_index] = define_walls(x, y, direction);
			(*wall_index)++;
		}
		direction++;
	}
}

static void	create_walls(t_data *data)
{
	int	wall_index;
	int	y;
	int	x;

	wall_index = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				create_walls_at_position(data, x, y, &wall_index);
			x++;
		}
		y++;
	}
}

void	parse_walls(t_data *data)
{
	int	y;
	int	x;

	data->wall_count = 0;
	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				count_walls_at_position(data, x, y);
			x++;
		}
		y++;
	}
	data->walls = ft_gc_malloc(sizeof(t_wall) * data->wall_count);
	if (!data->walls)
		exit(1);
	create_walls(data);
}
