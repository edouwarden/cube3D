/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:56:24 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 14:41:16 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

int	extract_bis(char name[2], char *str, t_data *data, int line)
{
	if (name[0] == 'E' && name[1] == 'A')
	{
		if (data->east)
			parse_error(6, line, "EAST");
		data->east = get_textures(str, line);
		return (1);
	}
	if (name[0] == 'F' && name[1] == ' ' && str != NULL)
	{
		if (data->f_red != -1)
			parse_error(6, line, "FLOOR");
		get_color(str, data, line);
		return (1);
	}
	if (name[0] == 'C' && name[1] == ' ' && str != NULL)
	{
		if (data->c_red != -1)
			parse_error(6, line, "CEILING");
		get_color(str, data, line);
		return (1);
	}
	return (0);
}

int	extract(char name[2], char *str, t_data *data, int line)
{
	if (name[0] == 'N' && name[1] == 'O')
	{
		if (data->north)
			parse_error(6, line, "NORTH");
		data->north = get_textures(str, line);
		return (1);
	}
	if (name[0] == 'S' && name[1] == 'O')
	{
		if (data->south)
			parse_error(6, line, "");
		data->south = get_textures(str, line);
		return (1);
	}
	if (name[0] == 'W' && name[1] == 'E')
	{
		if (data->west)
			parse_error(6, line, "WEST");
		data->west = get_textures(str, line);
		return (1);
	}
	else
		return (extract_bis(name, str, data, line));
}

int	extract_textures(char **file, t_data *data)
{
	int		i;
	int		line;
	char	name[2];

	i = 0;
	line = next_important_line(file, 0);
	while (i < 6 && file[line])
	{
		file[line] = ft_strtrim(file[line], " 	\n");
		while (file[line][0] == ' ')
			file++;
		if (file[0] && file[1])
		{
			name[0] = file[line][0];
			name[1] = file[line][1];
		}
		else
			parse_error(1, i, file[line]);
		if (!extract(name, file[line], data, line))
			parse_error(1, i, file[line]);
		line = next_important_line(file, line + 1);
		i++;
	}
	return (line);
}

void	extract_map(char **file, t_data *data, int index)
{
	int		size[2];
	char	**map_trash;

	get_max_lenght(file, index, data, size);
	if (data->player.x == -1)
		parse_error(8, 0, NULL);
	data->player.y = data->player.y - index;
	data->map = clone_map(file, index + 1, size[0] + 1, size[1] - (index));
	data->map_height = size[1] - index;
	data->map_width = size[0];
	map_trash = clone_map(file, index + 1, size[0] + 1, size[1] - (index));
	fraud_fill(0, size[1] - index, data, map_trash);
}

void	supa_parse(char **file, t_data *data)
{
	int	index;

	data->f_red = -1;
	data->c_red = -1;
	data->player.x = -1;
	data->player.y = -1;
	data->north = NULL;
	data->south = NULL;
	data->west = NULL;
	data->east = NULL;
	index = extract_textures(file, data);
	index--;
	extract_map(file, data, index);
	printf("Map is valid\n");
}
