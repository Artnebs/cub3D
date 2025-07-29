/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:15:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 12:25:39 by jeanb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_ray_params(t_cub3d *cub3d, int x, t_ray_params *params)
{
	double	camera_x;

	camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	init_ray_direction(cub3d, camera_x, params->ray_dir);
	params->map[0] = (int)cub3d->player.pos_x;
	params->map[1] = (int)cub3d->player.pos_y;
	params->delta_dist[0] = fabs(1 / params->ray_dir[0]);
	params->delta_dist[1] = fabs(1 / params->ray_dir[1]);
	init_step_and_side_dist(cub3d, params);
}

static void	perform_ray_calculation(t_cub3d *cub3d, t_ray_params *params,
	t_dda_data *dda, int *side)
{
	dda->map_x = &params->map[0];
	dda->map_y = &params->map[1];
	dda->side_dist_x = &params->side_dist[0];
	dda->side_dist_y = &params->side_dist[1];
	dda->delta_dist_x = params->delta_dist[0];
	dda->delta_dist_y = params->delta_dist[1];
	dda->step_x = params->step[0];
	dda->step_y = params->step[1];
	dda->side = side;
	perform_dda(cub3d, dda);
}

static void	setup_wall_rendering(t_cub3d *cub3d, t_ray_params *params,
	t_wall_data *wall, t_wall_render_params *wr_params)
{
	double			wall_x;
	t_wall_x_params	wall_x_params;

	wall_x_params.perp_wall_dist = wr_params->perp_wall_dist;
	wall_x_params.ray_dir[0] = params->ray_dir[0];
	wall_x_params.ray_dir[1] = params->ray_dir[1];
	wall_x_params.wall_x = &wall_x;
	wall_x_params.side = wr_params->side;
	calculate_wall_x(cub3d, &wall_x_params);
	setup_wall_data(wall, wall_x, wr_params->side, params->ray_dir);
}

void	cast_ray(t_cub3d *cub3d, int x)
{
	t_raycast_data	data;

	init_ray_params(cub3d, x, &data.params);
	perform_ray_calculation(cub3d, &data.params, &data.dda, &data.side);
	calculate_wall_distance(cub3d, &data.params,
		&data.perp_wall_dist, data.side);
	calculate_draw_bounds(data.perp_wall_dist, &data.draw_params);
	data.wr_params = (t_wall_render_params){data.perp_wall_dist, data.side};
	setup_wall_rendering(cub3d, &data.params,
		&data.wall, &data.wr_params);
	draw_floor_ceiling(cub3d, x, data.draw_params.draw_start,
		data.draw_params.draw_end);
	data.wall_params.x = x;
	data.wall_params.draw_start = data.draw_params.draw_start;
	data.wall_params.draw_end = data.draw_params.draw_end;
	data.wall_params.wall = &data.wall;
	draw_wall_texture(cub3d, &data.wall_params);
}
