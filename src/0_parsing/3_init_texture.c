/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_init_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 12:59:41 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/07 14:21:04 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

char	*get_textures(char *str, int line)
{
	char	*path;

	path = NULL;
	path = ft_strdup(str + 2);
	path = ft_strtrim(path, " 	\n");
	try_file(path, line);
	return (path);
}

void	try_file(char *path, int line)
{
	int	fd;

	if (!path)
		parse_error(2, line, path);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parse_error(2, line, path);
	close(fd);
}

void	erase_textures(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		mlx_destroy_image(data->mlx, data->texture[i]);
		i++;
	}
}

void	init_texture(t_data *data, int i, char *path, int size_xy[2])
{
	data->address[i] = NULL;
	data->texture[i] = mlx_xpm_file_to_image(data->mlx, path, &size_xy[0],
			&size_xy[1]);
	if (!data->texture[i])
	{
		printf("Could not create image %s (must be a valid xpm file)\n", path);
		clean_exit(data, i);
		erase_textures(data, i);
		parse_error(10, 0, path);
	}
	data->address[i] = mlx_get_data_addr(data->texture[i],
			&data->bits_per_pixel, &data->texture_line_length[i],
			&data->endian_bis[i]);
	if (!data->address[i])
	{
		printf("Could not create image %s (must be a valid xpm file)\n", path);
		clean_exit(data, i);
	}
}

void	init_all_textures(t_data *data)
{
	int		i;
	int		xy[2];
	char	**path;

	xy[0] = IMAGE_X_SIZE;
	xy[1] = IMAGE_Y_SIZE;
	i = 4;
	init_texture(data, INDEX_NORTH, data->north, xy);
	init_texture(data, INDEX_SOUTH, data->south, xy);
	init_texture(data, INDEX_EAST, data->east, xy);
	init_texture(data, INDEX_WEST, data->west, xy);
	if (NB_TEXTURES > 4)
	{
		path = ft_split(PATH_TO_TEXTURE, ',');
		if (!path)
			parse_error(10, 0, "Failed to allocate path array");
		while (i < NB_TEXTURES)
		{
			printf("Creating additional texture : %s \n", path[i]);
			init_texture(data, i, path[i], xy);
			i++;
		}
	}
}
