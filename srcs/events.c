/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:10:50 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 12:57:57 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	handle_keypress(int keycode, t_cub3d *cub3d)
{
	if (keycode == 65307)
		handle_window_close(cub3d);
	else if (keycode == 119 || keycode == 115
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
