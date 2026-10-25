/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_3d_parsing.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:30 by jsarter           #+#    #+#             */
/*   Updated: 2025/06/06 14:57:29 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_3D_PARSING_H
# define CUBE_3D_PARSING_H

# include "cube3d.h"
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

void	exit_check(int code);
void	parse_error(int code, int line, char *str);
int		get_y(char **map);
void	parse_walls(t_data *data);
void	map_check(char *path, t_data *data);
void	supa_parse(char **file, t_data *data);
char	*get_textures(char *str, int line);
char	*get_next_line(int fd);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef AUTHORIZED
#  define AUTHORIZED_MAP "10 \0"
#  define AUTHORIZED_PLAYER "NSWE\0"
#  define AUTHORIZED_THROUGH "0 \0"
# endif

void	exit_check(int code);
void	parse_error(int code, int line, char *str);
void	check_path_name(char *p);
int		get_y(char **map);
void	map_check(char *path, t_data *data);
void	supa_parse(char **file, t_data *data);
char	*get_textures(char *str, int line);
char	*get_next_line(int fd);
char	**file_add(char *line, char **prev_map, int len);
char	**clone_map(char **file, int start, int x_max, int y_max);
int		is_only_digit(char *str);
int		is_through(char c);
int		is_player(char c);
int		is_authorized(char c, char *str);
void	try_file(char *path, int line);
void	get_color(char *str, t_data *data, int line);
void	check(int i, int j, int lim[2], char **file);
void	check_up(int ij[2], char **file, int *mv, int last_pos[2]);
void	check_down(int ij[2], char **file, int *mv, int last_pos[2]);
void	check_left(int ij[2], char **file, int *mv, int last_pos[2]);
void	check_right(int ij[2], char **file, int *mv, int last_pos[2]);
void	get_max_lenght(char **file, int index, t_data *data, int size[2]);
int		get_len_legal(char *str, t_data *data, int line);
int		next_important_line(char **file, int start);
void	flood_fill(int lim_h, int lim_b, t_data *data, char **file);

int		sn(char *buffer, int size);
int		ft_cpl(char *dest, int j);
int		ft_clean(char *str, char *to_free);
int		is_player(char c);

#endif
