/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmassa-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 12:07:11 by mmassa-r          #+#    #+#             */
/*   Updated: 2022/11/25 12:07:13 by mmassa-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_save(int fd, char *save)
{
	char	*buff;
	int		read_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (0);
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buff);
			return (0);
		}
		buff[read_bytes] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*ft_get_line(char *save)
{
	char	*line;
	int		i;

	i = 0;
	if (!save[i])
		return (0);
	while (save[i] && save[i] != '\n')
		i++;
	line = malloc((i + 2) * sizeof(char *));
	if (!line)
		return (0);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (0);
	}
	str = malloc((ft_strlen(save) - i + 1) * sizeof(char));
	if (!str)
		return (0);
	i++;
	j = 0;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	save = ft_read_and_save(fd, save);
	if (!save)
		return (0);
	line = ft_get_line(save);
	save = ft_save(save);
	return (line);
}
/*
int	main(void)
{
	int		fd;
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	int		fd5;
	int		i;
	char	*line;

	fd = open("files/miranha.txt", O_RDONLY);
	fd1 = open("files/simpsons.txt", O_RDONLY);
	fd2 = open("files/hp.txt", O_RDONLY);
 	fd3 = open("files/hltv.txt", O_RDONLY);
	fd4 = open("files/big_line_with_nl", O_RDONLY);
	fd5 = open("files/big_line_no_nl", O_RDONLY);
	i = 1;
	while ((line = get_next_line(fd)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd);
	while ((line = get_next_line(fd1)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd1);
	while ((line = get_next_line(fd2)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd2);
	while ((line = get_next_line(fd3)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd3);
	while ((line = get_next_line(fd4)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd4);
	while ((line = get_next_line(fd5)))
	{
		printf("line [%02d]: %s", i, line);
		free(line);
		i++;
	}
	close(fd5);
	return (0);
}*/
