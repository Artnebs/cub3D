/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:55 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/28 18:15:57 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_raycasting(t_cub3d *cub3d)
{
	(void)cub3d;
}

static void	draw_floor_ceiling(t_cub3d *cub3d, int x, int draw_start,
	int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH)
			*(int *)(cub3d->data.addr + (y * cub3d->data.line_length
						+ x * (cub3d->data.bits_per_pixel / 8)))
				= cub3d->map.ceiling_color;
		y++;
	}
	y = draw_end;
	while (y < WINDOW_HEIGHT)
	{
		if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH)
			*(int *)(cub3d->data.addr + (y * cub3d->data.line_length
						+ x * (cub3d->data.bits_per_pixel / 8)))
				= cub3d->map.floor_color;
		y++;
	}
}

typedef struct s_wall_data
{
	int	tex_x;
	int	side;
	int	tex_num;
}	t_wall_data;

static void	draw_wall_texture(t_cub3d *cub3d, int x, int draw_start,
	int draw_end, t_wall_data *wall)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * TEXTURE_HEIGHT / (draw_end - draw_start);
	tex_pos = (draw_start - WINDOW_HEIGHT / 2
			+ (draw_end - draw_start) / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH)
		{
			color = get_texture_color(&cub3d->map.textures[wall->tex_num],
					wall->tex_x, tex_y);
			if (wall->side == 1)
				color = (color >> 1) & 8355711;
			*(int *)(cub3d->data.addr + (y * cub3d->data.line_length
						+ x * (cub3d->data.bits_per_pixel / 8))) = color;
		}
		y++;
	}
}

static int	is_wall(t_cub3d *cub3d, int map_x, int map_y)
{
	if (map_x < 0 || map_x >= cub3d->map.width
		|| map_y < 0 || map_y >= cub3d->map.height)
		return (1);
	if (!cub3d->map.map[map_y]
		|| map_x >= (int)ft_strlen(cub3d->map.map[map_y]))
		return (1);
	return (cub3d->map.map[map_y][map_x] == '1');
}

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

static void	perform_dda(t_cub3d *cub3d, t_dda_data *dda)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (*dda->side_dist_x < *dda->side_dist_y)
		{
			*dda->side_dist_x += dda->delta_dist_x;
			*dda->map_x += dda->step_x;
			*dda->side = 0;
		}
		else
		{
			*dda->side_dist_y += dda->delta_dist_y;
			*dda->map_y += dda->step_y;
			*dda->side = 1;
		}
		if (is_wall(cub3d, *dda->map_x, *dda->map_y))
			hit = 1;
	}
}

static void	cast_ray(t_cub3d *cub3d, int x)
{
	double		camera_x;
	double		ray_dir[2];
	int			map[2];
	double		side_dist[2];
	double		delta_dist[2];
	int			step[2];
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	t_wall_data	wall;
	t_dda_data	dda;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray_dir[0] = cub3d->player.dir_x + cub3d->player.plane_x * camera_x;
	ray_dir[1] = cub3d->player.dir_y + cub3d->player.plane_y * camera_x;
	map[0] = (int)cub3d->player.pos_x;
	map[1] = (int)cub3d->player.pos_y;
	delta_dist[0] = fabs(1 / ray_dir[0]);
	delta_dist[1] = fabs(1 / ray_dir[1]);
	if (ray_dir[0] < 0)
	{
		step[0] = -1;
		side_dist[0] = (cub3d->player.pos_x - map[0]) * delta_dist[0];
	}
	else
	{
		step[0] = 1;
		side_dist[0] = (map[0] + 1.0 - cub3d->player.pos_x) * delta_dist[0];
	}
	if (ray_dir[1] < 0)
	{
		step[1] = -1;
		side_dist[1] = (cub3d->player.pos_y - map[1]) * delta_dist[1];
	}
	else
	{
		step[1] = 1;
		side_dist[1] = (map[1] + 1.0 - cub3d->player.pos_y) * delta_dist[1];
	}
	dda = (t_dda_data){&map[0], &map[1], &side_dist[0], &side_dist[1],
		delta_dist[0], delta_dist[1], step[0], step[1], &side};
	perform_dda(cub3d, &dda);
	if (side == 0)
		perp_wall_dist = (map[0] - cub3d->player.pos_x
				+ (1 - step[0]) / 2) / ray_dir[0];
	else
		perp_wall_dist = (map[1] - cub3d->player.pos_y
				+ (1 - step[1]) / 2) / ray_dir[1];
	line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	draw_start = -line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	if (side == 0)
		wall_x = cub3d->player.pos_y + perp_wall_dist * ray_dir[1];
	else
		wall_x = cub3d->player.pos_x + perp_wall_dist * ray_dir[0];
	wall_x -= floor(wall_x);
	wall.tex_x = (int)(wall_x * TEXTURE_WIDTH);
	if (side == 0 && ray_dir[0] > 0)
		wall.tex_x = TEXTURE_WIDTH - wall.tex_x - 1;
	if (side == 1 && ray_dir[1] < 0)
		wall.tex_x = TEXTURE_WIDTH - wall.tex_x - 1;
	if (side == 0)
		wall.tex_num = (ray_dir[0] > 0) ? 2 : 3;
	else
		wall.tex_num = (ray_dir[1] > 0) ? 1 : 0;
	wall.side = side;
	draw_floor_ceiling(cub3d, x, draw_start, draw_end);
	draw_wall_texture(cub3d, x, draw_start, draw_end, &wall);
}

int	render_frame(void *param)
{
	t_cub3d	*cub3d;
	int		x;

	cub3d = (t_cub3d *)param;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cast_ray(cub3d, x);
		x++;
	}
	mlx_put_image_to_window(cub3d->data.mlx, cub3d->data.win,
		cub3d->data.img, 0, 0);
	return (0);
}
