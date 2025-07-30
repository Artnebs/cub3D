/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:29 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 14:35:51 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <errno.h>
# include "../Libft_GNL_Printf/includes/libft.h"
# include "../Libft_GNL_Printf/includes/get_next_line.h"
# include "../Libft_GNL_Printf/includes/ft_printf.h"

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 720
# define TILE_SIZE 64
# define FOV 60
# define ROTATION_SPEED 0.1
# define MOVE_SPEED 0.1
# define TEXTURE_WIDTH 64
# define TEXTURE_HEIGHT 64

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_data;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}	t_player;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
	char		*north_texture;
	char		*south_texture;
	char		*east_texture;
	char		*west_texture;
	int			floor_color;
	int			ceiling_color;
	t_texture	textures[4];
}	t_map;

typedef struct s_wall_data
{
	int	tex_x;
	int	side;
	int	tex_num;
}	t_wall_data;

typedef struct s_dda_data
{
	int		*map_x;
	int		*map_y;
	double	*side_dist_x;
	double	*side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		*side;
}	t_dda_data;

typedef struct s_ray_params
{
	double	ray_dir[2];
	int		map[2];
	double	side_dist[2];
	double	delta_dist[2];
	int		step[2];
}	t_ray_params;

typedef struct s_draw_params
{
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_draw_params;

typedef struct s_wall_draw_params
{
	int			x;
	int			draw_start;
	int			draw_end;
	t_wall_data	*wall;
}	t_wall_draw_params;

typedef struct s_wall_x_params
{
	double	perp_wall_dist;
	double	ray_dir[2];
	double	*wall_x;
	int		side;
}	t_wall_x_params;

typedef struct s_wall_render_params
{
	double	perp_wall_dist;
	int		side;
}	t_wall_render_params;

typedef struct s_raycast_data
{
	t_ray_params			params;
	t_draw_params			draw_params;
	t_wall_data				wall;
	t_dda_data				dda;
	double					perp_wall_dist;
	int						side;
	t_wall_render_params	wr_params;
	t_wall_draw_params		wall_params;
}	t_raycast_data;

typedef struct s_cub3d
{
	t_data		data;
	t_player	player;
	t_map		map;
	t_garbage	*garbage;
}	t_cub3d;

// Garbage collector functions
char		**ft_gc_split(t_cub3d *cub3d, char const *s, char c);
char		*gc_get_next_line(t_cub3d *cub3d, int fd);
void		*gc_malloc(t_cub3d *cub3d, size_t size);
void		gc_free(t_cub3d *cub3d, void *ptr);
void		gc_cleanup(t_cub3d *cub3d);

// Error handling
void		error_exit(t_cub3d *cub3d, const char *message);

// Map parsing
int			parse_map(t_cub3d *cub3d, const char *filename);
int			validate_map(t_cub3d *cub3d);
void		init_map_data(t_cub3d *cub3d);

// Parsing utilities
int			parse_texture(t_cub3d *cub3d, char *line,
				char **texture, char *type);
int			parse_color(t_cub3d *cub3d, char *line, int *color, char *type);
int			parse_map_line(t_cub3d *cub3d, char *line);
int			is_map_line(char *line);

// Texture validation utilities
int			validate_texture_args(char **split, t_cub3d *cub3d);
int			check_texture_duplicate(char **texture, char **split,
				t_cub3d *cub3d);
int			validate_texture_file(char *path, t_cub3d *cub3d);

// Validation utilities
int			is_valid_char(char c);
void		set_player_direction(t_cub3d *cub3d, char direction);
int			get_char_at_pos(t_cub3d *cub3d, int row, int col);
int			is_open_space_adjacent(t_cub3d *cub3d, int i, int j);
int			check_borders(t_cub3d *cub3d, int i, int j, int len);
int			check_adjacent_spaces(t_cub3d *cub3d, int i, int j, int len);
void		check_position(t_cub3d *cub3d, int i, int j, int len);
int			validate_colors(t_cub3d *cub3d);

// Texture handling
int			load_textures(t_cub3d *cub3d);
void		free_textures(t_cub3d *cub3d);
int			get_texture_color(t_texture *texture, int x, int y);

// Raycasting
void		init_raycasting(t_cub3d *cub3d);
int			render_frame(void *param);

// Raycasting utilities
void		perform_dda(t_cub3d *cub3d, t_dda_data *dda);
void		init_ray_direction(t_cub3d *cub3d,
				double camera_x, double ray_dir[2]);
void		init_step_and_side_dist(t_cub3d *cub3d, t_ray_params *params);
void		calculate_wall_distance(t_cub3d *cub3d, t_ray_params *params,
				double *perp_wall_dist, int side);
void		calculate_draw_bounds(double perp_wall_dist, t_draw_params *params);
void		calculate_wall_x(t_cub3d *cub3d, t_wall_x_params *params);
void		setup_wall_data(t_wall_data *wall, double wall_x, int side,
				double ray_dir[2]);
void		draw_wall_texture(t_cub3d *cub3d, t_wall_draw_params *params);

// Event handling
int			handle_keypress(int keycode, t_cub3d *cub3d);
int			handle_window_close(t_cub3d *cub3d);

// Event utilities
int			is_valid_position(t_cub3d *cub3d, double x, double y);
void		calculate_movement(t_cub3d *cub3d, int keycode,
				double *new_x, double *new_y);
void		handle_movement(t_cub3d *cub3d, int keycode);
void		handle_rotation(t_cub3d *cub3d, int keycode);

// Raycasting
void		cast_ray(t_cub3d *cub3d, int x);
void		draw_floor_ceiling(t_cub3d *cub3d, int x,
				int draw_start, int draw_end);

// Utility functions
void		strip_newline(char *str);
int			is_valid_cub_file(const char *filename);

#endif
