/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeanb <jeanb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 12:15:00 by jeanb             #+#    #+#             */
/*   Updated: 2025/07/29 12:25:39 by jeanb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	validate_color_args(char **split, t_cub3d *cub3d)
{
	int	i;

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
		return (0);
	}
	return (1);
}

static int	check_color_duplicate(int *color, char **split, t_cub3d *cub3d)
{
	if (*color != -1)
	{
		ft_free_split(split);
		error_exit(cub3d, "Color is defined multiple times");
		return (0);
	}
	return (1);
}

static int	validate_rgb_values(int r_g_b[3], char **rgb, t_cub3d *cub3d)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!rgb[i] || ft_strlen(rgb[i]) == 0)
		{
			ft_free_split(rgb);
			error_exit(cub3d, "Invalid RGB format");
			return (0);
		}
		r_g_b[i] = ft_atoi(rgb[i]);
		if (r_g_b[i] < 0 || r_g_b[i] > 255)
		{
			ft_free_split(rgb);
			error_exit(cub3d, "RGB values must be between 0 and 255");
			return (0);
		}
		i++;
	}
	return (1);
}

static int	parse_color_split_and_rgb(t_cub3d *cub3d, char *line, char ***split, char ***rgb)
{
	*split = ft_split(line, ' ');
	if (!*split)
		error_exit(cub3d, "Memory allocation failed while parsing color");
	if (!validate_color_args(*split, cub3d))
		return (0);
	*rgb = ft_split((*split)[1], ',');
	if (!*rgb)
	{
		ft_free_split(*split);
		error_exit(cub3d, "Memory allocation failed while parsing RGB values");
	}
	return (1);
}

int	parse_color(t_cub3d *cub3d, char *line, int *color, char *type)
{
	char	**split;
	char	**rgb;
	int		r_g_b[3];

	(void)type;
	if (!parse_color_split_and_rgb(cub3d, line, &split, &rgb))
		return (0);
	if (!check_color_duplicate(color, split, cub3d))
		return (0);
	if (!validate_rgb_values(r_g_b, rgb, cub3d))
	{
		ft_free_split(split);
		return (0);
	}
	*color = (r_g_b[0] << 16) | (r_g_b[1] << 8) | r_g_b[2];
	ft_free_split(rgb);
	ft_free_split(split);
	return (1);
}

int	parse_color_line(t_cub3d *cub3d, char *line, int i)
{
	if (i == 4 && ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(cub3d, line, &cub3d->map.floor_color, "F"));
	else if (i == 5 && ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(cub3d, line, &cub3d->map.ceiling_color, "C"));
	return (0);
} 