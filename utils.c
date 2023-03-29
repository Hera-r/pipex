/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:08 by hrandria          #+#    #+#             */
/*   Updated: 2023/03/24 15:23:50 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ftab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
	i++;
	}
	free(tab);
	tab = NULL;
}

int	ft_chan(int fd_pipe, int fd)
{
	if (dup2(fd_pipe, STDIN_FILENO) < 0)
		perror("Erreur de redirection");
	close(fd_pipe);
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("Erreur de redirection");
	close(fd);
	return (-1);
}

int	find_slash(char	*argv)
{
	int		i;
	char	**argv_split;

	i = 0;
	argv_split = ft_split(argv, ' ');
	if (!argv_split)
		return (0);
	while (argv_split[0][i])
	{
		if (argv_split[0][i] == '/')
			return (ftab(argv_split), argv_split = NULL, 1);
	i++;
	}
	return (ftab(argv_split), argv_split = NULL, 0);
}

int	test_pipe_and_fd(int *fd_pipe)
{
	if (pipe(fd_pipe) == -1)
		return (perror("Erreur de création du canal de communication"), 1);
	return (-1);
}

void	ft_close_fd(t_fd fd)
{
	if (fd.first != -1)
		close(fd.first);
	if (fd.second != -1)
		close(fd.second);
}
