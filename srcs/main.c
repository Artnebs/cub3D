/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:07:30 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 12:21:52 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void init_cub3d(t_cub3d *cub3d)
{
	cub3d->data.mlx = NULL;
	cub3d->data.win = NULL;
	cub3d->data.img = NULL;
	cub3d->data.addr = NULL;
	cub3d->player.pos_x = 0.0;
	cub3d->player.pos_y = 0.0;
	cub3d->player.dir_x = -1.0;
	cub3d->player.dir_y = 0.0;
	cub3d->player.plane_x = 0.0;
	cub3d->player.plane_y = 0.66;
	cub3d->map.map = NULL;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->map.north_texture = NULL;
	cub3d->map.south_texture = NULL;
	cub3d->map.east_texture = NULL;
	cub3d->map.west_texture = NULL;
	cub3d->map.floor_color = -1;
	cub3d->map.ceiling_color = -1;
	cub3d->garbage = NULL;
}

static int validate_arguments(int argc, char **argv)
{
	int fd;

	if (argc != 2)
	{
		write(STDERR_FILENO, "Error\nUsage: ./cub3D <map.cub>\n", 29);
		return (0);
	}
	if (!is_valid_cub_file(argv[1]))
	{
		write(STDERR_FILENO, "Error\nInvalid file extension. Use .cub\n", 38);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(STDERR_FILENO, "Error\nFailed to open file\n", 26);
		return (0);
	}
	close(fd);
	return (1);
}

static void setup_mlx(t_cub3d *cub3d)
{
	cub3d->data.mlx = mlx_init();
	if (!cub3d->data.mlx)
		error_exit(cub3d, "Failed to initialize MLX");
	cub3d->data.win = mlx_new_window(cub3d->data.mlx, WINDOW_WIDTH,
									 WINDOW_HEIGHT, "cub3D");
	if (!cub3d->data.win)
		error_exit(cub3d, "Failed to create window");
	cub3d->data.img = mlx_new_image(cub3d->data.mlx, WINDOW_WIDTH,
									WINDOW_HEIGHT);
	if (!cub3d->data.img)
		error_exit(cub3d, "Failed to create image");
	cub3d->data.addr = mlx_get_data_addr(cub3d->data.img,
										 &cub3d->data.bits_per_pixel, &cub3d->data.line_length,
										 &cub3d->data.endian);
	if (!cub3d->data.addr)
		error_exit(cub3d, "Failed to get image data address");
}

int main(int argc, char **argv)
{
	t_cub3d cub3d;

	if (!validate_arguments(argc, argv))
		return (1);
	init_cub3d(&cub3d);
	if (!static_parse_map(&cub3d, argv[1]))
		return (1);
	validate_map(&cub3d);
	setup_mlx(&cub3d);
	if (!load_textures(&cub3d))
		error_exit(&cub3d, "Failed to load textures");
	init_raycasting(&cub3d);
	mlx_hook(cub3d.data.win, 2, 1L << 0, handle_keypress, &cub3d);
	mlx_hook(cub3d.data.win, 17, 1L << 17, handle_window_close, &cub3d);
	mlx_loop_hook(cub3d.data.mlx, render_frame, &cub3d);
	mlx_loop(cub3d.data.mlx);
	return (0);
}
