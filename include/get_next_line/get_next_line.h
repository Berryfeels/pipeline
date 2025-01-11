/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 14:10:30 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/03/01 19:32:41 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

//# include <limits.h>
//# include <stdarg.h>
//# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
//# include <string.h>
# include <unistd.h>
# include <sys/uio.h>
# include <sys/types.h>

int		getlen(char *str);
char	*ft_strjoin_get_next_line(char *s1, char *s2);
char	*get_next_line(int fd);
void	emptybuff(char *buff);

#endif
