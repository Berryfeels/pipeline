/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stdi-pum <stdi-pum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:52:18 by stdi-pum          #+#    #+#             */
/*   Updated: 2024/09/13 17:33:51 by stdi-pum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	free_results(char **results)
{
	int	i;

	i = 0;
	while (results[i]) 
	{
		free(results[i++]);
	}
	free(results);
}

static char	*ft_eiterate(char **path, char **envp_paths, char *cmd)
{
	char	*add_slash;
	int		i;

	i = 0;
	while (envp_paths[i])
	{
		add_slash = ft_strjoin (envp_paths[i], "/");
		if (add_slash == NULL)
			return (NULL);
		(*path) = ft_strjoin (add_slash, cmd);
		if (*path == NULL)
			return (NULL);
		free(add_slash);
		if (access (*path, X_OK) == 0)
			return (*path);
		free(*path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**envp_paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr (envp[i], "PATH", 4) == 0)
		i++;
	if (!envp[i]) 
	{
		perror("PATH not found in environment variables");
		return (NULL);
	}
	envp_paths = ft_split (envp[i] + 5, ':');
	if (!envp_paths) 
	{
		perror ("Error: ft_split failed\n");
		return (NULL);
	}
	fprintf(stderr, "finding path before eiterate\n");
	path = ft_eiterate(&path, envp_paths, cmd);
	fprintf(stderr, "path is: %s\n", path);
	free_results(envp_paths);
	if (path != NULL)
		return (path);
	return (0);
}

int	execute(char *cmd_argv, char **envp)
{
	char	**cmds;
	char	*path;

	fprintf(stderr, "executing\n");
	cmds = ft_split(cmd_argv, ' ');
	if (!cmds) 
	{
		perror ("Error: ft_split failed\n");
		return (1);
	}
	path = find_path (cmds[0], envp);
	if (!path)
	{
		perror("Error, no path found");
		free_results(cmds);
		return (1);
	}
	int i = 0;
	while(cmds[i])
	{
		fprintf(stderr, "cmds[%d] is: %s\n", i, cmds[i]);
		i++;
	}
	
	if (execve(path, cmds, envp) == -1)
	{
		perror("Error at execve");
		return (1);
	}
	return (0);
}

int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error();
	return (file);
}

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}