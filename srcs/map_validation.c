/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:20 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 20:12:11 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	process_player_position(t_cub3d *cub3d, int i, int j,
		int *player_found)
{
	if (*player_found)
		error_exit(cub3d, "Multiple player positions found");
	*player_found = 1;
	cub3d->player.pos_x = j + 0.5;
	cub3d->player.pos_y = i + 0.5;
	set_player_direction(cub3d, cub3d->map.map[i][j]);
}

static int	check_map_chars(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	player_found;

	player_found = 0;
	i = 0;
	while (i < cub3d->map.height)
	{
		j = 0;
		while (cub3d->map.map[i][j])
		{
			if (cub3d->map.map[i][j] == 'N' || cub3d->map.map[i][j] == 'S'
				|| cub3d->map.map[i][j] == 'E'
				|| cub3d->map.map[i][j] == 'W')
				process_player_position(cub3d, i, j, &player_found);
			else if (!is_valid_char(cub3d->map.map[i][j]))
				error_exit(cub3d, "Invalid character found in map");
			j++;
		}
		i++;
	}
	if (!player_found)
		error_exit(cub3d, "No player starting position found in map");
	return (1);
}

static int	check_walls(t_cub3d *cub3d)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	while (i < cub3d->map.height)
	{
		j = 0;
		len = ft_strlen(cub3d->map.map[i]);
		while (j < len)
		{
			check_position(cub3d, i, j, len);
			j++;
		}
		i++;
	}
	return (1);
}

static int	validate_textures(t_cub3d *cub3d)
{
	if (!cub3d->map.north_texture)
		error_exit(cub3d, "Missing NO texture");
	if (!cub3d->map.south_texture)
		error_exit(cub3d, "Missing SO texture");
	if (!cub3d->map.east_texture)
		error_exit(cub3d, "Missing EA texture");
	if (!cub3d->map.west_texture)
		error_exit(cub3d, "Missing WE texture");
	return (1);
}

int	validate_map(t_cub3d *cub3d)
{
	validate_textures(cub3d);
	validate_colors(cub3d);
	if (!cub3d->map.map)
		error_exit(cub3d, "No map found in file");
	if (cub3d->map.height == 0)
		error_exit(cub3d, "Empty map");
	check_map_chars(cub3d);
	check_walls(cub3d);
	return (1);
}
