/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:20:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 20:49:20 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'E' || c == 'W' || c == ' ' || c == '\t');
}

int	check_borders(t_cub3d *cub3d, int i, int j, int len)
{
	if (i == 0 || i == cub3d->map.height - 1 || j == 0 || j == len - 1)
	{
		error_exit(cub3d, "Map border validation failed");
		return (0);
	}
	return (1);
}

int	check_adjacent_spaces(t_cub3d *cub3d, int i, int j, int len)
{
	if (i > 0 && (j >= (int)ft_strlen(cub3d->map.map[i - 1])
			|| cub3d->map.map[i - 1][j] == ' '
		|| cub3d->map.map[i - 1][j] == '\t'))
		error_exit(cub3d, "Map wall validation failed");
	if (i < cub3d->map.height - 1 && (j >= (int)ft_strlen(cub3d->map.map[i + 1])
			|| cub3d->map.map[i + 1][j] == ' '
		|| cub3d->map.map[i + 1][j] == '\t'))
		error_exit(cub3d, "Map wall validation failed");
	if (j > 0 && (cub3d->map.map[i][j - 1] == ' '
		|| cub3d->map.map[i][j - 1] == '\t'))
		error_exit(cub3d, "Map wall validation failed");
	if (j < len - 1 && (cub3d->map.map[i][j + 1] == ' '
		|| cub3d->map.map[i][j + 1] == '\t'))
		error_exit(cub3d, "Map wall validation failed");
	return (1);
}

int	validate_colors(t_cub3d *cub3d)
{
	if (cub3d->map.floor_color == -1)
		error_exit(cub3d, "Missing F color");
	if (cub3d->map.ceiling_color == -1)
		error_exit(cub3d, "Missing C color");
	return (1);
}
