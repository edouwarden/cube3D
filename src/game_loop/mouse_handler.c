/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 14:23:19 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/07 14:52:09 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	handle_mouse(t_data *data, int *redraw)
{
	int	pos_x;
	int	pos_y;
	int	diff;

	mlx_mouse_get_pos(data->mlx, data->win, &pos_x, &pos_y);
	diff = (WINDOW_WIDTH / 2) - pos_x;
	if (diff != 0)
	{
		data->player.theta -= ROT_SPEED * (diff * SENSIBILITY);
		mlx_mouse_move(data->mlx, data->win,
			WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		*redraw = 1;
	}
}
