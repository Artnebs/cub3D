/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_next_line_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:03:02 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 16:19:51 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gc_get_next_line.h"
#include "../../includes/cub3d.h"

t_gc_fd_buffer	*gc_gnl_find_or_add_fd(t_cub3d *cub3d, int fd,
		t_gc_fd_buffer **head)
{
	t_gc_fd_buffer	*current;
	t_gc_fd_buffer	*new_node;

	current = *head;
	while (current)
	{
		if (current->fd == fd)
			return (current);
		current = current->next;
	}
	if (fd > MAX_FD)
		return (NULL);
	new_node = (t_gc_fd_buffer *)gc_malloc(cub3d, sizeof(t_gc_fd_buffer));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->buffer = NULL;
	new_node->next = *head;
	*head = new_node;
	return (new_node);
}

void	gc_gnl_remove_fd(t_gc_fd_buffer **head, int fd)
{
	t_gc_fd_buffer	*current;
	t_gc_fd_buffer	*prev;

	current = *head;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head = current->next;
			return ;
		}
		prev = current;
		current = current->next;
	}
}

size_t	gc_gnl_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

char	*gc_gnl_strjoin_and_free(t_cub3d *cub3d, char *s1, char *s2)
{
	size_t	len_s1;
	size_t	len_s2;
	char	*result;
	size_t	i;

	len_s1 = gc_gnl_strlen(s1);
	len_s2 = gc_gnl_strlen(s2);
	if (!s1 && !s2)
		return (NULL);
	result = gc_malloc(cub3d, len_s1 + len_s2 + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len_s1)
	{
		result[i] = s1[i];
		i++;
	}
	while (i - len_s1 < len_s2)
	{
		result[i] = s2[i - len_s1];
		i++;
	}
	result[i] = '\0';
	return (result);
}

int	gc_gnl_find_newline(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}
