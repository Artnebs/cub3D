/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:08:45 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 12:58:34 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	error_exit(t_cub3d *cub3d, const char *message)
{
	if (cub3d)
	{
		if (cub3d->data.mlx)
		{
			if (cub3d->data.win)
				mlx_destroy_window(cub3d->data.mlx, cub3d->data.win);
			if (cub3d->data.img)
				mlx_destroy_image(cub3d->data.mlx, cub3d->data.img);
			mlx_destroy_display(cub3d->data.mlx);
			free(cub3d->data.mlx);
		}
		free_textures(cub3d);
		gc_cleanup(cub3d);
	}
	write(STDERR_FILENO, "Error\n", 6);
	if (message)
	{
		write(STDERR_FILENO, message, ft_strlen(message));
		write(STDERR_FILENO, "\n", 1);
	}
	exit(1);
}
