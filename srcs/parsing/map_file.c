/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:24:42 by jmader            #+#    #+#             */
/*   Updated: 2025/05/20 18:52:04 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

static int	is_texture_line(char *line)
{
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0);
}

static int	is_color_line(char *line)
{
	return (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

int	parse_map_file(char *filename, t_game *game)
{
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nCannot open file: %s\n", filename), -1);
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (is_texture_line(line))
		{
			if (parse_texture_line(game, line) == -1)
			{
				free(line);
				return (-1);
			}
		}
		else if (is_color_line(line))
		{
			if (line[0] == 'F' && parse_color_line(&game->gc, line, &game->floor_color) == -1)
			{
				free(line);
				return (-1);
			}
			if (line[0] == 'C' && parse_color_line(&game->gc, line, &game->ceiling_color) == -1)
			{
				free(line);
				return (-1);
			}
		}
		else
		{
			// Partie carte à traiter séparément
			free(line);
			break ;
		}
		free(line);
	}
	close(fd);
	return (0);
}
