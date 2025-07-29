/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:55 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 12:39:34 by jeanb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_raycasting(t_cub3d *cub3d)
{
	(void)cub3d;
}

void	draw_floor_ceiling(t_cub3d *cub3d, int x, int draw_start,
		int draw_end)
{
	int	y;

	y = 0;
	while (y < draw_start)
	{
		if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH)
			*(int *)(cub3d->data.addr + (y * cub3d->data.line_length
					+ x * (cub3d->data.bits_per_pixel / 8)))
				= cub3d->map.ceiling_color;
		y++;
	}
	y = draw_end;
	while (y < WINDOW_HEIGHT)
	{
		if (y >= 0 && y < WINDOW_HEIGHT && x >= 0 && x < WINDOW_WIDTH)
			*(int *)(cub3d->data.addr + (y * cub3d->data.line_length
					+ x * (cub3d->data.bits_per_pixel / 8)))
				= cub3d->map.floor_color;
		y++;
	}
}

void	draw_wall_texture(t_cub3d *cub3d, t_wall_draw_params *params)
{
	int		y;
	int		tex_y;
	int		color;
	double	step;
	double	tex_pos;

	step = 1.0 * TEXTURE_HEIGHT / (params->draw_end - params->draw_start);
	tex_pos = (params->draw_start - WINDOW_HEIGHT / 2
			+ (params->draw_end - params->draw_start) / 2) * step;
	y = params->draw_start;
	while (y < params->draw_end)
	{
		tex_y = (int)tex_pos & (TEXTURE_HEIGHT - 1);
		tex_pos += step;
		if (y >= 0 && y < WINDOW_HEIGHT && params->x >= 0 && params->x < WINDOW_WIDTH)
		{
			color = get_texture_color(&cub3d->map.textures[params->wall->tex_num],
			params->wall->tex_x, tex_y);
			if (params->wall->side == 1)
				color = (color >> 1) & 8355711;
			*(int *)(cub3d->data.addr + (y * cub3d->data.line_length
					+ params->x * (cub3d->data.bits_per_pixel / 8))) = color;
		}
		y++;
	}
}



int	render_frame(void *param)
{
	t_cub3d	*cub3d;
	int		x;

	cub3d = (t_cub3d *)param;
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		cast_ray(cub3d, x);
		x++;
	}
		mlx_put_image_to_window(cub3d->data.mlx, cub3d->data.win,
		cub3d->data.img, 0, 0);
	return (0);
}
