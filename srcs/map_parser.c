/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:09:10 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 14:35:51 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_texture_line(t_cub3d *cub3d, char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i,
				&cub3d->map.north_texture, "NO"));
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i,
				&cub3d->map.south_texture, "SO"));
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i, &cub3d->map.west_texture, "WE"));
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i, &cub3d->map.east_texture, "EA"));
	return (0);
}

static int	parse_color_line(t_cub3d *cub3d, char *line, int i)
{
	if (line[i] == 'F' && line[i + 1] == ' ')
		return (parse_color(cub3d, line + i, &cub3d->map.floor_color, "F"));
	else if (line[i] == 'C' && line[i + 1] == ' ')
		return (parse_color(cub3d, line + i, &cub3d->map.ceiling_color, "C"));
	return (0);
}

static int	parse_line(t_cub3d *cub3d, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (parse_texture_line(cub3d, line, i))
		return (1);
	if (parse_color_line(cub3d, line, i))
		return (1);
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	if (is_map_line(line))
		return (parse_map_line(cub3d, line));
	error_exit(cub3d,
		"Invalid line in map file: unknown identifier or character");
	return (0);
}

static void	process_map_lines(t_cub3d *cub3d, int fd)
{
	char	*line;

	line = gc_get_next_line(cub3d, fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (!parse_line(cub3d, line))
		{
			close(fd);
			error_exit(cub3d, "Failed to parse line in map file");
		}
		line = gc_get_next_line(cub3d, fd);
	}
}

int	parse_map(t_cub3d *cub3d, const char *filename)
{
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(cub3d, "Failed to open map file");
	init_map_data(cub3d);
	process_map_lines(cub3d, fd);
	close(fd);
	return (1);
}
