/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:46 by stefanodipu       #+#    #+#             */
/*   Updated: 2024/03/01 20:53:06 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_line_and_buff(int fd, char *line, char *buff)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	j = 0;
	flag = 0;
	while (!flag && ((buff[0]) || read(fd, buff, BUFFER_SIZE) > 0))
	{
		line = ft_strjoin_get_next_line(line, buff);
		i = 0;
		j = 0;
		while (buff[i])
		{
			if (flag == 1)
				buff[j++] = buff[i];
			if (buff[i] == '\n')
				flag = 1;
			buff[i++] = 0;
		}
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	buff[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
	{
		emptybuff(buff[fd]);
		line = NULL;
		return (NULL);
	}
	line = NULL;
	line = get_line_and_buff(fd, line, buff[fd]);
	if (BUFFER_SIZE <= 0 || fd < 0)
	{
		emptybuff(buff[fd]);
		free(line);
		return (NULL);
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int		fd[3];
// 	int	i = 0;
// 	char *temp;

// 	fd[0] =  open("file.txt", O_RDONLY);
// 	if (fd[0] == -1)
// 		return (1);
// 	fd[1] = -1;
// 	fd[2] = open("file2.txt", O_RDONLY);
// 	if (fd[0] == -1)
// 		return (1);
// 	while(1)
// 	{
// 		temp = get_next_line (fd[i % 3]);
// 		printf("line: %s\n", temp);
// 		free(temp);
// 		if (i == 10)
// 			break ;
// 		i++;
// 	}
// 	close(fd[0]);
// 	close(fd[2]);
// 	return (0);
// }
