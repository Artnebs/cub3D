/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:15:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/30 14:24:29 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_texture(t_cub3d *cub3d, char *line, char **texture, char *type)
{
	char	**split;
	int		fd;

	(void)type;
	split = ft_gc_split(cub3d, line, ' ');
	if (!split)
		error_exit(cub3d, "Memory allocation failed while parsing texture");
	if (!validate_texture_args(split, cub3d))
		return (0);
	if (!check_texture_duplicate(texture, split, cub3d))
		return (0);
	*texture = gc_malloc(cub3d, ft_strlen(split[1]) + 1);
	if (!*texture)
		error_exit(cub3d, "Memory allocation failed for texture path");
	ft_strlcpy(*texture, split[1], ft_strlen(split[1]) + 1);
	fd = open(*texture, O_RDONLY);
	if (fd == -1)
	{
		error_exit(cub3d, "Texture file not found or not accessible");
		return (0);
	}
	close(fd);
	return (1);
}
