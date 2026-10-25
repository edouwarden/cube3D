/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:58:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/07 14:44:58 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube3d_parsing.h"
#include "libft.h"

void	init_player(t_data *data)
{
	int	x;
	int	y;

	y = data->player.y;
	x = data->player.x;
	data->player.x = x + 0.5;
	data->player.y = y - 0.5;
	data->player.z = 0.0;
	data->player.r = 0.0;
	if (data->map[y - 1][x] == 'N')
		data->player.theta = -M_PI / 2;
	else if (data->map[y - 1][x] == 'S')
		data->player.theta = M_PI / 2;
	else if (data->map[y - 1][x] == 'E')
		data->player.theta = 0.0;
	else if (data->map[y - 1][x] == 'W')
		data->player.theta = M_PI;
	data->player.fov = FOV * M_PI / 180.0;
	return ;
}

void	define_keys(t_data *data)
{
	int	i;

	i = 0;
	while (i < 65536)
	{
		data->keys[i] = 0;
		i++;
	}
}

int	init_window(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
			"Cub3D");
	data->img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->win || !data->img)
		return (1);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel,
			&data->line_length, &data->endian);
	mlx_hook(data->win, 2, 1L << 0, handle_key_press, data);
	mlx_hook(data->win, 3, 1L << 1, handle_key_release, data);
	mlx_hook(data->win, 17, 0, (void *)exit_cross, data);
	mlx_loop_hook(data->mlx, handle_loop, data);
	draw_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	mlx_mouse_move(data->mlx, data->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	mlx_loop(data->mlx);
	return (0);
}

int	main(int c, char **v)
{
	t_data	data;

	ft_bzero(&data, sizeof(t_data));
	(void)c;
	define_keys(&data);
	load_and_parse_map(v[1], &data);
	if (!data.map[0])
		return (printf("Invalid map file\n"));
	data.mlx = mlx_init();
	if (!data.mlx)
		return (1);
	init_all_textures(&data);
	init_player(&data);
	if (init_window(&data))
		return (1);
	ft_gc_cleanup();
	return (0);
}
