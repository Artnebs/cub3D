/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:10:50 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 13:27:02 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_rotation(t_cub3d *cub3d, int keycode)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rotation_angle;

	if (keycode == 65361)
		rotation_angle = -ROTATION_SPEED;
	else if (keycode == 65363)
		rotation_angle = ROTATION_SPEED;
	else
		return ;
	old_dir_x = cub3d->player.dir_x;
	cub3d->player.dir_x = cub3d->player.dir_x * cos(rotation_angle)
		- cub3d->player.dir_y * sin(rotation_angle);
	cub3d->player.dir_y = old_dir_x * sin(rotation_angle)
		+ cub3d->player.dir_y * cos(rotation_angle);
	old_plane_x = cub3d->player.plane_x;
	cub3d->player.plane_x = cub3d->player.plane_x * cos(rotation_angle)
		- cub3d->player.plane_y * sin(rotation_angle);
	cub3d->player.plane_y = old_plane_x * sin(rotation_angle)
		+ cub3d->player.plane_y * cos(rotation_angle);
}
