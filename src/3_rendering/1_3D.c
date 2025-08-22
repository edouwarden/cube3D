/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_3D.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:58:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/06 22:58:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

unsigned int	my_mlx_pixel_get_col(t_data *data, int x, int y, int nb)
{
	void			*dst;
	unsigned int	color;

	if (!data || !data->address[nb] || nb >= NB_TEXTURES || x < 0
		|| x >= IMAGE_X_SIZE || y < 0 || y >= IMAGE_Y_SIZE)
		return ((unsigned int)-1);
	dst = data->address[nb] + (y * data->texture_line_length[nb] + x
			* (data->bits_per_pixel / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	draw_sky_floor(t_data *data)
{
	int	ceiling_color;
	int	floor_color;
	int	y;
	int	x;

	ceiling_color = (data->c_red << 16) | (data->c_green << 8) | data->c_blue;
	floor_color = (data->f_red << 16) | (data->f_green << 8) | data->f_blue;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			if (y < WINDOW_HEIGHT / 2)
				my_mlx_pixel_put(data, x, y, ceiling_color);
			else
				my_mlx_pixel_put(data, x, y, floor_color);
			x++;
		}
		y++;
	}
}

void	draw_collums(t_render_vars *vars, t_data *data)
{
	vars->y = vars->wall_top;
	while (vars->y < vars->wall_bottom)
	{
		if (vars->y >= WINDOW_HEIGHT || vars->y < 0)
		{
			vars->y++;
			continue ;
		}
		vars->texture_y = ((vars->y * IMAGE_Y_SIZE) / vars->wall_height)
			+ vars->texture_ratio;
		vars->color = my_mlx_pixel_get_col(data, vars->texture_x,
				vars->texture_y, vars->wall_dir);
		if (vars->color == (unsigned int)-1)
		{
			vars->y++;
			continue ;
		}
		my_mlx_pixel_put(data, vars->x, vars->y, vars->color);
		vars->y++;
	}
}

void	send_ray(t_render_vars *vars, t_data *data)
{
	vars->ray_angle = vars->start_angle + vars->x * vars->angle_step;
	vars->ray = find_nearest_wall_hit(data, vars->ray_angle, &vars->hit_wall);
	if (vars->ray.distance == INFINITY)
	{
		vars->x++;
		return ;
	}
	vars->corrected_dist = vars->ray.distance * cosf(vars->ray_angle
			- data->player.theta);
	vars->wall_height = (TILE_SIZE * WINDOW_HEIGHT) / vars->corrected_dist;
	vars->wall_top = (int)(WINDOW_HEIGHT - vars->wall_height) / 2;
	vars->wall_bottom = (int)(WINDOW_HEIGHT + vars->wall_height) / 2;
	if (vars->wall_top < 0)
		vars->wall_top = 0;
	if (vars->wall_bottom > WINDOW_HEIGHT)
		vars->wall_bottom = WINDOW_HEIGHT;
	vars->wall_dir = get_wall_orientation(data, vars->hit_wall);
	vars->texture_ratio = (128 * (vars->wall_height - WINDOW_HEIGHT)
			* IMAGE_Y_SIZE) / (vars->wall_height * 256);
	vars->hit_pos = get_relative_position(vars->ray, data, vars->hit_wall);
	vars->texture_x = (int)(vars->hit_pos * IMAGE_X_SIZE) % IMAGE_X_SIZE;
	if ((vars->hit_wall.nx > 0 && vars->ray.wall_x > 0)
		|| (vars->hit_wall.ny < 0 && vars->ray.wall_y > 0))
		vars->texture_x = IMAGE_X_SIZE - vars->texture_x - 1;
	draw_collums(vars, data);
}

void	render_3d_view(t_data *data)
{
	t_render_vars	vars;

	draw_sky_floor(data);
	vars.fov_rad = FOV * M_PI / 180.0f;
	vars.angle_step = vars.fov_rad / WINDOW_WIDTH;
	vars.start_angle = data->player.theta - vars.fov_rad / 2.0f;
	vars.hit_wall = data->walls[0];
	vars.x = 0;
	while (vars.x < WINDOW_WIDTH)
	{
		send_ray(&vars, data);
		vars.x++;
	}
}
/*
void	render_3d_view(t_data *data)
{
	float			fov_rad;
	float			angle_step;
	float			start_angle;
	t_wall			hit_wall;
	t_ray			ray;
	float			corrected_dist;
	float			wall_height;
	int				wall_top;
	int				wall_bottom;
	float			hit_pos;
	int				texture_x;
	int				texture_y;
	float			texture_ratio;
	int				wall_dir;
	unsigned int	color;
	float			ray_angle;
	int				x;
	int				y;

	draw_sky_floor(data);
	fov_rad = FOV * M_PI / 180.0f;
	angle_step = fov_rad / WINDOW_WIDTH;
	start_angle = data->player.theta - fov_rad / 2.0f;
	hit_wall = data->walls[0];
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		ray_angle = start_angle + x * angle_step;
		ray = find_nearest_wall_hit(data, ray_angle, &hit_wall);
		if (ray.distance == INFINITY)
		{
			x++;
			continue ;
		}
		corrected_dist = ray.distance * cosf(ray_angle - data->player.theta);
		wall_height = (TILE_SIZE * WINDOW_HEIGHT) / corrected_dist;
		wall_top = (int)(WINDOW_HEIGHT - wall_height) / 2;
		wall_bottom = (int)(WINDOW_HEIGHT + wall_height) / 2;
		if (wall_top < 0)
			wall_top = 0;
		if (wall_bottom > WINDOW_HEIGHT)
			wall_bottom = WINDOW_HEIGHT;
		wall_dir = get_wall_orientation(data, hit_wall);
		texture_ratio = (128 * (wall_height - WINDOW_HEIGHT) * IMAGE_Y_SIZE)
			/ (wall_height * 256);
		hit_pos = get_relative_position(ray, data, hit_wall);
		texture_x = (int)(hit_pos * IMAGE_X_SIZE) % IMAGE_X_SIZE;
		y = wall_top;
		while (y < wall_bottom)
		{
			if (y >= WINDOW_HEIGHT || y < 0)
			{
				y++;
				continue ;
			}
			texture_y = ((y * IMAGE_Y_SIZE) / wall_height) + texture_ratio;
			color = my_mlx_pixel_get_col(data, texture_x, texture_y, wall_dir);
			if (color == (unsigned int)-1)
			{
				y++;
				continue ;
			}
			my_mlx_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}
*/