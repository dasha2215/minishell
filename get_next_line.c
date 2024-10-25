/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dsiroten <dsiroten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 14:59:29 by dsiroten          #+#    #+#             */
/*   Updated: 2024/09/09 13:56:18 by dsiroten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_line(int fd, char *prev_line, char *buffer)
{
	char	*line;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!prev_line)
			prev_line = ft_strdup("");
		line = prev_line;
		prev_line = ft_strjoin(line, buffer);
		free(line);
		if (ft_strrchr(buffer, '\n'))
			break ;
	}
	return (prev_line);
}

static char	*set_line(char *next_line)
{
	char	*prev_line;
	int		i;

	i = 0;
	prev_line = NULL;
	if (!next_line[i])
		return (0);
	while (next_line[i] && next_line[i] != '\n')
		i++;
	if (!next_line[i])
		return (0);
	prev_line = ft_substr(next_line, i + 1, ft_strlen(next_line) - i);
	if (!prev_line)
		return (0);
	next_line[i + 1] = '\0';
	return (prev_line);
}

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*prev_line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (0);
	next_line = read_line(fd, prev_line, buffer);
	free(buffer);
	if (!next_line)
	{
		free(prev_line);
		prev_line = NULL;
		return (0);
	}
	prev_line = set_line(next_line);
	if (*next_line == '\0')
	{
		free(next_line);
		return (0);
	}
	return (next_line);
}
