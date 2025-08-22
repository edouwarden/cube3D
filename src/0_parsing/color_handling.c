/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:52:49 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 17:53:17 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

void	color_attribution(t_data *data, int stock[3], char c)
{
	if (c == 'F')
	{
		data->f_red = stock[0];
		data->f_green = stock[1];
		data->f_blue = stock[2];
	}
	else if (c == 'C')
	{
		data->c_red = stock[0];
		data->c_green = stock[1];
		data->c_blue = stock[2];
	}
	if (c != 'C' && c != 'F')
		parse_error(6, 0, NULL);
}

void	try_colors(char **colors, int line, char *str, t_data *data)
{
	int	nb;
	int	i;
	int	stock[3];

	i = 0;
	nb = get_y(colors);
	if (nb != 3)
		parse_error(3, line, str);
	while (i < 3)
	{
		if (strlen(colors[i]) > 3)
			parse_error(4, line, colors[i]);
		if (!is_only_digit(colors[i]))
			parse_error(4, line, colors[i]);
		stock[i] = atoi(colors[i]);
		if (stock[i] < 0 || stock[i] > 255)
			parse_error(4, line, colors[i]);
		i++;
	}
	color_attribution(data, stock, str[0]);
}

void	get_color(char *str, t_data *data, int line)
{
	char	*color;
	char	**colors;

	color = NULL;
	color = ft_strdup(str + 2);
	color = ft_strtrim(color, " 	\n");
	colors = ft_split(color, ',');
	try_colors(colors, line, str, data);
}
