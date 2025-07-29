/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:20 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 13:10:56 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"





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
				|| cub3d->map.map[i][j] == 'E' || cub3d->map.map[i][j] == 'W')
			{
				if (player_found)
					error_exit(cub3d, "Multiple player starting positions found");
				player_found = 1;
				cub3d->player.pos_x = j + 0.5;
				cub3d->player.pos_y = i + 0.5;
				set_player_direction(cub3d, cub3d->map.map[i][j]);
			}
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
			if (cub3d->map.map[i][j] == '0' || cub3d->map.map[i][j] == 'N'
				|| cub3d->map.map[i][j] == 'S' || cub3d->map.map[i][j] == 'E'
				|| cub3d->map.map[i][j] == 'W')
			{
				if (i == 0 || i == cub3d->map.height - 1 || \
					j == 0 || j == len - 1)
					error_exit(cub3d, "Map is not surrounded by walls: open space at border");
				if (i > 0 && (j >= (int)ft_strlen(cub3d->map.map[i - 1])
						|| cub3d->map.map[i - 1][j] == ' ' || cub3d->map.map[i - 1][j] == '\t'))
					error_exit(cub3d, "Map is not surrounded by walls: open space adjacent to void");
				if (i < cub3d->map.height - 1 && \
					(j >= (int)ft_strlen(cub3d->map.map[i + 1])
						|| cub3d->map.map[i + 1][j] == ' ' || cub3d->map.map[i + 1][j] == '\t'))
					error_exit(cub3d, "Map is not surrounded by walls: open space adjacent to void");
				if (j > 0 && (cub3d->map.map[i][j - 1] == ' ' || cub3d->map.map[i][j - 1] == '\t'))
					error_exit(cub3d, "Map is not surrounded by walls: open space adjacent to void");
				if (j < len - 1 && (cub3d->map.map[i][j + 1] == ' ' || cub3d->map.map[i][j + 1] == '\t'))
					error_exit(cub3d, "Map is not surrounded by walls: open space adjacent to void");
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_cub3d *cub3d)
{
	if (!cub3d->map.north_texture)
		error_exit(cub3d, "Missing NO texture");
	if (!cub3d->map.south_texture)
		error_exit(cub3d, "Missing SO texture");
	if (!cub3d->map.east_texture)
		error_exit(cub3d, "Missing EA texture");
	if (!cub3d->map.west_texture)
		error_exit(cub3d, "Missing WE texture");
	if (cub3d->map.floor_color == -1)
		error_exit(cub3d, "Missing F color");
	if (cub3d->map.ceiling_color == -1)
		error_exit(cub3d, "Missing C color");
	if (!cub3d->map.map)
		error_exit(cub3d, "No map found in file");
	if (cub3d->map.height == 0)
		error_exit(cub3d, "Empty map");
	check_map_chars(cub3d);  // This now exits on error
	check_walls(cub3d);      // This now exits on error
	return (1);
}
