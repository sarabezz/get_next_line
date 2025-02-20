/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarabermudez <sarabermudez@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:41:33 by sarabermude       #+#    #+#             */
/*   Updated: 2025/02/19 17:12:24 by sarabermude      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer)
{
	char	*b;
	char	buf[BUFFER_SIZE + 1];
	int		bytes;

	while (!ft_strchr(buffer, '\n'))
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes <= 0)
			return (buffer);
		b = ft_strjoin(buffer, buf);
		buffer = b;
	}
	return (buffer);
}

static char	*extract_line(char *buffer)
{
	size_t	i;
	char	*line;

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

static char	*trim_buffer(char *buffer)
{
	char	*new_buffer;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = malloc(ft_strlen(buffer + i + 1) + 1);
	if (!new_buffer)
		return (NULL);
	while (buffer[++i])
		new_buffer[j++] = buffer[i];
	new_buffer[j] = '\0';
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_line(fd, buffer);
	if (!buffer || !*buffer)
	{
		free(buffer);
		return (NULL);
	}
	line = extract_line(buffer);
	buffer = trim_buffer(buffer);
	return (line);
}
