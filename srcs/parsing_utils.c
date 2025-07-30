/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:15:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/30 16:43:27 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	**allocate_new_map(t_cub3d *cub3d)
{
	char	**new_map;

	new_map = gc_malloc(cub3d, sizeof(char *) * (cub3d->map.height + 2));
	if (!new_map)
		error_exit(cub3d, "Memory allocation failed for map");
	return (new_map);
}

static void	copy_existing_map(char **new_map, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < cub3d->map.height)
	{
		new_map[i] = cub3d->map.map[i];
		i++;
	}
}

static void	allocate_map_line(char **new_map, char *line, t_cub3d *cub3d)
{
	new_map[cub3d->map.height] = gc_malloc(cub3d, ft_strlen(line) + 1);
	if (!new_map[cub3d->map.height])
	{
		gc_free(cub3d, new_map);
		error_exit(cub3d, "Memory allocation failed for map line");
	}
	ft_strlcpy(new_map[cub3d->map.height], line, ft_strlen(line) + 1);
	new_map[cub3d->map.height + 1] = NULL;
}

int	parse_map_line(t_cub3d *cub3d, char *line)
{
	char	**new_map;

	new_map = allocate_new_map(cub3d);
	copy_existing_map(new_map, cub3d);
	allocate_map_line(new_map, line, cub3d);
	if (cub3d->map.map)
		gc_free(cub3d, cub3d->map.map);
	cub3d->map.map = new_map;
	cub3d->map.height++;
	if ((int)ft_strlen(line) > cub3d->map.width)
		cub3d->map.width = (int)ft_strlen(line);
	return (1);
}

int	is_map_line(char *line)
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
