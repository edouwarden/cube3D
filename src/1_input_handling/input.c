/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 22:58:00 by enormand          #+#    #+#             */
/*   Updated: 2025/08/06 22:58:00 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "cube_3d_parsing.h"

void	exit_cross(t_data *data)
{
	clean_exit(data, NB_TEXTURES);
}

void	clean_exit(t_data *data, int texture_to_free)
{
	erase_textures(data, texture_to_free);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	ft_gc_cleanup();
	printf("Closing now\n");
	exit(0);
}

int	handle_key_press(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < 65536)
		data->keys[keycode] = 1;
	if (keycode == 65307)
		clean_exit(data, NB_TEXTURES);
	return (0);
}

int	handle_key_release(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < 65536)
		data->keys[keycode] = 0;
	return (0);
}
