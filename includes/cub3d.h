/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:39:29 by anebbou           #+#    #+#             */
/*   Updated: 2025/05/20 18:20:53 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

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
} t_texture;

typedef struct s_garbage
{
	void			*ptr;
	struct s_garbage	*next;
} t_garbage;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
} t_data;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
} t_player;

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
	t_texture	textures[4]; // 0:N 1:S 2:E 3:W
} t_map;

typedef struct s_cub3d
{
	t_data		data;
	t_player	player;
	t_map		map;
	t_garbage	*garbage;
} t_cub3d;

// Garbage collector functions
void		*gc_malloc(t_cub3d *cub3d, size_t size);
void		gc_free(t_cub3d *cub3d, void *ptr);
void		gc_cleanup(t_cub3d *cub3d);

// Error handling
void		error_exit(t_cub3d *cub3d, const char *message);

// Map parsing
int			parse_map(t_cub3d *cub3d, const char *filename);
int			validate_map(t_cub3d *cub3d);

// Texture handling
int			load_textures(t_cub3d *cub3d);
void		free_textures(t_cub3d *cub3d);
int			get_texture_color(t_texture *texture, int x, int y);

// Raycasting
void		init_raycasting(t_cub3d *cub3d);
void		render_frame(t_cub3d *cub3d);

// Event handling
int			handle_keypress(int keycode, t_cub3d *cub3d);
int			handle_window_close(t_cub3d *cub3d);

// Utility functions
void		free_split(char **split);
char		*ft_strdup(const char *s);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *str);
size_t		ft_strlen(const char *s);

#endif
