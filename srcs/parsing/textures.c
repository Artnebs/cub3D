/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:19:46 by jmader            #+#    #+#             */
/*   Updated: 2025/05/20 18:51:17 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "gc.h"

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

int	parse_texture_line(t_game *game, char *line)
{
	char	**tokens;
	int		index;

	tokens = gc_split(&game->gc, line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		return (printf("Error\nInvalid texture line format\n"), -1);
	index = get_texture_index(tokens[0]);
	if (index == -1)
		return (printf("Error\nUnknown texture identifier: %s\n", tokens[0]), -1);
	if (game->textures[index].path != NULL)
		return (printf("Error\nDuplicate texture identifier: %s\n",
				tokens[0]), -1);
	game->textures[index].path = gc_strdup(&game->gc, tokens[1]);
	if (!game->textures[index].path)
		return (printf("Error\nMemory allocation failed\n"), -1);
	return (0);
}
