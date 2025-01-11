/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:40:46 by stefanodipu       #+#    #+#             */
/*   Updated: 2024/03/01 20:55:41 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	buff[BUFFER_SIZE + 1];
	char		*line;

	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
	{
		emptybuff(buff);
		line = NULL;
		return (NULL);
	}
	line = NULL;
	line = get_line_and_buff(fd, line, buff);
	if (BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0 || fd < 0)
	{
		emptybuff(buff);
		line = NULL;
		return (NULL);
	}
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	char	*str;
// 	int		fd;

// 	fd = open("file.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		return (1);
// 	}
// 	/*while (1)
// 	{
// 		str = get_next_line(fd);
// 		if (str == NULL)
// 			break ;

// 		printf("- %s", str);
// 		str = NULL;
// 	}*/
// 	str = get_next_line(fd);
// 	while (1)
// 	{
// 		printf("%s", str);
// 		free(str);
// 		str = get_next_line(fd);
// 	}
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// 	fd = open("file.txt", O_RDONLY);
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
