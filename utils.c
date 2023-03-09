/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:08 by hrandria          #+#    #+#             */
/*   Updated: 2023/03/09 12:39:42 by hrandria         ###   ########.fr       */
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

int	read_and_write(int fd1, int fd2)
{
	char		buffer[1024];
	ssize_t		bytes_read;
	ssize_t		bytes_written;

	bytes_read = read(fd1, buffer, sizeof(buffer));
	buffer[bytes_read] = '\0';
	if (bytes_read == -1)
	{
		perror("Erreur lors de la lecture du fichier");
		exit(EXIT_FAILURE);
	}
	bytes_written = write(fd2, buffer, ft_len(buffer));
	if (bytes_written == -1)
	{
		perror("Erreur lors de l'écriture dans le fichier");
		exit(EXIT_FAILURE);
	}
	return (close(fd1), close(fd2), 1);
}

int	test_pipe_and_fd(t_fd fd, int *fd_pipe, char **argv)
{
	if (ft_len(argv[2]) == 0 && ft_len(argv[3]) == 0)
		return (read_and_write(fd.first, fd.second), -1);
	if (pipe(fd_pipe) == -1)
		return (perror("Erreur de création du canal de communication"), 1);
	return (-1);
}
