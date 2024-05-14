

#include "get_next_line.h"

char	*ft_free(char *buffer, char *buf)
{
	char	*temp;
 
	if (!buffer)
		return (NULL);
	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;
 
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
		return (free(buffer), NULL);
	i++;
	j = 0;
 
	while (buffer[i])
		line[j++] = buffer[i++];
	free(buffer);
	return (line);
}
 
// Ota line palautukseen
char	*ft_line(char *buffer)
{
	char	*line;
	int		i;
 
	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
		line = ft_calloc(i + 1, sizeof(char));
	else
		line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i])
		line[i] = '\n';
	return (line);
}
 
char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;
 
	if (!res)
		res = ft_calloc(1, 1);
	// if (!res)
	// 	return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(res), NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(res),free(buffer), NULL);
		buffer[byte_read] = 0;
		res = ft_free(res, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (res);
}
 
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
 
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(buffer);
        buffer = NULL;
		return (NULL);
	}
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	line = ft_line(buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
	}
	else
		buffer = ft_next(buffer);
	return (line);
}