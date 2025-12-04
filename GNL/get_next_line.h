/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asari <asari@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 14:40:44 by asari             #+#    #+#             */
/*   Updated: 2025/08/23 15:52:07 by asari            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>

int		ft_is_in_newline(char *str);
char	*ft_strjoin_and_free(char *s1, char *s2);
char	*ft_get_line(char *stash);
char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*free_and_return(char **pointer);

#endif