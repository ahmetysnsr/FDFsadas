/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 13:08:49 by asari             #+#    #+#             */
/*   Updated: 2025/12/01 13:18:33 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> 

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static char	*get_next_word(char const *s, char c, int *cursor)
{
	char	*word;
	int		len;
	int		start;
	int		i;

	len = 0;
	while (s[*cursor] == c)
		(*cursor)++;
	start = *cursor;
	while (s[*cursor] && s[*cursor] != c)
	{
		len++;
		(*cursor)++;
	}
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (i < len)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	int		words;
	int		i;
	int		cursor;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	cursor = 0;
	while (i < words)
	{
		result[i] = get_next_word(s, c, &cursor);
		if (!result[i])
		{
			free_split(result);
			return (NULL);
		}
		i++;
	}
	result[i] = NULL;
	return (result);
}
