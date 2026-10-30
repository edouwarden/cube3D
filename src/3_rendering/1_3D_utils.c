/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_3D_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:58:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/06 22:58:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	get_wall_orientation(t_data *data, t_wall wall)
{
	(void)data;
	if (wall.nx > 0)
		return (INDEX_EAST);
	else if (wall.nx < 0)
		return (INDEX_WEST);
	else if (wall.ny > 0)
		return (INDEX_SOUTH);
	else if (wall.ny < 0)
		return (INDEX_NORTH);
	return (0);
}

float	get_relative_position(t_ray ray, t_data *data, t_wall wall)
{
	float	wall_length;
	float	ray_length;
	float	relative_pos;

	wall_length = sqrtf(powf(wall.x2 - wall.x1, 2) + powf(wall.y2 - wall.y1,
				2));
	ray.wall_x -= wall.x1;
	ray.wall_y -= wall.y1;
	ray_length = sqrtf(powf(ray.wall_x, 2) + powf(ray.wall_y, 2));
	relative_pos = ray_length / wall_length;
	(void)data;
	return (relative_pos);
}
