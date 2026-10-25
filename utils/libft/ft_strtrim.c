/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enormand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:47:41 by enormand          #+#    #+#             */
/*   Updated: 2024/11/19 19:37:33 by enormand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_trim_char(char c, const char *set)
{
	int	i;
	int	occurs;

	i = 0;
	occurs = 0;
	while (set[i])
	{
		if (set[i] == c)
			occurs = 1;
		i++;
	}
	return (occurs);
}

static int	len_trimmed(const char *str, const char *set)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (str[i] && (is_trim_char(str[i], set) == 1))
	{
		start++;
		i++;
	}
	while (str[i])
	{
		if ((is_trim_char(str[i], set) == 0))
		{
			end = 0;
		}
		else
			end++;
		i++;
	}
	return (i - (start + end));
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		len;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = len_trimmed(s1, set);
	str = ft_calloc(sizeof(char) * (len + 1), sizeof(char));
	if (str == (char *) NULL)
		return (str);
	while (is_trim_char(s1[0], set) == 1)
		s1++;
	while (i < len)
	{
		str[i] = s1[i];
		i++;
	}
	return (str);
}
