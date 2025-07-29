/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:20:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 20:12:10 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_map_data(t_cub3d *cub3d)
{
	cub3d->map.map = NULL;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->map.north_texture = NULL;
	cub3d->map.south_texture = NULL;
	cub3d->map.east_texture = NULL;
	cub3d->map.west_texture = NULL;
	cub3d->map.floor_color = -1;
	cub3d->map.ceiling_color = -1;
}
