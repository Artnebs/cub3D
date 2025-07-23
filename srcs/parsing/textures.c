/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:19:46 by jmader            #+#    #+#             */
/*   Updated: 2025/07/23 16:24:29 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	get_texture_index(char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0)
		return (0);
	if (ft_strncmp(id, "SO", 2) == 0)
		return (1);
	if (ft_strncmp(id, "EA", 2) == 0)
		return (2);
	if (ft_strncmp(id, "WE", 2) == 0)
		return (3);
	return (-1);
}

static char	*get_texture_path_ptr(t_cub3d *game, int index)
{
	if (index == 0)
		return (game->map.north_texture);
	if (index == 1)
		return (game->map.south_texture);
	if (index == 2)
		return (game->map.east_texture);
	if (index == 3)
		return (game->map.west_texture);
	return (NULL);
}

static void	set_texture_path(t_cub3d *game, int index, char *path)
{
	if (index == 0)
		game->map.north_texture = path;
	else if (index == 1)
		game->map.south_texture = path;
	else if (index == 2)
		game->map.east_texture = path;
	else if (index == 3)
		game->map.west_texture = path;
}

int	parse_texture_line(t_cub3d *game, char *line)
{
	char	**tokens;
	int		index;
	char	*path;

	tokens = ft_split(line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
	{
		if (tokens)
			free_split(tokens);
		return (printf("Error\nInvalid texture line format\n"), -1);
	}
	index = get_texture_index(tokens[0]);
	if (index == -1)
	{
		free_split(tokens);
		return (printf("Error\nUnknown texture identifier: %s\n", tokens[0]), -1);
	}
	if (get_texture_path_ptr(game, index) != NULL)
	{
		free_split(tokens);
		return (printf("Error\nDuplicate texture identifier: %s\n", tokens[0]), -1);
	}
	path = gc_malloc(game, ft_strlen(tokens[1]) + 1);
	if (!path)
	{
		free_split(tokens);
		return (printf("Error\nMemory allocation failed\n"), -1);
	}
	ft_strlcpy(path, tokens[1], ft_strlen(tokens[1]) + 1);
	set_texture_path(game, index, path);
	free_split(tokens);
	return (0);
}
