/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:09:10 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 16:47:02 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_line(t_cub3d *cub3d, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i,
				&cub3d->map.north_texture, "NO"));
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i,
				&cub3d->map.south_texture, "SO"));
	else if (line[i] == 'W' && line[i + 1] == 'E' && \
		line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i, &cub3d->map.west_texture, "WE"));
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i, &cub3d->map.east_texture, "EA"));
	else if (line[i] == 'F' && line[i + 1] == ' ')
		return (parse_color(cub3d, line + i, &cub3d->map.floor_color, "F"));
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (parse_color(cub3d, line + i, &cub3d->map.ceiling_color, "C"));
	else if (line[i] == '\n' || line[i] == '\0')
		return (1);
	else if (is_map_line(line))
		return (parse_map_line(cub3d, line));
	error_exit(cub3d,
		"Invalid line in map file: unknown identifier or character");
	return (0);
}

int	parse_map(t_cub3d *cub3d, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(cub3d, "Failed to open map file");
	cub3d->map.map = NULL;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->map.north_texture = NULL;
	cub3d->map.south_texture = NULL;
	cub3d->map.east_texture = NULL;
	cub3d->map.west_texture = NULL;
	cub3d->map.floor_color = -1;
	cub3d->map.ceiling_color = -1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (!parse_line(cub3d, line))
		{
			free(line);
			close(fd);
			error_exit(cub3d, "Failed to parse line in map file");
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
