/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:02:59 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 16:18:55 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_get_next_line.h"
#include "../../includes/cub3d.h"

char	*gc_get_next_line(t_cub3d *cub3d, int fd)
{
	static t_gc_fd_buffer	*fd_list = NULL;
	t_gc_fd_buffer			*current_fd;
	char					*line;

	if (!cub3d || fd < 0)
		return (NULL);
	current_fd = gc_gnl_find_or_add_fd(cub3d, fd, &fd_list);
	if (!current_fd)
		return (NULL);
	if (!gc_read_to_buffer(cub3d, fd, current_fd, &fd_list))
	{
		gc_gnl_remove_fd(&fd_list, fd);
		return (NULL);
	}
	line = gc_gnl_extract_line(cub3d, &(current_fd->buffer));
	if (!line && (!current_fd->buffer || *current_fd->buffer == '\0'))
		gc_gnl_remove_fd(&fd_list, fd);
	return (line);
}

char	*gc_read_to_buffer(t_cub3d *cub3d, int fd, t_gc_fd_buffer *current_fd,
		t_gc_fd_buffer **fd_list)
{
	char	*temp_buffer;
	ssize_t	bytes_read;

	temp_buffer = gc_malloc(cub3d, BUFFER_SIZE + 1);
	if (!temp_buffer)
		return (NULL);
	bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		temp_buffer[bytes_read] = '\0';
		current_fd->buffer = gc_gnl_strjoin_and_free(cub3d, current_fd->buffer,
				temp_buffer);
		if (!current_fd->buffer)
			return (gc_gnl_remove_fd(fd_list, fd), NULL);
		if (gc_gnl_find_newline(current_fd->buffer) >= 0)
			break ;
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
	{
		gc_gnl_remove_fd(fd_list, fd);
		return (NULL);
	}
	return (current_fd->buffer);
}

char	*gc_gnl_extract_line(t_cub3d *cub3d, char **buffer)
{
	char	*line;
	char	*temp;
	int		line_length;

	if (!buffer || !*buffer || **buffer == '\0')
		return (NULL);
	line_length = gc_gnl_find_newline(*buffer);
	if (line_length >= 0)
		line_length += 1;
	else
	{
		line_length = 0;
		while ((*buffer)[line_length])
			line_length++;
	}
	line = gc_gnl_allocate_line(cub3d, *buffer, line_length);
	if (!line)
	{
		*buffer = NULL;
		return (NULL);
	}
	temp = gc_gnl_update_buffer(cub3d, *buffer, line_length);
	*buffer = temp;
	return (line);
}

char	*gc_gnl_update_buffer(t_cub3d *cub3d, char *buffer, int line_length)
{
	char	*temp;
	int		i;

	i = 0;
	while (buffer[line_length + i])
		i++;
	temp = gc_malloc(cub3d, i + 1);
	if (!temp)
		return (NULL);
	i = 0;
	while (buffer[line_length + i])
	{
		temp[i] = buffer[line_length + i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*gc_gnl_allocate_line(t_cub3d *cub3d, char *buffer, int line_length)
{
	char	*line;
	int		i;

	i = 0;
	line = gc_malloc(cub3d, line_length + 1);
	if (!line)
		return (NULL);
	while (i < line_length)
	{
		line[i] = buffer[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}
