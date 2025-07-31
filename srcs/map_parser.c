/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:09:10 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/31 12:45:53 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_texture_line(t_cub3d *cub3d, char *line, int i)
{
	if (ft_strncmp(line + i, "NO ", 3) == 0)
		return (parse_texture(cub3d, line + i,
				&cub3d->map.north_texture, "NO"));
	else if (ft_strncmp(line + i, "SO ", 3) == 0)
		return (parse_texture(cub3d, line + i,
				&cub3d->map.south_texture, "SO"));
	else if (ft_strncmp(line + i, "WE ", 3) == 0)
		return (parse_texture(cub3d, line + i, &cub3d->map.west_texture, "WE"));
	else if (ft_strncmp(line + i, "EA ", 3) == 0)
		return (parse_texture(cub3d, line + i, &cub3d->map.east_texture, "EA"));
	return (0);
}

static int	parse_color_line(t_cub3d *cub3d, char *line, int i)
{
	if (ft_strncmp(line + i, "F ", 2) == 0)
		return (parse_color(cub3d, line + i, &cub3d->map.floor_color, "F"));
	else if (ft_strncmp(line + i, "C ", 2) == 0)
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
	if (ft_strchr(line, '1') || ft_strchr(line, '0') || ft_strchr(line, 'N')
		|| ft_strchr(line, 'S') || ft_strchr(line, 'E') || ft_strchr(line, 'W'))
		error_exit(cub3d, "Invalid character was used for texture or map");
	else
		error_exit(cub3d, "Invalid line in map file: unknown identifier");
	return (0);
}

static void	process_map_lines(t_cub3d *cub3d, int fd)
{
	char	*line;
	int		map_started;

	map_started = 0;
	line = gc_get_next_line(cub3d, fd);
	while (line != NULL)
	{
		strip_newline(line);
		if (!map_started && is_map_line(line) && line[0] != '\0')
			map_started = 1;
		if (map_started && !is_map_line(line) && line[0] != '\0')
		{
			close(fd);
			error_exit(cub3d, "Invalid map placement");
		}
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
