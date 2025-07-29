/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 16:55:00 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/29 16:55:00 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_color_line(t_cub3d *cub3d, char *line, int i)
{
	if (i == 4 && ft_strncmp(line, "F ", 2) == 0)
		return (parse_color(cub3d, line, &cub3d->map.floor_color, "F"));
	else if (i == 5 && ft_strncmp(line, "C ", 2) == 0)
		return (parse_color(cub3d, line, &cub3d->map.ceiling_color, "C"));
	return (0);
}
