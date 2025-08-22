/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_something.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 17:50:01 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 17:53:27 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_3d_parsing.h"
#include "libft.h"

int	is_only_digit(char *str)
{
	int	i;

	i = 1;
	while (str[i] != 0)
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_through(char c)
{
	int	i;

	i = 0;
	while (AUTHORIZED_THROUGH[i])
	{
		if (c == AUTHORIZED_THROUGH[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_player(char c)
{
	int	i;

	i = 0;
	while (AUTHORIZED_PLAYER[i])
	{
		if (c == AUTHORIZED_PLAYER[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_authorized(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
/*
int	is_in_set(char *set, char *str)
{
	int	i;
	int j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (str[i] == set)
				return (1);
			j++;
		}		
		i++;
	}
	return (0);
}
*/