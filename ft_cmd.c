/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mle-bras <mle-bras@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:11:18 by hrandria          #+#    #+#             */
/*   Updated: 2023/03/25 15:18:12 by mle-bras         ###   ########.fr       */
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
			ft_close_fd(fd);
			exit(EXIT_FAILURE);
		}
		close(fd.first);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}

void	second_cmd(int fd_pipe[], t_fd fd, char **argv, char **envp)
{
	close(fd_pipe[1]);
	if (second_execve(argv, envp, fd_pipe[0], fd) != 0)
	{
		close(fd_pipe[0]);
		ft_close_fd(fd);
		exit(EXIT_FAILURE);
	}
	close(fd.second);
	exit(EXIT_SUCCESS);
}
