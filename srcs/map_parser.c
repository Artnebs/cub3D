/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:09:10 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/28 18:41:26 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_texture(t_cub3d *cub3d, char *line, char **texture, char *type)
{
	char	**split;
	int		i;

	(void)type;
	split = ft_split(line, ' ');
	if (!split)
		error_exit(cub3d, "Memory allocation failed while parsing texture");
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
	{
		ft_free_split(split);
		if (i < 2)
			error_exit(cub3d, "Missing texture path");
		else
			error_exit(cub3d, "Too many arguments for texture definition");
	}
	if (*texture != NULL)
	{
		ft_free_split(split);
		error_exit(cub3d, "Texture is defined multiple times");
	}
	*texture = gc_malloc(cub3d, ft_strlen(split[1]) + 1);
	if (!*texture)
	{
		ft_free_split(split);
		error_exit(cub3d, "Memory allocation failed for texture path");
	}
	ft_strlcpy(*texture, split[1], ft_strlen(split[1]) + 1);
	ft_free_split(split);
	return (1);
}

static int	parse_color(t_cub3d *cub3d, char *line, int *color, char *type)
{
	char	**split;
	char	**rgb;
	int		r_g_b[3];
	int		i;

	(void)type;
	split = ft_split(line, ' ');
	if (!split)
		error_exit(cub3d, "Memory allocation failed while parsing color");
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
	{
		ft_free_split(split);
		if (i < 2)
			error_exit(cub3d, "Missing color values");
		else
			error_exit(cub3d, "Too many arguments for color definition");
	}
	if (*color != -1)
	{
		ft_free_split(split);
		error_exit(cub3d, "Color is defined multiple times");
	}
	rgb = ft_split(split[1], ',');
	ft_free_split(split);
	if (!rgb)
		error_exit(cub3d, "Memory allocation failed while parsing RGB values");
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		ft_free_split(rgb);
		error_exit(cub3d, "Invalid RGB format: expected R,G,B");
	}
	r_g_b[0] = ft_atoi(rgb[0]);
	r_g_b[1] = ft_atoi(rgb[1]);
	r_g_b[2] = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (r_g_b[0] < 0 || r_g_b[0] > 255 || r_g_b[1] < 0 || r_g_b[1] > 255
		|| r_g_b[2] < 0 || r_g_b[2] > 255)
		error_exit(cub3d, "RGB values must be between 0 and 255");
	*color = (r_g_b[0] << 16) | (r_g_b[1] << 8) | r_g_b[2];
	return (1);
}

static int	parse_map_line(t_cub3d *cub3d, char *line)
{
	char	**new_map;
	int		i;

	new_map = gc_malloc(cub3d, sizeof(char *) * (cub3d->map.height + 2));
	if (!new_map)
		error_exit(cub3d, "Memory allocation failed for map");
	i = 0;
	while (i < cub3d->map.height)
	{
		new_map[i] = cub3d->map.map[i];
		i++;
	}
	new_map[i] = gc_malloc(cub3d, ft_strlen(line) + 1);
	if (!new_map[i])
	{
		gc_free(cub3d, new_map);
		error_exit(cub3d, "Memory allocation failed for map line");
	}
	ft_strlcpy(new_map[i], line, ft_strlen(line) + 1);
	new_map[i + 1] = NULL;
	if (cub3d->map.map)
		gc_free(cub3d, cub3d->map.map);
	cub3d->map.map = new_map;
	cub3d->map.height++;
	if ((int)ft_strlen(line) > cub3d->map.width)
		cub3d->map.width = (int)ft_strlen(line);
	return (1);
}

static int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '1' || line[i] == '0' || line[i] == 'N'
			|| line[i] == 'S' || line[i] == 'E' || line[i] == 'W'
			|| line[i] == ' ' || line[i] == '\t')
			i++;
		else
			return (0);
	}
	return (1);
}

static int	parse_line(t_cub3d *cub3d, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i, &cub3d->map.north_texture, "NO"));
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		return (parse_texture(cub3d, line + i, &cub3d->map.south_texture, "SO"));
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
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
	error_exit(cub3d, "Invalid line in map file: unknown identifier or character");
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
	while ((line = get_next_line(fd)) != NULL)
	{
		strip_newline(line);
		if (!parse_line(cub3d, line))
		{
			free(line);
			close(fd);
			error_exit(cub3d, "Failed to parse line in map file");
		}
		free(line);
	}
	close(fd);
	return (1);
}
