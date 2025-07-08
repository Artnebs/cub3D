/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:32 by jmader            #+#    #+#             */
/*   Updated: 2025/05/20 15:47:20 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"
#include "cub3d.h"

static void init_cub3d(t_cub3d *cub3d)
{
	cub3d->garbage = NULL;
	cub3d->data.mlx = NULL;
	cub3d->data.win = NULL;
	cub3d->data.img = NULL;
	cub3d->data.addr = NULL;
	cub3d->map.map = NULL;
	cub3d->map.north_texture = NULL;
	cub3d->map.south_texture = NULL;
	cub3d->map.east_texture = NULL;
	cub3d->map.west_texture = NULL;
}

int main(int argc, char **argv)
{
	t_cub3d cub3d;

	if (argc != 2)
		error_exit(NULL, "Usage: ./cub3D <map_file>");
	
	init_cub3d(&cub3d);
	
	if (!parse_map(&cub3d, argv[1]))
		error_exit(&cub3d, "Map parsing failed");
	
	if (!validate_map(&cub3d))
		error_exit(&cub3d, "Map validation failed");
	
	if (!load_textures(&cub3d))
		error_exit(&cub3d, "Texture loading failed");
	
	init_raycasting(&cub3d);
	
	cub3d.data.mlx = mlx_init();
	if (!cub3d.data.mlx)
		error_exit(&cub3d, "MLX initialization failed");
	
	cub3d.data.win = mlx_new_window(cub3d.data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub3d.data.win)
		error_exit(&cub3d, "Window creation failed");
	
	cub3d.data.img = mlx_new_image(cub3d.data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d.data.img)
		error_exit(&cub3d, "Image creation failed");
	
	cub3d.data.addr = mlx_get_data_addr(cub3d.data.img, &cub3d.data.bits_per_pixel,
		&cub3d.data.line_length, &cub3d.data.endian);
	
	mlx_hook(cub3d.data.win, 2, 1L << 0, handle_keypress, &cub3d);
	mlx_hook(cub3d.data.win, 17, 0, handle_window_close, &cub3d);
	mlx_loop_hook(cub3d.data.mlx, render_frame, &cub3d);
	
	mlx_loop(cub3d.data.mlx);
	
	return (0);
}
