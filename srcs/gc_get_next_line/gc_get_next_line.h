/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anebbou <anebbou@student42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 21:27:12 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 16:17:32 by anebbou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GC_GET_NEXT_LINE_H
# define GC_GET_NEXT_LINE_H

# define MAX_FD 1024

/* ************************************************************************** */
/* BUFFER DEFINITION */
/* ************************************************************************** */

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

/* ************************************************************************** */
/* INCLUDES */
/* ************************************************************************** */

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

// Forward declaration for garbage collector
typedef struct s_cub3d	t_cub3d;

/* ************************************************************************** */
/* STRUCTURES */
/* ************************************************************************** */

typedef struct s_gc_fd_buffer
{
	int						fd;
	char					*buffer;
	struct s_gc_fd_buffer	*next;
}	t_gc_fd_buffer;

/* ************************************************************************** */
/* PROTOTYPES */
/* ************************************************************************** */

// Main function for getting the next line with garbage collector
char			*gc_get_next_line(t_cub3d *cub3d, int fd);

// Utility functions for gc_get_next_line
void			gc_gnl_remove_fd(t_gc_fd_buffer **head, int fd);
size_t			gc_gnl_strlen(const char *str);
char			*gc_gnl_strjoin_and_free(t_cub3d *cub3d, char *s1, char *s2);
int				gc_gnl_find_newline(const char *str);
char			*gc_read_to_buffer(t_cub3d *cub3d, int fd,
					t_gc_fd_buffer *current_fd,
					t_gc_fd_buffer **fd_list);
char			*gc_gnl_extract_line(t_cub3d *cub3d, char **buffer);
char			*gc_gnl_update_buffer(t_cub3d *cub3d, char *buffer,
					int line_length);
char			*gc_gnl_allocate_line(t_cub3d *cub3d, char *buffer,
					int line_length);
t_gc_fd_buffer	*gc_gnl_find_or_add_fd(t_cub3d *cub3d, int fd,
					t_gc_fd_buffer **head);

#endif
