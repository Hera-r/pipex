/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/26 21:41:54 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 21:41:54 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_fd	get_file_descriptor(char **argv)
{
	t_fd	fd;

	fd.first = open(argv[1], O_RDONLY);
	if (fd.first < 0)
		perror(argv[1]);
	fd.second = open(argv[4], O_CREAT | O_WRONLY, 0644);
	if (fd.second < 0)
		perror(argv[4]);
	return (fd);
}

void	cmd_pid(char **argv, char **envp, t_fd fd, int fd_pipe[])
{
	if (fd.first < 0)
		exit(EXIT_FAILURE);
	else
		first_cmd(fd_pipe, fd, argv, envp);
}

void	cmd_pid2(char **argv, char **envp, t_fd fd, int fd_pipe[])
{
	if (fd.second < 0)
		exit(EXIT_FAILURE);
	else
		second_cmd(fd_pipe, fd, argv, envp);
}

int	pipex(char **argv, char **envp, t_fd fd)
{
	pid_t		pid;
	pid_t		pid2;
	int			fd_pipe[2];

	test_pipe_and_fd(fd_pipe);
	pid = fork();
	if (pid == -1)
		return (perror("Erreur de création du processus fils"), 1);
	else if (pid == 0)
		cmd_pid(argv, envp, fd, fd_pipe);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
		cmd_pid2(argv, envp, fd, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	ft_close_fd(fd);
	return (1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_fd		fd;

	if (argc == 5)
	{
		if (ft_len(argv[2]) == 0 && ft_len(argv[3]) == 0)
		{
			ft_printf("\"\" : Commande introuvable\n");
			fd.second = open(argv[4], O_CREAT | O_WRONLY, 0644);
			if (fd.second == -1)
				return (perror(argv[4]), 1);
			ft_printf("\"\" : Commande introuvable\n");
			return (close(fd.second), 1);
		}
		fd = get_file_descriptor(argv);
		pipex(argv, envp, fd);
	}
	else
	{
		argv_error(argc);
	}
	return (0);
}
