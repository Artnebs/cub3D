/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:09:10 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/23 17:13:18 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	parse_texture(t_cub3d *cub3d, char *line, char **texture)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
	{
		ft_free_split(split);
		return (0);
	}
	*texture = gc_malloc(cub3d, ft_strlen(split[1]) + 1);
	if (!*texture)
	{
		ft_free_split(split);
		return (0);
	}
	ft_strlcpy(*texture, split[1], ft_strlen(split[1]) + 1);
	ft_free_split(split);
	return (1);
}

static int	parse_color(t_cub3d *cub3d, char *line, int *color)
{
	char	**split;
	char	**rgb;
	int		r_g_b[3];
	int		i;

	(void)cub3d;
	split = ft_split(line, ' ');
	if (!split)
		return (0);
	i = 0;
	while (split[i])
		i++;
	if (i != 2)
	{
		ft_free_split(split);
		return (0);
	}
	rgb = ft_split(split[1], ',');
	ft_free_split(split);
	if (!rgb)
		return (0);
	i = 0;
	while (rgb[i])
		i++;
	if (i != 3)
	{
		ft_free_split(rgb);
		return (0);
	}
	r_g_b[0] = ft_atoi(rgb[0]);
	r_g_b[1] = ft_atoi(rgb[1]);
	r_g_b[2] = ft_atoi(rgb[2]);
	ft_free_split(rgb);
	if (r_g_b[0] < 0 || r_g_b[0] > 255 || r_g_b[1] < 0 || r_g_b[1] > 255
		|| r_g_b[2] < 0 || r_g_b[2] > 255)
		return (0);
	*color = (r_g_b[0] << 16) | (r_g_b[1] << 8) | r_g_b[2];
	return (1);
}

static int	parse_map_line(t_cub3d *cub3d, char *line)
{
	char	**new_map;
	int		i;

	new_map = gc_malloc(cub3d, sizeof(char *) * (cub3d->map.height + 2));
	if (!new_map)
		return (0);
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
		return (0);
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

static int	parse_line(t_cub3d *cub3d, char *line)
{
	if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ')
		return (parse_texture(cub3d, line, &cub3d->map.north_texture));
	else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ')
		return (parse_texture(cub3d, line, &cub3d->map.south_texture));
	else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ')
		return (parse_texture(cub3d, line, &cub3d->map.west_texture));
	else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ')
		return (parse_texture(cub3d, line, &cub3d->map.east_texture));
	else if (line[0] == 'F' && line[1] == ' ')
		return (parse_color(cub3d, line, &cub3d->map.floor_color));
	else if (line[0] == 'C' && line[1] == ' ')
		return (parse_color(cub3d, line, &cub3d->map.ceiling_color));
	else if (line[0] == '1' || line[0] == '0' || line[0] == 'N'
		|| line[0] == 'S' || line[0] == 'E' || line[0] == 'W')
		return (parse_map_line(cub3d, line));
	else if (line[0] == '\n' || line[0] == '\0')
		return (1);
	return (0);
}

int	parse_map(t_cub3d *cub3d, const char *filename)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	cub3d->map.map = NULL;
	cub3d->map.width = 0;
	cub3d->map.height = 0;
	cub3d->map.north_texture = NULL;
	cub3d->map.south_texture = NULL;
	cub3d->map.east_texture = NULL;
	cub3d->map.west_texture = NULL;
	while ((line = get_next_line(fd)) != NULL)
	{
		strip_newline(line);
		if (!parse_line(cub3d, line))
		{
			free(line);
			close(fd);
			return (0);
		}
		free(line);
	}
	close(fd);
	return (1);
}
