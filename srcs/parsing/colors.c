/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 13:20:30 by jmader            #+#    #+#             */
/*   Updated: 2025/05/20 15:33:57 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static int	parse_rgb_values(t_gc *gc, char *str, int *color)
{
	char	**parts;
	int		r;
	int		g;
	int		b;

	parts = gc_split(gc, str, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3])
		return (-1);
	r = ft_atoi(parts[0]);
	g = ft_atoi(parts[1]);
	b = ft_atoi(parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
	*color = (r << 16) + (g << 8) + b;
	return (0);
}

int	parse_color_line(t_gc *gc, char *line, int *color)
{
	char	**tokens;

	tokens = gc_split(gc, line, ' ');
	if (!tokens || !tokens[0] || !tokens[1] || tokens[2])
		return (printf("Error\nInvalid color line format\n"), -1);
	if (tokens[0][0] != 'F' && tokens[0][0] != 'C')
		return (printf("Error\nUnknown color identifier: %s\n", tokens[0]), -1);
	if (parse_rgb_values(gc, tokens[1], color) == -1)
		return (printf("Error\nInvalid RGB values: %s\n", tokens[1]), -1);
	return (0);
}
