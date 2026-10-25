/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 14:09:27 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/06 18:01:20 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d_parsing.h"

void	parse_error(int code, int line, char *str)
{
	printf("Error\n");
	if (code == 0)
		printf("Uh\n...\nNot supposed to happen something's wrong\n");
	if (code == 1)
		printf("Line %d : %s start with a wrong indicator\n", line, str);
	if (code == 2)
		printf("Could not open the texture file : %s at line %d\n", str, line);
	if (code == 3)
		printf("Invalid number of colors : %s(3 required) line %d\n", str, line);
	if (code == 4)
		printf("Color range is [0 : 255] %s line %d\n", str, line);
	if (code == 5)
		printf("Invalid caracter : %s at line %d\n", str, line);
	if (code == 6)
		printf("Path to %s already exist at line %d\n", str, line);
	if (code == 7)
		printf("Redefinition of player at line %d : %s\n", line, str);
	if (code == 8)
		printf("No definition for player, be sure to use (NSWE)\n");
	if (code == 9)
		printf("Map not closed at line %d\n", line);
	exit_check(3);
}

void	exit_check(int code)
{
	if (code == 0)
		printf("Error\nMemory allocation failed\n");
	if (code == 1)
		printf("Error\nWrong Filename(invalid extension)\n");
	if (code == 2)
		printf("Error\nWrong Filename(file does not exist / cannot be opened)\n");
	if (code == 3)
		printf("Initialization failed(check the message above)\n");
	printf("Closing Now ...\n");
	ft_gc_cleanup();
	exit (0);
}
