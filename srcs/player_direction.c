/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:20:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 13:25:55 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_player_north(t_cub3d *cub3d)
{
	cub3d->player.dir_x = 0;
	cub3d->player.dir_y = -1;
	cub3d->player.plane_x = 0.66;
	cub3d->player.plane_y = 0;
}

static void	set_player_south(t_cub3d *cub3d)
{
	cub3d->player.dir_x = 0;
	cub3d->player.dir_y = 1;
	cub3d->player.plane_x = -0.66;
	cub3d->player.plane_y = 0;
}

static void	set_player_east(t_cub3d *cub3d)
{
	cub3d->player.dir_x = 1;
	cub3d->player.dir_y = 0;
	cub3d->player.plane_x = 0;
	cub3d->player.plane_y = 0.66;
}

static void	set_player_west(t_cub3d *cub3d)
{
	cub3d->player.dir_x = -1;
	cub3d->player.dir_y = 0;
	cub3d->player.plane_x = 0;
	cub3d->player.plane_y = -0.66;
}

void	set_player_direction(t_cub3d *cub3d, char direction)
{
	if (direction == 'N')
		set_player_north(cub3d);
	else if (direction == 'S')
		set_player_south(cub3d);
	else if (direction == 'E')
		set_player_east(cub3d);
	else if (direction == 'W')
		set_player_west(cub3d);
}
