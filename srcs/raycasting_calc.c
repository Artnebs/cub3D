/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 17:34:09 by anebbou          ###   ########.fr       */
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
		*params->wall_x = cub3d->player.pos_y + params->perp_wall_dist
			* params->ray_dir[1];
	else
		*params->wall_x = cub3d->player.pos_x + params->perp_wall_dist
			* params->ray_dir[0];
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
