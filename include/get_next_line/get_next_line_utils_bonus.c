/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:37:37 by stefanodipu       #+#    #+#             */
/*   Updated: 2024/03/01 20:50:41 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	emptybuff(char *buff)
{
	if (buff)
		buff[0] = '\0';
}

char	*write_sj(char *sj, char *s1, char *s2)
{
	int	i;
	int	y;

	i = 0;
	y = 0;
	while (s1 && s1[i])
	{
		sj[i] = s1[i];
		i++;
	}
	y = -1;
	while (s2 && s2[++y])
	{
		sj[i++] = s2[y];
		if (s2[y] == '\n')
			break ;
	}
	sj[i] = 0;
	free(s1);
	return (sj);
}

int	getlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}

char	*ft_strjoin_get_next_line(char *s1, char *s2)
{
	int		ls;
	char	*sj;

	ls = getlen(s1) + getlen(s2);
	sj = (char *)malloc((ls + 1) * sizeof(char));
	if (!sj)
		return (NULL);
	sj = write_sj(sj, s1, s2);
	return (sj);
}

char	*ft_strdup(const char *s)
{
	int		ls;
	char	*ptr;
	int		i;

	ls = getlen ((char *)s);
	ptr = (char *) malloc ((ls + 1) * sizeof(const char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (i < ls)
	{
		ptr[i] = s[i];
		i ++;
	}
	ptr[i] = '\0';
	return (ptr);
}
