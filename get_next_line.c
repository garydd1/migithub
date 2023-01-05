/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:52:35 by dgarizad          #+#    #+#             */
/*   Updated: 2022/12/29 19:00:26 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE	1
#endif

char	*ft_save_buffer(char *line)
{
	int		i;
	int		j;
	char	*newbuffer;

	i = 0;
	j = 0;
	while (line[i] != '\n')
		i++;
	while (line[i + j] != '\0')
		j++;
	newbuffer = (char *)ft_calloc(j, 1);
	if (!newbuffer)
		return (NULL);
	j = 0;
	while (line[i + 1 + j] != '\0')
	{
		newbuffer[j] = line[i + 1 + j];
		j++;
	}
	if (ft_strlen(newbuffer) == 0)
	{
		free(newbuffer);
		newbuffer = NULL;
	}
	return (newbuffer);
}

char	*ft_fix_line(char *line)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	while (line[i] != '\n')
		i++;
	newline = (char *)malloc(i + 2);
	if (!newline)
		return (NULL);
	j = 0;
	while (line[j] != '\0')
	{
		if (j <= i)
			newline[j] = line[j];
		j++;
	}
	newline[i + 1] = '\0';
	free(line);
	line = NULL;
	return (newline);
}

char	*ft_buffercat(char *buffer, char *local_buffer)
{
	unsigned int	len1;
	unsigned int	len2;
	char			*new_buffer;

	len1 = strlen(buffer);
	len2 = strlen(local_buffer);
	new_buffer = (char *)malloc(len1 + len2 + 1);
	if (!new_buffer)
		return (NULL);
	new_buffer[len1 + len2] = '\0';
	len1 = 0;
	while (buffer[len1] != '\0')
	{
		new_buffer[len1] = buffer[len1];
		len1++;
	}
	len2 = 0;
	while (local_buffer[len2] != '\0')
	{
		new_buffer[len1 + len2] = local_buffer[len2];
		len2++;
	}
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

char	*ft_read_fd(int fd, char *buffer)
{
	int		nread;
	int		i;
	char	*local_buffer;

	i = 0;
	nread = 1;
	local_buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!local_buffer)
		return (NULL);
	while (nread > 0)
	{
		nread = read(fd, local_buffer, BUFFER_SIZE);
		printf("\n nread:'%d'", nread);
		if (nread <= 0)
		{
			free (local_buffer);
			return (buffer);
		}
		buffer = ft_buffercat(buffer, local_buffer);
		if (ft_strchr(local_buffer, '\n'))
			break ;
	}
	free(local_buffer);
	local_buffer = NULL;
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	printf("\n starting buffer: '%s'\n\n", buffer);
	if (!buffer)
	{
		printf("ALLOCATED");
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	}
	if (!buffer)
		return (NULL);
	line = NULL;
	printf("\n keep going buffer: '%s'\n\n", buffer);
	line = ft_read_fd(fd, buffer);
	if (!line)
		return (NULL);
	buffer = ft_save_buffer(line);
	line = ft_fix_line(line);
	printf("\n test newline: '%s'", line);
	printf("\n test buffer: '%s'", buffer);
	return (line);
}

// int	main()
// {
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	fd = open("./numbers.dict", O_RDONLY);
// 	while (i++ < 43)
// 	{
// 		printf("\n-----\n'%s'\n----\n",get_next_line(fd));
// 		getchar();
// 	}
// 	return (0);
// }
