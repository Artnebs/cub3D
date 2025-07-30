/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 12:00:00 by jmader            #+#    #+#             */
/*   Updated: 2025/07/30 12:04:48 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	validate_texture_args(char **split, t_cub3d *cub3d)
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

int	check_texture_duplicate(char **texture, char **split, t_cub3d *cub3d)
{
	if (*texture != NULL)
	{
		ft_free_split(split);
		error_exit(cub3d, "Texture is defined multiple times");
		return (0);
	}
	return (1);
}

int	validate_texture_file(char *path, t_cub3d *cub3d)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		error_exit(cub3d, "Texture file not found or not accessible");
		return (0);
	}
	close(fd);
	return (1);
}
