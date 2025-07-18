/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:27:32 by jmader            #+#    #+#             */
/*   Updated: 2025/07/18 16:55:06 by jeanb            ###   ########.fr       */
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

static int render_frame_wrapper(void *param)
{
    return render_frame((t_cub3d *)param);
}

int main(int argc, char **argv)
{
	t_cub3d cub3d;

	if (argc != 2)
		error_exit(NULL, "Usage: ./cub3D <map_file>");
	
	printf("Parsing map...\n");
	init_cub3d(&cub3d);
	
	if (!parse_map(&cub3d, argv[1]))
		error_exit(&cub3d, "Map parsing failed");
	
	printf("Validating map...\n");
	if (!validate_map(&cub3d))
		error_exit(&cub3d, "Map validation failed");
	
	printf("Loading textures...\n");
	if (!load_textures(&cub3d))
		error_exit(&cub3d, "Texture loading failed");
	
	printf("Init raycasting...\n");
	init_raycasting(&cub3d);
	
	printf("MLX init...\n");
	cub3d.data.mlx = mlx_init();
	if (!cub3d.data.mlx)
		error_exit(&cub3d, "MLX initialization failed");
	
	printf("Creating window...\n");
	cub3d.data.win = mlx_new_window(cub3d.data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!cub3d.data.win)
		error_exit(&cub3d, "Window creation failed");
	
	printf("Creating image...\n");
	cub3d.data.img = mlx_new_image(cub3d.data.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!cub3d.data.img)
		error_exit(&cub3d, "Image creation failed");
	
	printf("Getting image data address...\n");
	cub3d.data.addr = mlx_get_data_addr(cub3d.data.img, &cub3d.data.bits_per_pixel,
		&cub3d.data.line_length, &cub3d.data.endian);
	
	printf("Setting up hooks...\n");
	mlx_hook(cub3d.data.win, 2, 1L << 0, handle_keypress, &cub3d);
	mlx_hook(cub3d.data.win, 17, 0, handle_window_close, &cub3d);
	mlx_loop_hook(cub3d.data.mlx, render_frame_wrapper, &cub3d);
	
	printf("Entering main loop...\n");
	mlx_loop(cub3d.data.mlx);
	
	return (0);
}
