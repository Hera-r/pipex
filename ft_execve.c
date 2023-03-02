/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:12:47 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/27 15:24:49 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_execve(t_fd fd, char **argv, char **envp, int fd_pipe1)
{
	char	*path;
	char	**args;

	args = NULL;
	if (ft_len(argv[2]) != 0)
	{
		path = final_path(argv[2], envp);
		if (ft_len(argv[3]) == 0)
			ft_chan(fd.first, fd.second);
		else
			ft_chan(fd.first, fd_pipe1);
		args = ft_split(argv[2], ' ');
		if (!args)
			return (0);
		if (execve(path, args, NULL) == -1)
		{
			ftab(args);
			perror("execve");
		}
	}
	ftab(args);
	return (-1);
}

int	second_execve(char **argv, char **envp, int fd_pipe0, t_fd fd)
{
	char		*path;
	char		**args;

	args = NULL;
	if (ft_len(argv[3]) != 0)
	{
		path = final_path(argv[3], envp);
		if (ft_len(argv[2]) == 0)
			ft_chan(fd.first, fd.second);
		else
			ft_chan(fd_pipe0, fd.second);
		args = ft_split(argv[3], ' ');
		if (!args)
			return (0);
		if (execve(path, args, NULL) == -1)
		{
			ftab(args);
			perror("execve");
		}
	}
	return (-1);
}
