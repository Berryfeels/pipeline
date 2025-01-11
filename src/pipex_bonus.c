#include "../include/pipex.h"

// static void	ft_close_pipes(int **pipes, int n)
// {
//     for (int i = 0; i < n; i++)
//     {
//         close(pipes[i][0]);
//         close(pipes[i][1]);
//     }
// }

// static int	ft_execute_process(char *cmd, int *pipe_in, int *pipe_out, char **envp)
// {
//     if (pipe_in != NULL)
//     {
//         dup2(pipe_in[0], STDIN_FILENO);
//         close(pipe_in[0]);
//         close(pipe_in[1]);
//         fprintf(stderr, "pipe_in is: pipe[%ls] and ", pipe_in);
//     }
//     if (pipe_out != NULL)
//     {
//         dup2(pipe_out[1], STDOUT_FILENO);
//         close(pipe_out[0]);
//         close(pipe_out[1]);
//         fprintf(stderr, "pipe_out is: pipe[%ls]\n", pipe_out);
//     }

//     execute(cmd, envp);
//     perror("Error executing command");
//     exit(1); // Termina il processo figlio se execve fallisce
// }

// int	main(int argc, char **argv, char **envp)
// {
//     int		**pipes;
//     pid_t	*pids;
//     int		fd_in, fd_out;

//     if (argc < 5)
//     {
//         ft_printf("Error, no right nr. of args\n");
//         return (1);
//     }

//     int n = argc - 3; // Number of processes needed
//     pipes = malloc((n - 1) * sizeof(int *));
//     pids = malloc(n * sizeof(pid_t));
//     for (int i = 0; i < n; i++)
//     {
//         pipes[i] = malloc(2 * sizeof(int));
//         if (pipe(pipes[i]) == -1)
//             return (1);
//     }

//     fd_in = open(argv[1], O_RDONLY, 0777);
//     if (fd_in == -1)
//     {
//         perror("Error opening input file");
//         return (1);
//     }

//     fd_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd_out == -1)
//     {
//         perror("Error opening output file");
//         return (1);
//     }
//     fprintf(stderr, "fd_in is: %d and fd_out is: %d\n", fd_in, fd_out);
//     dprintf(fd_out, "TesST ----------------\n");
//     for (int i = 0; i < n; i++)
//     {
//         pids[i] = fork();
//         if (pids[i] < 0)
//         {
//             perror("Error forking process");
//             return (2);
//         }
//         if (pids[i] == 0)
//         {
//             if (i == 0)
//             {
//                 dup2(fd_in, STDIN_FILENO);
//                 close(fd_in);
//                 ft_execute_process(argv[2], NULL, pipes[i], envp);
//             }
//             else if (i == n - 1)
//             {
//                 dup2(fd_out, STDOUT_FILENO);
//                 close(fd_out);
//                 ft_execute_process(argv[argc - 2], pipes[i - 1], NULL, envp);
//             }
//             else
//             {
//                 ft_execute_process(argv[i + 2], pipes[i - 1], pipes[i], envp);
//             }
//         }
//     }
//     close(fd_in);
//     close(fd_out);
//     ft_close_pipes(pipes, n);
//     for (int i = 0; i < n; i++)
//         waitpid(pids[i], NULL, 0);
//     free(pids);
//     for (int i = 0; i < (n - 1); i++)
//         free(pipes[i]);
//     free(pipes);

//     return (0);
// }


void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error();
	pid = fork();
	if (pid == -1)
		error();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
}

/* Function who make a child process that will read from the stdin with
 get_next_line until it find the limiter word and then put the output inside a
 pipe. The main process will change his stdin for the pipe file descriptor. */
void	here_doc(char *limiter, int argc)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	if (argc < 6)
		error();
	if (pipe(fd) == -1)
		error();
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		wait(NULL);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	filein;
	int	fileout;

	if (argc >= 5)
	{
		if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		{
			i = 3;
			fileout = open_file(argv[argc - 1], 0);
			here_doc(argv[2], argc);
		}
		else
		{
			i = 2;
			fileout = open_file(argv[argc - 1], 1);
			filein = open_file(argv[1], 2);
			dup2(filein, STDIN_FILENO);
		}
		while (i < argc - 2)
			child_process(argv[i++], envp);
		dup2(fileout, STDOUT_FILENO);
		execute(argv[argc - 2], envp);
	}
	return(0);
}
