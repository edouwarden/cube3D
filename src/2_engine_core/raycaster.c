/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:58:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/06 22:58:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

static float	calculate_ray_wall_intersection(float *start_point,
		float *ray_direction, t_wall wall)
{
	float	det;
	float	intersection_param;
	float	distance;

	det = (wall.x2 - wall.x1) * ray_direction[1] - (wall.y2 - wall.y1)
		* ray_direction[0];
	if (det == 0)
		return (-1);
	intersection_param = ((wall.y1 - start_point[1]) * ray_direction[0]
			- (wall.x1 - start_point[0]) * ray_direction[1]) / det;
	if (intersection_param < 0 || intersection_param > 1)
		return (-1);
	distance = ((wall.x2 - wall.x1) * (wall.y1 - start_point[1]) - (wall.y2
				- wall.y1) * (wall.x1 - start_point[0])) / det;
	if (distance < 0)
		return (-1);
	return (distance);
}

t_ray	find_nearest_wall_hit(t_data *data, float view_angle, t_wall *last_wall)
{
	t_ray	ray_hit;
	float	start_point[2];
	float	ray_direction[2];
	int		wall_index;
	float	hit_distance;

	ray_hit.distance = INFINITY;
	start_point[0] = data->player.x * TILE_SIZE;
	start_point[1] = data->player.y * TILE_SIZE;
	ray_direction[0] = cos(view_angle);
	ray_direction[1] = sin(view_angle);
	wall_index = -1;
	while (++wall_index < data->wall_count)
	{
		hit_distance = calculate_ray_wall_intersection(start_point,
				ray_direction, data->walls[wall_index]);
		if (hit_distance >= 0 && hit_distance < ray_hit.distance)
		{
			ray_hit.distance = hit_distance;
			ray_hit.wall_x = start_point[0] + ray_direction[0] * hit_distance;
			ray_hit.wall_y = start_point[1] + ray_direction[1] * hit_distance;
			*last_wall = data->walls[wall_index];
		}
	}
	return (ray_hit);
}
