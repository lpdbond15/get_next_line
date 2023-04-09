/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leon <leon@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 09:49:41 by leon              #+#    #+#             */
/*   Updated: 2023/04/09 10:57:35 by leon             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// #include "get_next_line_utils.c"

char	*extract_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str[0])
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n' )
		i++;
	line = ft_calloc(sizeof(char), (i + 1));
	if (!line)
		return (ft_free(&line));
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		line[j++] = str[i++];
	if (str[i] == '\n')
		line[j++] = str[i++];
	return (line);
}

char	*fill_stash(char *stash, int fd)
{
	char	*buffer;
	int		read_bytes;

	read_bytes = 1;
	buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (ft_free(&stash));
	// buffer[0] = 0;
	while (read_bytes > 0 && !ft_strchr(buffer, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes > 0)
		{
		buffer[read_bytes] = 0;
		stash = ft_strjoin(stash, buffer);
		}

	}
	free(buffer);
	if (read_bytes == -1)
		return (ft_free(&stash));
	return (stash);
}

char	*clean_stash(char *str)
{
	int		i;
	int		j;
	char	*new_stash;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
		return (ft_free(&str));
	new_stash = ft_calloc(sizeof(char), (ft_strlen(str) - i + 1));
	if (!new_stash)
		return (ft_free(&str));
	// if (str[i] == '\n')
	i++;
	j = 0;
	while (str[i])
		new_stash[j++] = str[i++];
	free(str);
	return (new_stash);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash = NULL;

	line = NULL;
	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((stash && !ft_strchr(stash, '\n')) || !stash)
		stash = fill_stash(stash, fd);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	if (!line)
		return (ft_free(&stash));
	stash = clean_stash(stash);
	return (line);
}
