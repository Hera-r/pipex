/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:12:47 by hrandria          #+#    #+#             */
/*   Updated: 2023/03/29 12:00:12 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	real_execve(char *path, char **args)
{
	if (execve(path, args, NULL) == -1)
	{
		ftab(args);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return (0);
}

int	first_execve(t_fd fd, char **argv, char **envp, int fd_pipe1)
{
	char	*path;
	char	**args;

	args = NULL;
	if (ft_len(argv[2]) == 0)
		return (ft_printf("\"\" : commande introuvable\n"), 1);
	else
	{
		path = final_path(argv[2], envp);
		if (!path)
			return (close(fd_pipe1), 1);
		ft_chan(fd.first, fd_pipe1);
		args = ft_split(argv[2], ' ');
		if (!args)
			return (1);
		real_execve(path, args);
	}
	return (close(fd_pipe1), 1);
}

int	second_execve(char **argv, char **envp, int fd_pipe0, t_fd fd)
{
	char	*path;
	char	**args;

	args = NULL;
	if (ft_len(argv[3]) == 0)
		return (ft_printf("\"\" : commande introuvable\n"), 1);
	else
	{
		path = final_path(argv[3], envp);
		if (!path)
			return (close(fd_pipe0), 1);
		ft_chan(fd_pipe0, fd.second);
		args = ft_split(argv[3], ' ');
		if (!args)
			return (0);
		real_execve(path, args);
	}
	return (close(fd_pipe0), 1);
}
