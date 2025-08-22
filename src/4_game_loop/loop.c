/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:58:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/07 14:56:05 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube_3d_parsing.h"

int	is_pos_val(t_data *data, float x, float y)
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;

	if (x < COLLISION_MARGIN || y < COLLISION_MARGIN || x >= data->map_width
		- COLLISION_MARGIN || y >= data->map_height - COLLISION_MARGIN)
		return (0);
	x1 = (int)(x - COLLISION_MARGIN);
	x2 = (int)(x + COLLISION_MARGIN);
	y1 = (int)(y - COLLISION_MARGIN);
	y2 = (int)(y + COLLISION_MARGIN);
	if (x1 < 0 || x2 >= data->map_width || y1 < 0 || y2 >= data->map_height)
	{
		return (0);
	}
	return (data->map[y1][x1] != '1' && data->map[y1][x2] != '1'
		&& data->map[y2][x1] != '1' && data->map[y2][x2] != '1'
		&& data->map[y1][(int)x] != '1' && data->map[y2][(int)x] != '1'
		&& data->map[(int)y][x1] != '1' && data->map[(int)y][x2] != '1'
		&& data->map[(int)y][(int)x] != '1');
}

void	handle_movement(t_data *data, int *redraw, float move_x, float move_y)
{
	float	new_x;
	float	new_y;

	new_x = data->player.x + move_x;
	new_y = data->player.y + move_y;
	if (!BONUS || (BONUS && is_pos_val(data, new_x, new_y)))
	{
		data->player.x = new_x;
		data->player.y = new_y;
		*redraw = 1;
	}
	else
	{
		if (fabs(move_x) > 0.001 && is_pos_val(data, new_x, data->player.y))
		{
			data->player.x += move_x;
			*redraw = 1;
		}
		if (fabs(move_y) > 0.001 && is_pos_val(data, data->player.x, new_y))
		{
			data->player.y += move_y;
			*redraw = 1;
		}
	}
}

static void	handle_keyboard_movement(t_data *data, int *redraw)
{
	float	move_x;
	float	move_y;

	if (data->keys[65362] || data->keys['w'] || data->keys['W'])
	{
		move_x = cos(data->player.theta) * MOVE_SPEED;
		move_y = sin(data->player.theta) * MOVE_SPEED;
		handle_movement(data, redraw, move_x, move_y);
	}
	if (data->keys[65364] || data->keys['s'] || data->keys['S'])
	{
		move_x = -cos(data->player.theta) * MOVE_SPEED;
		move_y = -sin(data->player.theta) * MOVE_SPEED;
		handle_movement(data, redraw, move_x, move_y);
	}
	if (data->keys['a'] || data->keys['A'])
	{
		move_x = cos(data->player.theta - M_PI / 2) * MOVE_SPEED;
		move_y = sin(data->player.theta - M_PI / 2) * MOVE_SPEED;
		handle_movement(data, redraw, move_x, move_y);
	}
}

static void	handle_rotation(t_data *data, int *redraw)
{
	float	move_x;
	float	move_y;

	if (data->keys[65361])
	{
		data->player.theta -= ROT_SPEED;
		*redraw = 1;
	}
	if (data->keys[65363])
	{
		data->player.theta += ROT_SPEED;
		*redraw = 1;
	}
	if (data->keys['d'] || data->keys['D'])
	{
		move_x = cos(data->player.theta + M_PI / 2) * MOVE_SPEED;
		move_y = sin(data->player.theta + M_PI / 2) * MOVE_SPEED;
		handle_movement(data, redraw, move_x, move_y);
	}
}

int	handle_loop(t_data *data)
{
	static struct timespec	last_time = {0, 0};
	struct timespec			current_time;
	int						redraw;
	long					time_diff;

	redraw = 0;
	clock_gettime(CLOCK_MONOTONIC, &current_time);
	time_diff = (current_time.tv_sec - last_time.tv_sec) * 1000000
		+ (current_time.tv_nsec - last_time.tv_nsec) / 1000;
	if (time_diff < FRAME_DELAY)
		return (0);
	last_time = current_time;
	if (BONUS)
		handle_mouse(data, &redraw);
	handle_rotation(data, &redraw);
	handle_keyboard_movement(data, &redraw);
	if (redraw)
	{
		draw_map(data);
		mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	}
	return (0);
}
