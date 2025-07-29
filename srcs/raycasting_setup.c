/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:50:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 18:45:24 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
		params->side_dist[0] = (cub3d->player.pos_x - params->map[0])
			* params->delta_dist[0];
	}
	else
	{
		params->step[0] = 1;
		params->side_dist[0] = (params->map[0] + 1.0 - cub3d->player.pos_x)
			* params->delta_dist[0];
	}
	if (params->ray_dir[1] < 0)
	{
		params->step[1] = -1;
		params->side_dist[1] = (cub3d->player.pos_y - params->map[1])
			* params->delta_dist[1];
	}
	else
	{
		params->step[1] = 1;
		params->side_dist[1] = (params->map[1] + 1.0 - cub3d->player.pos_y)
			* params->delta_dist[1];
	}
}

void	perform_dda(t_cub3d *cub3d, t_dda_data *dda)
{
	int	hit;

	hit = 0;
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
