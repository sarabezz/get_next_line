/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarbermu <sarbermu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:41:33 by sarabermude       #+#    #+#             */
/*   Updated: 2025/02/25 15:54:15 by sarbermu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*rd(int fd, char *buffer)
{
	char	*b;
	char	buf[BUFFER_SIZE + 1];
	int		length;

	if (!buffer)
		buffer = ft_strdup("");
	while (1)
	{
		length = read(fd, buf, BUFFER_SIZE);
		if (length < 0)
		{
			free(buffer);
			return (NULL);
		}
		if (length == 0)
			break ;
		buf[length] = '\0';
		b = ft_strjoin(buffer, buf);
		if (!b)
		{
			free(buffer);
			return (NULL);
		}
		free(buffer);
		buffer = b;
	}
	return (buffer);
}

static char	*get_line(char *buffer)
{
	size_t	i;
	char	*line;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = malloc(i + (buffer[i] == '\n') + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, i + (buffer[i] == '\n'));
	line[i + (buffer[i] == '\n')] = '\0';
	return (line);
}

static char	*separate(char *buffer)
{
	char	*new_buffer;
	size_t	i;

	if (!buffer || !*buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i] || !buffer[i + 1])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i + 1);
	if (!new_buffer)
		return (NULL);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = rd(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	line = get_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = separate(buffer);
	return (line);
}
