/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:00:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 13:00:00 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_static_parser(t_static_parser *parser)
{
	int	i;

	i = 0;
	while (i < MAX_MAP_SIZE)
	{
		parser->lines[i][0] = '\0';
		i++;
	}
	parser->north_path[0] = '\0';
	parser->south_path[0] = '\0';
	parser->east_path[0] = '\0';
	parser->west_path[0] = '\0';
	parser->floor_r = -1;
	parser->floor_g = -1;
	parser->floor_b = -1;
	parser->ceiling_r = -1;
	parser->ceiling_g = -1;
	parser->ceiling_b = -1;
	parser->line_count = 0;
	parser->has_north = 0;
	parser->has_south = 0;
	parser->has_east = 0;
	parser->has_west = 0;
	parser->has_floor = 0;
	parser->has_ceiling = 0;
	parser->player_x = -1;
	parser->player_y = -1;
	parser->player_dir = '\0';
	parser->map_start_line = -1;
	parser->map_width = 0;
	parser->map_height = 0;
}

static int	read_file_to_buffer(const char *filename, t_static_parser *parser)
{
	int		fd;
	char	buffer[MAX_LINE_LENGTH];
	int		bytes_read;
	int		line_pos;
	int		i;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	bytes_read = read(fd, buffer, MAX_LINE_LENGTH - 1);
	line_pos = 0;
	i = 0;
	while (i < bytes_read && parser->line_count < MAX_MAP_SIZE)
	{
		if (buffer[i] == '\n')
		{
			parser->lines[parser->line_count][line_pos] = '\0';
			parser->line_count++;
			line_pos = 0;
		}
		else if (line_pos < MAX_LINE_LENGTH - 1)
		{
			parser->lines[parser->line_count][line_pos] = buffer[i];
			line_pos++;
		}
		i++;
	}
	if (line_pos > 0)
	{
		parser->lines[parser->line_count][line_pos] = '\0';
		parser->line_count++;
	}
	close(fd);
	return (1);
}

static int	parse_texture_static(char *line, char *dest, const char *type)
{
	int	i;
	int	j;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(line + i, type, ft_strlen(type)) != 0)
		return (0);
	i += ft_strlen(type);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	j = 0;
	while (line[i] && line[i] != ' ' && line[i] != '\t' && j < MAX_PATH_LENGTH - 1)
	{
		dest[j] = line[i];
		i++;
		j++;
	}
	dest[j] = '\0';
	return (1);
}

static int	parse_color_static(char *line, int *r, int *g, int *b, const char *type)
{
	int		i;
	char	*rgb_str;
	char	*comma_pos;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (ft_strncmp(line + i, type, ft_strlen(type)) != 0)
		return (0);
	i += ft_strlen(type);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	
	rgb_str = line + i;
	*r = ft_atoi(rgb_str);
	comma_pos = ft_strchr(rgb_str, ',');
	if (!comma_pos)
		return (0);
	rgb_str = comma_pos + 1;
	*g = ft_atoi(rgb_str);
	comma_pos = ft_strchr(rgb_str, ',');
	if (!comma_pos)
		return (0);
	rgb_str = comma_pos + 1;
	*b = ft_atoi(rgb_str);
	
	if (*r < 0 || *r > 255 || *g < 0 || *g > 255 || *b < 0 || *b > 255)
		return (0);
	return (1);
}

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	return (1);
}

static int	find_map_start(t_static_parser *parser)
{
	int	i;

	i = 0;
	while (i < parser->line_count)
	{
		if (!is_empty_line(parser->lines[i]) &&
			!parse_texture_static(parser->lines[i], parser->north_path, "NO") &&
			!parse_texture_static(parser->lines[i], parser->south_path, "SO") &&
			!parse_texture_static(parser->lines[i], parser->east_path, "EA") &&
			!parse_texture_static(parser->lines[i], parser->west_path, "WE") &&
			!parse_color_static(parser->lines[i], &parser->floor_r, &parser->floor_g, &parser->floor_b, "F") &&
			!parse_color_static(parser->lines[i], &parser->ceiling_r, &parser->ceiling_g, &parser->ceiling_b, "C"))
		{
			parser->map_start_line = i;
			return (1);
		}
		i++;
	}
	return (0);
}

