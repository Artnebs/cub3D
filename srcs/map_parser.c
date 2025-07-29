/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:09:10 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 12:25:39 by jeanb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	error_exit(cub3d, "Invalid line in map file");
	return (0);
}

static void	init_map_data(t_cub3d *cub3d)
{
	cub3d->map.map = NULL;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->map.north_texture = NULL;
	cub3d->map.south_texture = NULL;
	cub3d->map.east_texture = NULL;
	cub3d->map.west_texture = NULL;
	cub3d->map.floor_color = -1;
	cub3d->map.ceiling_color = -1;
}

static void	process_line(t_cub3d *cub3d, char *line, int fd)
{
	strip_newline(line);
	if (!parse_line(cub3d, line))
	{
		free(line);
		close(fd);
		error_exit(cub3d, "Failed to parse line in map file");
	}
}

int	parse_map(t_cub3d *cub3d, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit(cub3d, "Failed to open map file");
	init_map_data(cub3d);
	line = get_next_line(fd);
	while (line != NULL)
	{
		process_line(cub3d, line, fd);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (1);
}
