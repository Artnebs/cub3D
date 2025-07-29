/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 13:10:56 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	calculate_wall_distance(t_cub3d *cub3d, t_ray_params *params,
		double *perp_wall_dist, int side)
{
	if (side == 0)
		*perp_wall_dist = (params->map[0] - cub3d->player.pos_x
				+ (1 - params->step[0]) / 2) / params->ray_dir[0];
	else
		*perp_wall_dist = (params->map[1] - cub3d->player.pos_y
				+ (1 - params->step[1]) / 2) / params->ray_dir[1];
}

void	calculate_draw_bounds(double perp_wall_dist, t_draw_params *params)
{
	params->line_height = (int)(WINDOW_HEIGHT / perp_wall_dist);
	params->draw_start = -(params->line_height) / 2 + WINDOW_HEIGHT / 2;
	if (params->draw_start < 0)
		params->draw_start = 0;
	params->draw_end = (params->line_height) / 2 + WINDOW_HEIGHT / 2;
	if (params->draw_end >= WINDOW_HEIGHT)
		params->draw_end = WINDOW_HEIGHT - 1;
}

void	calculate_wall_x(t_cub3d *cub3d, t_wall_x_params *params)
{
	if (params->side == 0)
		*params->wall_x = cub3d->player.pos_y + params->perp_wall_dist * params->ray_dir[1];
	else
		*params->wall_x = cub3d->player.pos_x + params->perp_wall_dist * params->ray_dir[0];
	*params->wall_x -= floor(*params->wall_x);
}

void	setup_wall_data(t_wall_data *wall, double wall_x, int side,
		double ray_dir[2])
{
	wall->tex_x = (int)(wall_x * TEXTURE_WIDTH);
	if (side == 0 && ray_dir[0] > 0)
		wall->tex_x = TEXTURE_WIDTH - wall->tex_x - 1;
	if (side == 1 && ray_dir[1] < 0)
		wall->tex_x = TEXTURE_WIDTH - wall->tex_x - 1;
	if (side == 0)
	{
		if (ray_dir[0] > 0)
			wall->tex_num = 2;
		else
			wall->tex_num = 3;
	}
	else
	{
		if (ray_dir[1] > 0)
			wall->tex_num = 1;
		else
			wall->tex_num = 0;
	}
	wall->side = side;
}

void	init_ray_direction(t_cub3d *cub3d, double camera_x, double ray_dir[2])
{
	ray_dir[0] = cub3d->player.dir_x + cub3d->player.plane_x * camera_x;
	ray_dir[1] = cub3d->player.dir_y + cub3d->player.plane_y * camera_x;
}

void	init_step_and_side_dist(t_cub3d *cub3d, t_ray_params *params)
{
	if (params->ray_dir[0] < 0)
	{
		params->step[0] = -1;
		params->side_dist[0] = (cub3d->player.pos_x - params->map[0]) * params->delta_dist[0];
	}
	else
	{
		params->step[0] = 1;
		params->side_dist[0] = (params->map[0] + 1.0 - cub3d->player.pos_x) * params->delta_dist[0];
	}
	if (params->ray_dir[1] < 0)
	{
		params->step[1] = -1;
		params->side_dist[1] = (cub3d->player.pos_y - params->map[1]) * params->delta_dist[1];
	}
	else
	{
		params->step[1] = 1;
		params->side_dist[1] = (params->map[1] + 1.0 - cub3d->player.pos_y) * params->delta_dist[1];
	}
}

void	perform_dda(t_cub3d *cub3d, t_dda_data *dda)
{
	int	hit = 0;
	
	while (hit == 0)
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
		if (cub3d->map.map[*dda->map_y][*dda->map_x] == '1')
			hit = 1;
	}
}