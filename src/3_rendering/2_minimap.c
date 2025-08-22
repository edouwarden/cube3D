/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:58:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/06 22:58:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	draw_minimap_background(t_data *data)
{
	int	minimap_width;
	int	minimap_height;
	int	x;
	int	y;

	minimap_width = data->map_width * TILE_SIZE + MINIMAP_PADDING * 2;
	minimap_height = data->map_height * TILE_SIZE + MINIMAP_PADDING * 2;
	y = 0;
	while (y < minimap_height)
	{
		x = 0;
		while (x < minimap_width)
		{
			if (x < MINIMAP_PADDING || x >= minimap_width - MINIMAP_PADDING
				|| y < MINIMAP_PADDING || y >= minimap_height - MINIMAP_PADDING)
				my_mlx_pixel_put(data, x, y, MINIMAP_BORDER_COLOR);
			else
				my_mlx_pixel_put(data, x, y, EMPTY_COLOR);
			x++;
		}
		y++;
	}
}

void	draw_minimap_tile(t_data *data, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			my_mlx_pixel_put(data, x * TILE_SIZE + i + MINIMAP_PADDING, y
				* TILE_SIZE + j + MINIMAP_PADDING, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap_walls(t_data *data)
{
	int	y;
	int	x;
	int	color;

	y = 0;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (data->map[y][x] == '1')
				color = WALL_COLOR;
			else
				color = EMPTY_COLOR;
			draw_minimap_tile(data, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap_player(t_data *data, int px, int py)
{
	int	i;
	int	j;

	i = -PLAYER_SIZE / 2;
	while (i < PLAYER_SIZE / 2)
	{
		j = -PLAYER_SIZE / 2;
		while (j < PLAYER_SIZE / 2)
		{
			my_mlx_pixel_put(data, px + i, py + j, PLAYER_COLOR);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_data *data)
{
	int	player_x;
	int	player_y;

	draw_minimap_background(data);
	draw_minimap_walls(data);
	player_x = (int)(data->player.x * TILE_SIZE) + MINIMAP_PADDING;
	player_y = (int)(data->player.y * TILE_SIZE) + MINIMAP_PADDING;
	draw_minimap_player(data, player_x, player_y);
}
