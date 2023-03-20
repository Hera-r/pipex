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
	// if (fd.first < 0 && fd.second > 0)
	// 	close(fd.second);
	// if (fd.second < 0 && fd.first > 0)
	// 	close(fd.first);
	return (fd);
}

int	argv_error(int argc)
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
	return (0);
}

int	pipex(char **argv, char **envp, t_fd fd)
{
	pid_t		pid;
	pid_t		pid2;
	int			fd_pipe[2];

	test_pipe_and_fd(fd, fd_pipe, argv);
	pid = fork();
	if (pid == -1)
		return (perror("Erreur de création du processus fils"), 1);
	else if (pid == 0)
	{
		close(fd_pipe[0]);
		if (fd.first > 0)
		{
			if (first_execve(fd, argv, envp, fd_pipe[1]) != 0)
				return (close(fd_pipe[1]), close(fd.first), close(fd.second), 1);
			exit(EXIT_FAILURE);
		}
		exit(EXIT_FAILURE);
	}
    pid2 = fork();
    if (pid2 == -1)
	{
        perror("fork");
        exit(EXIT_FAILURE);
	}
	else if (pid2 == 0)
	{
		close(fd_pipe[1]);
		if (second_execve(argv, envp, fd_pipe[0], fd) != 0)
			return (close(fd_pipe[0]), close(fd.first), close(fd.second), 1);
	}
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (close(fd.first), close(fd.second), 1);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_fd		fd;

	if (argc == 5)
	{
		if (ft_len(argv[2]) == 0 && ft_len(argv[3]) == 0)
		{
			ft_printf("Commande \"\" introuvable\nCommande \"\" introuvable\n");
			fd.second = open(argv[4], O_CREAT | O_WRONLY, 0644);
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
