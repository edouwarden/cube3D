/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsarter <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:30 by jsarter           #+#    #+#             */
/*   Updated: 2025/08/21 12:17:27 by jsarter          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef CUBE3D_H
# define CUBE3D_H
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <unistd.h>
# include "../mlx/mlx.h"

# define TILE_SIZE 16
# define PLAYER_SIZE 4
# define WALL_COLOR 0x333333
# define EMPTY_COLOR 0x111111
# define PLAYER_COLOR 0xFF0000
# define MOVE_SPEED 0.05
# define ROT_SPEED 0.05
# define COLLISION_MARGIN 0.2
# define FRAME_DELAY 16000
# define MINIMAP_PADDING 2
# define MINIMAP_BORDER_COLOR 0x666666
# define WINDOW_WIDTH 2540
# define WINDOW_HEIGHT 1440
# define FOV 60.0
# define NUM_RAYS 640
# define WALL_HEIGHT 2.0
# define MAX_LIGHTS 100
# define LIGHT_INTENSITY 5.0
# define LIGHT_FALLOFF 0.1

# define PATH_TO_TEXTURE "textures/default.xpm"
# define IMAGE_X_SIZE 900
# define IMAGE_Y_SIZE 900
# define NB_TEXTURES 4
# define INDEX_NORTH 0
# define INDEX_SOUTH 1
# define INDEX_EAST 2
# define INDEX_WEST 3
# define SENSIBILITY 0.2

typedef struct s_player
{
	float			x;
	float			y;
	float			z;
	float			r;
	float			theta;
	float			fov;
}					t_player;

typedef struct s_wall
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;
	float			nx;
	float			ny;
}					t_wall;

typedef struct s_ray
{
	float			distance;
	float			wall_x;
	float			wall_y;
}					t_ray;

typedef struct s_data
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	int				f_red;
	int				f_green;
	int				f_blue;
	int				c_red;
	int				c_blue;
	int				c_green;
	char			**map;
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				map_width;
	int				map_height;
	t_player		player;
	t_wall			*walls;
	int				wall_count;
	void			*texture[NB_TEXTURES];
	char			*address[NB_TEXTURES];
	int				endian_bis[NB_TEXTURES];

	int				texture_line_length[NB_TEXTURES];
	int				keys[65536];
}					t_data;

typedef struct s_render_vars
{
	float			fov_rad;
	float			angle_step;
	float			start_angle;
	t_wall			hit_wall;
	t_ray			ray;
	float			corrected_dist;
	float			wall_height;
	int				wall_top;
	int				wall_bottom;
	float			hit_pos;
	int				texture_x;
	int				texture_y;
	float			texture_ratio;
	int				wall_dir;
	unsigned int	color;
	float			ray_angle;
	int				x;
	int				y;
}					t_render_vars;

char				*get_next_line(int fd);
int					handle_key_press(int keycode, t_data *data);
int					handle_key_release(int keycode, t_data *data);
void				read_map(t_data *data, char *filename);
void				init_player(t_data *data);
void				parse_walls(t_data *data);
void				put_pixel(t_data *data, int x, int y, int color);
void				draw_map(t_data *data);
int					handle_loop(t_data *data);
t_ray				find_nearest_wall_hit(t_data *data, float view_angle,
						t_wall *last_wall);
void				init_all_textures(t_data *data);
void				render_3d_view(t_data *data);
void				draw_minimap(t_data *data);
void				put_pixel(t_data *data, int x, int y, int color);
void				clean_exit(t_data *data, int texture_to_free);
void				exit_cross(t_data *data);
void				erase_textures(t_data *data, int nb);
void				handle_mouse(t_data *data, int *redraw);
int					get_wall_orientation(t_data *data, t_wall wall);
float				get_relative_position(t_ray ray, t_data *data, t_wall wall);
#endif
