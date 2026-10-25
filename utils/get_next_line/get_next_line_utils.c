/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:46:30 by enormand          #+#    #+#             */
/*   Updated: 2025/08/18 10:45:11 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*gnl_strjoin(char *s, char *buff)
{
	char	*arr;
	int		i;
	int		j;

	if (!s || !buff)
		return (NULL);
	arr = (char *)ft_gc_malloc((gnl_strlen(s) + gnl_strlen(buff) + 1)
			* sizeof(char));
	if (!arr)
		return (NULL);
	i = 0;
	while (s[i])
	{
		arr[i] = s[i];
		i++;
	}
	j = 0;
	while (buff[j])
		arr[i++] = buff[j++];
	arr[i] = '\0';
	return (ft_gc_free(s), arr);
}

char	*process_buffer(char *s, char *buff, ssize_t bytes)
{
	if (bytes < 0)
	{
		ft_gc_free(buff);
		ft_gc_free(s);
		return (NULL);
	}
	buff[bytes] = '\0';
	if (bytes > 0)
		s = gnl_strjoin(s, buff);
	return (s);
}
