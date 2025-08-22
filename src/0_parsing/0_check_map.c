/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_check_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:52:59 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 18:02:17 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

void	check_path_name(char *p)
{
	int	l;

	l = ft_strlen(p);
	if (l < 4)
		exit_check(1);
	l--;
	if (p[l - 3] != '.' || p[l - 2] != 'c' || p[l - 1] != 'u' || p[l] != 'b')
		exit_check(1);
}

void	erase_map(char **map, int abort, int fd, int all)
{
	int	i;

	i = 0;
	if (map != NULL)
	{
		while (map[i])
		{
			if (all)
				ft_gc_free(map[i]);
			i++;
		}
		if (map[i])
			ft_gc_free(map[i]);
		ft_gc_free(map);
	}
	if (abort)
	{
		if (fd > 0)
			close(fd);
		exit_check(abort);
	}
}

char	**file_add(char *line, char **prev_map, int len)
{
	char	**new_map;
	int		i;

	new_map = ft_calloc(sizeof(char *), len + 2);
	line = ft_strtrim(line, "\n");
	i = 0;
	while (i < len)
	{
		new_map[i] = prev_map[i];
		i++;
	}
	new_map[i] = line;
	new_map[i + 1] = NULL;
	return (new_map);
}

char	**check_file(char *path)
{
	int		fd;
	char	*line;
	char	**file;
	int		len_map;

	fd = open(path, 0, O_RDONLY);
	if (fd < 0)
		exit_check(2);
	line = (char *)1;
	file = NULL;
	len_map = 0;
	while (line)
	{
		line = get_next_line(fd);
		file = file_add(line, file, len_map);
		len_map++;
	}
	close(fd);
	return (file);
}

void	map_check(char *path, t_data *data)
{
	char	**file;

	check_path_name(path);
	file = check_file(path);
	supa_parse(file, data);
	parse_walls(data);
}