static int	validate_map_character(char c, t_static_parser *parser, int x, int y)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (parser->player_x != -1)
		{
			write(STDERR_FILENO, "Error\nMultiple players found\n", 28);
			return (0);
		}
		parser->player_x = x;
		parser->player_y = y;
		parser->player_dir = c;
		return (1);
	}
	write(STDERR_FILENO, "Error\nInvalid character in map\n", 30);
	return (0);
}

static int	validate_map_borders(t_static_parser *parser)
{
	int	i, j;

	// Check first and last rows
	for (i = 0; i < parser->map_width; i++)
	{
		if (parser->lines[parser->map_start_line][i] != '1' && parser->lines[parser->map_start_line][i] != ' ')
			return (0);
		if (parser->lines[parser->map_start_line + parser->map_height - 1][i] != '1' && 
			parser->lines[parser->map_start_line + parser->map_height - 1][i] != ' ')
			return (0);
	}
	
	// Check first and last columns
	for (j = 0; j < parser->map_height; j++)
	{
		if (parser->lines[parser->map_start_line + j][0] != '1' && parser->lines[parser->map_start_line + j][0] != ' ')
			return (0);
		int line_len = ft_strlen(parser->lines[parser->map_start_line + j]);
		if (line_len > 0 && parser->lines[parser->map_start_line + j][line_len - 1] != '1' && 
			parser->lines[parser->map_start_line + j][line_len - 1] != ' ')
			return (0);
	}
	
	return (1);
}

static int	transfer_to_cub3d(t_cub3d *cub3d, t_static_parser *parser)
{
	int	i;

	// Use garbage collector for memory management
	cub3d->map.north_texture = gc_malloc(cub3d, ft_strlen(parser->north_path) + 1);
	cub3d->map.south_texture = gc_malloc(cub3d, ft_strlen(parser->south_path) + 1);
	cub3d->map.east_texture = gc_malloc(cub3d, ft_strlen(parser->east_path) + 1);
	cub3d->map.west_texture = gc_malloc(cub3d, ft_strlen(parser->west_path) + 1);
	
	if (!cub3d->map.north_texture || !cub3d->map.south_texture || 
		!cub3d->map.east_texture || !cub3d->map.west_texture)
		return (0);
	
	// Copy paths using simple string copy to avoid ft_strdup
	i = 0;
	while (parser->north_path[i])
	{
		cub3d->map.north_texture[i] = parser->north_path[i];
		i++;
	}
	cub3d->map.north_texture[i] = '\0';
	
	i = 0;
	while (parser->south_path[i])
	{
		cub3d->map.south_texture[i] = parser->south_path[i];
		i++;
	}
	cub3d->map.south_texture[i] = '\0';
	
	i = 0;
	while (parser->east_path[i])
	{
		cub3d->map.east_texture[i] = parser->east_path[i];
		i++;
	}
	cub3d->map.east_texture[i] = '\0';
	
	i = 0;
	while (parser->west_path[i])
	{
		cub3d->map.west_texture[i] = parser->west_path[i];
		i++;
	}
	cub3d->map.west_texture[i] = '\0';
	
	cub3d->map.floor_color = (parser->floor_r << 16) | (parser->floor_g << 8) | parser->floor_b;
	cub3d->map.ceiling_color = (parser->ceiling_r << 16) | (parser->ceiling_g << 8) | parser->ceiling_b;
	
	// Allocate map using garbage collector
	cub3d->map.map = gc_malloc(cub3d, sizeof(char *) * (parser->map_height + 1));
	if (!cub3d->map.map)
		return (0);
	
	i = 0;
	while (i < parser->map_height)
	{
		int line_len = ft_strlen(parser->lines[parser->map_start_line + i]);
		cub3d->map.map[i] = gc_malloc(cub3d, line_len + 1);
		if (!cub3d->map.map[i])
			return (0);
		
		// Copy line using simple copy to avoid ft_strdup
		int j = 0;
		while (parser->lines[parser->map_start_line + i][j])
		{
			cub3d->map.map[i][j] = parser->lines[parser->map_start_line + i][j];
			j++;
		}
		cub3d->map.map[i][j] = '\0';
		i++;
	}
	cub3d->map.map[i] = NULL;
	
	cub3d->map.width = parser->map_width;
	cub3d->map.height = parser->map_height;
	
	// Set player position
	cub3d->player.pos_x = parser->player_x + 0.5;
	cub3d->player.pos_y = parser->player_y + 0.5;
	
	// Set player direction based on character
	if (parser->player_dir == 'N')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = -1;
		cub3d->player.plane_x = 0.66;
		cub3d->player.plane_y = 0;
	}
	else if (parser->player_dir == 'S')
	{
		cub3d->player.dir_x = 0;
		cub3d->player.dir_y = 1;
		cub3d->player.plane_x = -0.66;
		cub3d->player.plane_y = 0;
	}
	else if (parser->player_dir == 'E')
	{
		cub3d->player.dir_x = 1;
		cub3d->player.dir_y = 0;
		cub3d->player.plane_x = 0;
		cub3d->player.plane_y = 0.66;
	}
	else if (parser->player_dir == 'W')
	{
		cub3d->player.dir_x = -1;
		cub3d->player.dir_y = 0;
		cub3d->player.plane_x = 0;
		cub3d->player.plane_y = -0.66;
	}
	
	return (1);
}

