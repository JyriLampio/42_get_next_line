#include "get_next_line.h"
 
// joinaa ja vapauta muisti
char	*ft_free(char *buffer, char *buf)
{
	char	*temp;
 
	if (!buffer)
		return (NULL);
	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}
 
// Poista jo etsitty line ja palauta loput
char	*ft_next(char *buffer)
{
	int		i;
	int		j;
	char	*line;
 
	i = 0;
	// Eti eka line
	while (buffer[i] && buffer[i] != '\n')
		i++;
 
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	// Filen length - ensimmäinen line + 1
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
	// Palauta Null jos ei ole lineä
	if (!buffer[i])
		return (NULL);
	// Mee EOL:ään
	while (buffer[i] && buffer[i] != '\n')
		i++;
	// mallocaa EOL:ään asti
	line = ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	// Jos EOL niin replacee newlinellä ja palauta
	if (buffer[i])
		line[i] = '\n';
	return (line);
}
 
char	*read_file(int fd, char *res)
{
	char	*buffer;
	int		byte_read;
 
	// malloc jos ressiä ei ole (Eka ajo)
	if (!res)
		res = ft_calloc(1, 1);
	if (!res)
		return (NULL);
	// mallocaa bufferi
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
	{
		free(res);
		return (NULL);
	}
	byte_read = 1;
	while (byte_read > 0)
	{
		// kunnes loppu
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(buffer);
			free(res);
			return (NULL);
		}
		// 0 loppuun vuotojen takia
		buffer[byte_read] = 0;
		// Joinaa ja vapauta (Pieni bufferi)
		res = ft_free(res, buffer);
		// Lopeta jos löytyy newline
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