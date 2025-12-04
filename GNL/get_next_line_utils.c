/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:40:39 by asari             #+#    #+#             */
/*   Updated: 2025/08/23 15:50:26 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	char	*dup_start;
	int		len;

	if (!s)
		return (NULL);
	len = 0;
	while (s[len] != '\0')
		len++;
	dup = malloc(sizeof(char) * (len + 1));
	if (dup == NULL)
		return (NULL);
	dup_start = dup;
	while (*s != '\0')
	{
		*dup_start = *s;
		dup_start++;
		s++;
	}
	*dup_start = '\0';
	return (dup);
}

int	ft_is_in_newline(char *str)
{
	if (!str)
		return (0);
	while (*str != '\0')
	{
		if (*str == '\n')
			return (1);
		str++;
	}
	return (0);
}

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len] != '\0')
		len++;
	return (len);
}

static void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char		*dst_move;
	const unsigned char	*src_move;

	if (dst == NULL && src == NULL)
		return (NULL);
	dst_move = (unsigned char *)dst;
	src_move = (const unsigned char *)src;
	if (src_move > dst_move)
	{
		while (n-- > 0)
			*dst_move++ = *src_move++;
	}
	else
	{
		while (n > 0)
		{
			*(dst_move + n - 1) = *(src_move + n - 1);
			n--;
		}
	}
	return (dst);
}

char	*ft_strjoin_and_free(char *s1, char *s2)
{
	char	*str;
	size_t	n1;
	size_t	n2;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	n1 = ft_strlen(s1);
	n2 = ft_strlen(s2);
	str = malloc(n1 + n2 + 1);
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	ft_memmove(str, s1, n1);
	ft_memmove(str + n1, s2, n2);
	str[n1 + n2] = '\0';
	free(s1);
	return (str);
}
