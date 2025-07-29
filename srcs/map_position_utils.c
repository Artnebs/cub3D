/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_position_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 17:30:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 18:46:28 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
