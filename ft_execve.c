/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:12:47 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/27 15:05:41 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_execve(t_fd fd, char **argv, char **envp, int fd_pipe1)
{
	char	*path;
	char	**args;

	if (ft_strlen(argv[2]) != 0)
	{
		path = final_path(argv[2], envp);
		if (ft_strlen(argv[3]) == 0)
			ft_chan(fd.first, fd.second);
		else
			ft_chan(fd.first, fd_pipe1);
		args = ft_split(argv[2], ' ');
		if (!args)
			return (0);
		if (execve(path, args, NULL) == -1)
			perror("execve");
	}
	return (-1);
}

int	second_execve(char *argv, char **envp, int fd_pipe0, int fd2)
{
	char		*path;
	char		**args;

	args = NULL;
	if (ft_strlen(argv) != 0)
	{
		path = final_path(argv, envp);
		ft_chan(fd_pipe0, fd2);
		args = ft_split(argv, ' ');
		if (!args)
			return (0);
		if (execve(path, args, NULL) == -1)
			perror("execve");
	}
	free(args);
	return (-1);
}
