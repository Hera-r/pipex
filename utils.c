/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:06:08 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/27 15:08:35 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_chan(int fd_pipe, int fd)
{
	if (dup2(fd_pipe, STDIN_FILENO) < 0)
		perror("Erreur de redirection");
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("Erreur de redirection");
	return (-1);
}

int	find_slash(char	*argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '/')
			return (1);
	i++;
	}
	return (0);
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
	bytes_written = write(fd2, buffer, ft_strlen(buffer));
	if (bytes_written == -1)
	{
		perror("Erreur lors de l'écriture dans le fichier");
		exit(EXIT_FAILURE);
	}
	return (1);
}

int	test_pipe_and_fd(t_fd fd, int *fd_pipe, char **argv)
{
	if (ft_strlen(argv[2]) == 0 && ft_strlen(argv[3]) == 0)
		return (read_and_write(fd.first, fd.second));
	if (pipe(fd_pipe) == -1)
		return (perror("Erreur de création du canal de communication"), 1);
	return (-1);
}
