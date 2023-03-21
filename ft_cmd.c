/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:11:18 by hrandria          #+#    #+#             */
/*   Updated: 2023/03/21 13:18:23 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	first_cmd(int fd_pipe[], t_fd fd, char **argv, char **envp)
{
	close(fd_pipe[0]);
	if (fd.first > 0)
	{
		if (first_execve(fd, argv, envp, fd_pipe[1]) != 0)
		{
			close(fd_pipe[1]);
			close(fd.first);
			close(fd.second);
			exit(EXIT_FAILURE);
		}
	}
	exit(EXIT_FAILURE);
}

void	second_cmd(int fd_pipe[], t_fd fd, char **argv, char **envp)
{
	close(fd_pipe[1]);
	if (second_execve(argv, envp, fd_pipe[0], fd) != 0)
	{
		close(fd_pipe[0]);
		close(fd.first);
		close(fd.second);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}
