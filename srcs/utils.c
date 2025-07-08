#include "cub3d.h"

void    free_split(char **split)
{
    int i;

    if (!split)
        return;
    
    i = 0;
    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

char    *ft_strdup(const char *s)
{
    char    *dup;
    size_t  len;

    len = ft_strlen(s);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    ft_strlcpy(dup, s, len + 1);
    return (dup);
}

char    **ft_split(char const *s, char c)
{
    char    **result;
    int     i;
    int     j;
    int     k;
    int     len;

    if (!s)
        return (NULL);
    result = malloc(sizeof(char *) * (ft_strlen(s) + 1));
    if (!result)
        return (NULL);
    i = 0;
    j = 0;
    while (s[i])
    {
        while (s[i] && s[i] == c)
            i++;
        if (s[i])
        {
            k = i;
            while (s[i] && s[i] != c)
                i++;
            len = i - k;
            result[j] = malloc(len + 1);
            if (!result[j])
            {
                free_split(result);
                return (NULL);
            }
            ft_strlcpy(result[j], s + k, len + 1);
            j++;
        }
    }
    result[j] = NULL;
    return (result);
}

int ft_atoi(const char *str)
{
    int i;
    int sign;
    int result;

    i = 0;
    sign = 1;
    result = 0;
    while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
        i++;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return (result * sign);
}

size_t  ft_strlen(const char *s)
{
    size_t  i;

    i = 0;
    while (s[i])
        i++;
    return (i);
} 