/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:54:47 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 17:55:52 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_parsing.h"
#include "libft.h"

int	next_important_line(char **file, int start)
{
	int		i;
	char	*str;

	i = start;
	str = ft_strtrim(file[i], "	 ");
	while (str && ft_strlen(str) == 0)
	{
		i++;
		str = ft_strtrim(file[i], "	 ");
	}
	return (i);
}

int	get_valid_line_length(char *str, t_data *data, int line)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_authorized(str[i], AUTHORIZED_MAP))
		{
			if (is_player(str[i]))
			{
				if (data->player.x != -1)
					parse_error(7, i, str);
				data->player.x = i;
				data->player.y = line;
			}
			else
				parse_error(5, line, str);
		}
		i++;
	}
	return (i);
}

void	get_max_length(char **file, int index, t_data *data, int size[2])
{
	int	i;
	int	max;
	int	tmp;

	i = index;
	max = 0;
	i++;
	while (file[i])
	{
		tmp = get_valid_line_length(file[i], data, i);
		if (tmp > max)
			max = tmp;
		i++;
	}
	size[0] = max;
	size[1] = i;
}
