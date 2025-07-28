/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:10:50 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/28 18:11:49 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_position(t_cub3d *cub3d, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= cub3d->map.width
		|| map_y < 0 || map_y >= cub3d->map.height)
		return (0);
	if (!cub3d->map.map[map_y] || \
		map_x >= (int)ft_strlen(cub3d->map.map[map_y]))
		return (0);
	return (cub3d->map.map[map_y][map_x] != '1');
}

static void	handle_movement(t_cub3d *cub3d, int keycode)
{
	double	new_x;
	double	new_y;

	if (keycode == 119)
	{
		new_x = cub3d->player.pos_x + cub3d->player.dir_x * MOVE_SPEED;
		new_y = cub3d->player.pos_y + cub3d->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 115)
	{
		new_x = cub3d->player.pos_x - cub3d->player.dir_x * MOVE_SPEED;
		new_y = cub3d->player.pos_y - cub3d->player.dir_y * MOVE_SPEED;
	}
	else if (keycode == 97)
	{
		new_x = cub3d->player.pos_x + cub3d->player.dir_y * MOVE_SPEED;
		new_y = cub3d->player.pos_y - cub3d->player.dir_x * MOVE_SPEED;
	}
	else if (keycode == 100)
	{
		new_x = cub3d->player.pos_x - cub3d->player.dir_y * MOVE_SPEED;
		new_y = cub3d->player.pos_y + cub3d->player.dir_x * MOVE_SPEED;
	}
	else
		return ;
	if (is_valid_position(cub3d, new_x, new_y))
	{
		cub3d->player.pos_x = new_x;
		cub3d->player.pos_y = new_y;
	}
}

static void	handle_rotation(t_cub3d *cub3d, int keycode)
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

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == 65307)
		handle_window_close(cub3d);
	else if (keycode == 119 || keycode == 115 \
		|| keycode == 97 || keycode == 100)
		handle_movement(cub3d, keycode);
	else if (keycode == 65361 || keycode == 65363)
		handle_rotation(cub3d, keycode);
	return (0);
}

int	handle_window_close(t_cub3d *cub3d)
{
	if (cub3d->data.mlx)
	{
		if (cub3d->data.win)
			mlx_destroy_window(cub3d->data.mlx, cub3d->data.win);
		if (cub3d->data.img)
			mlx_destroy_image(cub3d->data.mlx, cub3d->data.img);
		free_textures(cub3d);
		mlx_destroy_display(cub3d->data.mlx);
		free(cub3d->data.mlx);
	}
	gc_cleanup(cub3d);
	exit(0);
	return (0);
}
