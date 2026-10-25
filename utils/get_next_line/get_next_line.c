/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:46:30 by enormand          #+#    #+#             */
/*   Updated: 2025/08/18 10:43:35 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_new_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[0])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)ft_gc_malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*new_string(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		ft_gc_free(str);
		return (NULL);
	}
	new_str = (char *)ft_gc_malloc((gnl_strlen(str) - i + 1) * sizeof(char));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		new_str[j++] = str[i++];
	new_str[j] = '\0';
	ft_gc_free(str);
	return (new_str);
}

static char	*read_str(int fd, char *s)
{
	char		*buff;
	ssize_t		bytes;

	buff = (char *)ft_gc_malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	bytes = BUFFER_SIZE;
	while ((!ft_strchr(s, '\n')) && bytes > 0)
	{
		bytes = read(fd, buff, BUFFER_SIZE);
		s = process_buffer(s, buff, bytes);
		if (!s)
			return (NULL);
	}
	ft_gc_free(buff);
	return (s);
}

static char	*handle_line(char **next_line)
{
	char	*line;

	line = get_new_line(*next_line);
	if (!line)
	{
		ft_gc_free(*next_line);
		*next_line = NULL;
		return (NULL);
	}
	*next_line = new_string(*next_line);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!next_line)
	{
		next_line = ft_gc_malloc(1);
		if (!next_line)
			return (NULL);
		next_line[0] = '\0';
	}
	temp = read_str(fd, next_line);
	if (!temp)
	{
		ft_gc_free(next_line);
		next_line = NULL;
		return (NULL);
	}
	next_line = temp;
	return (handle_line(&next_line));
}
