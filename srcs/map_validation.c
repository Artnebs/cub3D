/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:11:20 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/23 17:11:38 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ');
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
					return (0);
				player_found = 1;
				cub3d->player.pos_x = j + 0.5;
				cub3d->player.pos_y = i + 0.5;
				set_player_direction(cub3d, cub3d->map.map[i][j]);
			}
			else if (!is_valid_char(cub3d->map.map[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (player_found);
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
				if (i == 0 || i == cub3d->map.height - 1 || j == 0 || j == len - 1)
					return (0);
				if (i > 0 && (j >= (int)ft_strlen(cub3d->map.map[i - 1])
					|| cub3d->map.map[i - 1][j] == ' '))
					return (0);
				if (i < cub3d->map.height - 1 && (j >= (int)ft_strlen(cub3d->map.map[i + 1])
					|| cub3d->map.map[i + 1][j] == ' '))
					return (0);
				if (j > 0 && cub3d->map.map[i][j - 1] == ' ')
					return (0);
				if (j < len - 1 && cub3d->map.map[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int	validate_map(t_cub3d *cub3d)
{
	if (!cub3d->map.north_texture || !cub3d->map.south_texture
		|| !cub3d->map.east_texture || !cub3d->map.west_texture)
		return (0);
	if (!check_map_chars(cub3d))
		return (0);
	if (!check_walls(cub3d))
		return (0);
	return (1);
}
