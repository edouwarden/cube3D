/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_ray_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:00:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/21 12:00:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static void	draw_ray_line(t_data *data, t_ray ray)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	int		steps;
	int		i;

	x = data->player.x * TILE_SIZE + MINIMAP_PADDING;
	y = data->player.y * TILE_SIZE + MINIMAP_PADDING;
	dx = ray.wall_x - data->player.x * TILE_SIZE;
	dy = ray.wall_y - data->player.y * TILE_SIZE;
	steps = (int)ray.distance;
	if (steps < 1)
		steps = 1;
	i = 0;
	while (i <= steps)
	{
		put_pixel(data, (int)(x + dx * i / steps),
			(int)(y + dy * i / steps), RAY_COLOR);
		i++;
	}
}

static void	mark_hit(t_data *data, t_ray ray)
{
	put_pixel(data, (int)ray.wall_x + MINIMAP_PADDING,
		(int)ray.wall_y + MINIMAP_PADDING, RAY_HIT_COLOR);
}

void	draw_minimap_rays(t_data *data)
{
	float	fov;
	float	step;
	float	angle;
	t_wall	wall;
	t_ray	ray;
	int		x;

	fov = FOV * M_PI / 180.0f;
	step = fov / WINDOW_WIDTH;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		angle = data->player.theta - fov / 2.0f + x * step;
		ray = find_nearest_wall_hit(data, angle, &wall);
		if (ray.distance != INFINITY)
		{
			draw_ray_line(data, ray);
			mark_hit(data, ray);
		}
		x += RAY_DEBUG_STEP;
	}
}
