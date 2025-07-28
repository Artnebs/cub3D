/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:20 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/28 18:41:26 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

static void	set_player_direction(t_cub3d *cub3d, char direction)
{
	if (direction == 'N')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = -1;
		cub3d->player.plane_x = 0.66;
		cub3d->player.plane_y = 0;
	}
	else if (direction == 'S')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = 1;
		cub3d->player.plane_x = -0.66;
		cub3d->player.plane_y = 0;
	}
	else if (direction == 'E')
	{
		cub3d->player.dir_x = 1;
		cub3d->player.dir_y = 0;
		cub3d->player.plane_x = 0;
		cub3d->player.plane_y = 0.66;
	}
	else if (direction == 'W')
	{
		cub3d->player.dir_x = -1;
		cub3d->player.dir_y = 0;
		cub3d->player.plane_x = 0;
		cub3d->player.plane_y = -0.66;
	}
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

static int	get_char_at_pos(t_cub3d *cub3d, int row, int col)
{
	if (row < 0 || row >= cub3d->map.height)
		return (' ');
	if (col < 0 || col >= (int)ft_strlen(cub3d->map.map[row]))
		return (' ');
	return (cub3d->map.map[row][col]);
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
				if (get_char_at_pos(cub3d, i - 1, j) == ' ' || get_char_at_pos(cub3d, i - 1, j) == '\t')
					error_exit(cub3d, "Map is not surrounded by walls: open space adjacent to void");
				if (get_char_at_pos(cub3d, i + 1, j) == ' ' || get_char_at_pos(cub3d, i + 1, j) == '\t')
					error_exit(cub3d, "Map is not surrounded by walls: open space adjacent to void");
				if (get_char_at_pos(cub3d, i, j - 1) == ' ' || get_char_at_pos(cub3d, i, j - 1) == '\t')
					error_exit(cub3d, "Map is not surrounded by walls: open space adjacent to void");
				if (get_char_at_pos(cub3d, i, j + 1) == ' ' || get_char_at_pos(cub3d, i, j + 1) == '\t')
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
