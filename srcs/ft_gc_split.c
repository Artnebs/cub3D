/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gc_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmader <jmader@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 13:27:32 by anebbou           #+#    #+#             */
/*   Updated: 2025/07/30 14:19:10 by jmader           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Libft_GNL_Printf/includes/libft.h"
#include "../includes/cub3d.h"

static const char	*find_next_word(const char **s, char c)
{
	const char	*start;

	while (**s && **s == c)
		(*s)++;
	start = *s;
	while (**s && **s != c)
		(*s)++;
	return (start);
}

static int	count_words(const char *s, char c)
{
	int	count;
	int	in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*gc_substr(t_cub3d *cub3d, const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = gc_malloc(cub3d, 1);
		if (substr)
			substr[0] = '\0';
		return (substr);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = gc_malloc(cub3d, len + 1);
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

//splits string s using character c as delimiter - managed by garbage collector
char	**ft_gc_split(t_cub3d *cub3d, char const *s, char c)
{
	char		**result;
	int			i;
	const char	*start;

	if (!s || !cub3d)
		return (NULL);
	result = gc_malloc(cub3d, sizeof(char *) * (count_words(s, c) + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		start = find_next_word(&s, c);
		if (*start)
		{
			result[i] = gc_substr(cub3d, start, 0, s - start);
			if (!result[i])
				return (NULL);
			i++;
		}
	}
	result[i] = NULL;
	return (result);
}