int	static_parse_map(t_cub3d *cub3d, const char *filename)
{
	static t_static_parser	parser;
	int						i, j;

	init_static_parser(&parser);
	if (!read_file_to_buffer(filename, &parser))
	{
		write(STDERR_FILENO, "Error\nFailed to read file\n", 25);
		return (0);
	}
	
	// Parse textures and colors
	i = 0;
	while (i < parser.line_count)
	{
		if (!parser.has_north && parse_texture_static(parser.lines[i], parser.north_path, "NO"))
			parser.has_north = 1;
		else if (!parser.has_south && parse_texture_static(parser.lines[i], parser.south_path, "SO"))
			parser.has_south = 1;
		else if (!parser.has_east && parse_texture_static(parser.lines[i], parser.east_path, "EA"))
			parser.has_east = 1;
		else if (!parser.has_west && parse_texture_static(parser.lines[i], parser.west_path, "WE"))
			parser.has_west = 1;
		else if (!parser.has_floor && parse_color_static(parser.lines[i], &parser.floor_r, &parser.floor_g, &parser.floor_b, "F"))
			parser.has_floor = 1;
		else if (!parser.has_ceiling && parse_color_static(parser.lines[i], &parser.ceiling_r, &parser.ceiling_g, &parser.ceiling_b, "C"))
			parser.has_ceiling = 1;
		i++;
	}
	
	// Validate all required elements
	if (!parser.has_north || !parser.has_south || !parser.has_east || !parser.has_west || !parser.has_floor || !parser.has_ceiling)
	{
		write(STDERR_FILENO, "Error\nMissing required elements\n", 30);
		return (0);
	}
	
	// Find map start
	if (!find_map_start(&parser))
	{
		write(STDERR_FILENO, "Error\nNo map found\n", 18);
		return (0);
	}
	
	// Calculate map dimensions and validate characters
	parser.map_height = parser.line_count - parser.map_start_line;
	parser.map_width = 0;
	for (i = parser.map_start_line; i < parser.line_count; i++)
	{
		int line_len = ft_strlen(parser.lines[i]);
		if (line_len > parser.map_width)
			parser.map_width = line_len;
		
		for (j = 0; j < line_len; j++)
		{
			if (!validate_map_character(parser.lines[i][j], &parser, j, i - parser.map_start_line))
				return (0);
		}
	}
	
	// Check for player
	if (parser.player_x == -1)
	{
		write(STDERR_FILENO, "Error\nNo player found\n", 21);
		return (0);
	}
	
	// Validate map borders
	if (!validate_map_borders(&parser))
	{
		write(STDERR_FILENO, "Error\nMap not properly enclosed\n", 31);
		return (0);
	}
	
	// Transfer data to cub3d structure only after all validation
	if (!transfer_to_cub3d(cub3d, &parser))
	{
		write(STDERR_FILENO, "Error\nMemory allocation failed\n", 30);
		return (0);
	}
	
	return (1);
}
