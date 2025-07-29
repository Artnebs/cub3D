/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:20:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 13:24:22 by jmader           ###   ########.fr       */
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

void	check_position(t_cub3d *cub3d, int i, int j, int len)
{
	if (cub3d->map.map[i][j] == '0' || cub3d->map.map[i][j] == 'N'
		|| cub3d->map.map[i][j] == 'S' || cub3d->map.map[i][j] == 'E'
		|| cub3d->map.map[i][j] == 'W')
	{
		check_borders(cub3d, i, j, len);
		check_adjacent_spaces(cub3d, i, j, len);
	}
}

int	get_char_at_pos(t_cub3d *cub3d, int row, int col)
{
	if (row < 0 || row >= cub3d->map.height)
		return (' ');
	if (col < 0 || col >= (int)ft_strlen(cub3d->map.map[row]))
		return (' ');
	return (cub3d->map.map[row][col]);
}

int	is_open_space_adjacent(t_cub3d *cub3d, int i, int j)
{
	char	adjacent_chars[4];

	adjacent_chars[0] = get_char_at_pos(cub3d, i - 1, j);
	adjacent_chars[1] = get_char_at_pos(cub3d, i + 1, j);
	adjacent_chars[2] = get_char_at_pos(cub3d, i, j - 1);
	adjacent_chars[3] = get_char_at_pos(cub3d, i, j + 1);
	if (adjacent_chars[0] == ' ' || adjacent_chars[0] == '\t')
		return (1);
	if (adjacent_chars[1] == ' ' || adjacent_chars[1] == '\t')
		return (1);
	if (adjacent_chars[2] == ' ' || adjacent_chars[2] == '\t')
		return (1);
	if (adjacent_chars[3] == ' ' || adjacent_chars[3] == '\t')
		return (1);
	return (0);
}
