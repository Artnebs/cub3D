/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:15:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 12:39:34 by jeanb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_texture_args(char **split, t_cub3d *cub3d)
{
	int	i;

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
		return (0);
	}
	return (1);
}

static int	check_texture_duplicate(char **texture, char **split, t_cub3d *cub3d)
{
	if (*texture != NULL)
	{
		ft_free_split(split);
		error_exit(cub3d, "Texture is defined multiple times");
		return (0);
	}
	return (1);
}

static void	allocate_texture_path(char **texture, char **split, t_cub3d *cub3d)
{
	*texture = gc_malloc(cub3d, ft_strlen(split[1]) + 1);
	if (!*texture)
	{
		ft_free_split(split);
		error_exit(cub3d, "Memory allocation failed for texture path");
	}
	ft_strlcpy(*texture, split[1], ft_strlen(split[1]) + 1);
}

int	parse_texture(t_cub3d *cub3d, char *line, char **texture, char *type)
{
	char	**split;

	(void)type;
	split = ft_split(line, ' ');
	if (!split)
		error_exit(cub3d, "Memory allocation failed while parsing texture");
	if (!validate_texture_args(split, cub3d))
		return (0);
	if (!check_texture_duplicate(texture, split, cub3d))
		return (0);
	allocate_texture_path(texture, split, cub3d);
	ft_free_split(split);
	return (1);
}

int	parse_texture_line(t_cub3d *cub3d, char *line, int i)
{
	if (i == 0 && ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(cub3d, line, &cub3d->map.north_texture, "NO"));
	else if (i == 1 && ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(cub3d, line, &cub3d->map.south_texture, "SO"));
	else if (i == 2 && ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(cub3d, line, &cub3d->map.west_texture, "WE"));
	else if (i == 3 && ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(cub3d, line, &cub3d->map.east_texture, "EA"));
	return (0);
} 