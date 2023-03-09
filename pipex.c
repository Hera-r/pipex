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
		perror("Erreur d'ouverture du fichier");
	fd.second = open(argv[4], O_CREAT | O_WRONLY, 0644);
	if (fd.second < 0)
		perror("Erreur d'ouverture du fichier");
	if (fd.first < 0 && fd.second > 0)
		close(fd.second);
	if (fd.second < 0 && fd.first > 0)
		close(fd.first);
	return (fd);
}

int	pipex(char **argv, char **envp, t_fd fd)
{
	pid_t		pid;
	int			status;
	int			fd_pipe[2];

	test_pipe_and_fd(fd, fd_pipe, argv);
	pid = fork();
	if (pid == -1)
		return (perror("Erreur de création du processus fils"), 1);
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		first_execve(fd, argv, envp, fd_pipe[1]);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd_pipe[1]);
		second_execve(argv, envp, fd_pipe[0], fd);
		wait(&status);
	}
	close(fd.first);
	close(fd.second);
	return (-1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_fd		fd;

	if (argc == 5)
	{
		fd = get_file_descriptor(argv);
		if (fd.first == -1 || fd.second == -1)
			return (-1);
		pipex(argv, envp, fd);
	}
	else
	{
		if (argc > 5)
		{
			ft_printf("Erreur : Trop d'arguments.\n");
			return (1);
		}
		else if (argc < 5)
		{
			ft_printf("Erreur : Pas assez d'arguments.\n");
			return (1);
		}
	}
	return (0);
}
