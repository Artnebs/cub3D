/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:25:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 12:26:06 by jeanb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_position(t_cub3d *cub3d, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= cub3d->map.width
		|| map_y < 0 || map_y >= cub3d->map.height)
		return (0);
	if (!cub3d->map.map[map_y] || map_x >= (int)ft_strlen(cub3d->map.map[map_y]))
		return (0);
	return (cub3d->map.map[map_y][map_x] != '1');
}

void	calculate_movement(t_cub3d *cub3d, int keycode, double *new_x,
			double *new_y)
{
	if (keycode == 119)
	{
		*new_x = cub3d->player.pos_x + cub3d->player.dir_x * MOVE_SPEED;
		*new_y = cub3d->player.pos_y + cub3d->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 115)
	{
		*new_x = cub3d->player.pos_x - cub3d->player.dir_x * MOVE_SPEED;
		*new_y = cub3d->player.pos_y - cub3d->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 97)
	{
		*new_x = cub3d->player.pos_x + cub3d->player.dir_y * MOVE_SPEED;
		*new_y = cub3d->player.pos_y - cub3d->player.dir_x * MOVE_SPEED;
	}
	else if (keycode == 100)
	{
		*new_x = cub3d->player.pos_x - cub3d->player.dir_y * MOVE_SPEED;
		*new_y = cub3d->player.pos_y + cub3d->player.dir_x * MOVE_SPEED;
	}
} 