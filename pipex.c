#include "pipex.h"

char	**get_path(char **envp)
{
	char	**tab;
	int	i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
		{
			tab = ft_split(envp[i] + 5, ':');
			if (!tab)
				return (NULL);
			return (tab);
		}
		i++;
	}
	return (0);
}

char	*access_ok(char **tab, char **args)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (tab[i])
	{
		tmp = ft_strjoin(tab[i], "/");
		path = ft_strjoin(tmp, args[0]);
		if (access(path, F_OK) != -1)
			return (free(tmp), path);
	i++;
	free(tmp);
	free(path);
	}
	return (0);
}

int	ft_chan(int fd_pipe, int fd)
{
	if (dup2(fd_pipe, STDIN_FILENO) < 0)
		perror("Erreur de redirection de la sortie standard");
	
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("Erreur de redirection de la sortie standard");

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

char	*final_path(char *argv, char **envp)
{
	char	**tab;
	char	**args;
	char	*path;

	if (find_slash(argv) == 1)
	{
		tab = ft_split(argv, ' ');
		if (access(tab[0], F_OK) != -1)
			return (tab[0]);
	}
	else
	{
		tab = get_path(envp);
		args = ft_split(argv, ' ');
		path = access_ok(tab, args);
		if (!path)
			return (printf("command not found\n"), exit(EXIT_FAILURE), NULL);
	}
	return (path);
}

int	read_and_write(int fd1, int fd2)
{
	char buffer[1024];
    ssize_t bytes_read;
	ssize_t bytes_written;

	bytes_read = read(fd1, buffer, sizeof(buffer));
	buffer[bytes_read] = '\0';
	if (bytes_read == -1) {
        perror("Erreur lors de la lecture du fichier");
        exit(EXIT_FAILURE);
    }
	bytes_written = write(fd2, buffer, ft_strlen(buffer));
    if (bytes_written == -1) {
        perror("Erreur lors de l'écriture dans le fichier");
        exit(EXIT_FAILURE);
    }
	return (1);
}

int	main(int argc, char *argv[], char *envp[]) 
{
	char		**tab;
	int 		fd1;
	int 		fd2;
	int 		fd_pipe[2];
	pid_t		pid;
	char		**args;
	int 		status;
	char		*path;
	int			i;

	i = 0;
	if (argc == 5)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[4], O_CREAT | O_WRONLY, 0644);
		if (fd1 < 0 || fd2 < 0)
			perror("Erreur d'ouverture du fichier");
		if (ft_strlen(argv[2]) == 0 && ft_strlen(argv[3]) == 0)
			return (read_and_write(fd1, fd2));
		if (pipe(fd_pipe) == -1)
			return (perror("Erreur de création du canal de communication"), 1);

		pid = fork();
		if (pid == -1)
			return (perror("Erreur de création du processus fils"), 1);
		else if (pid == 0)
		{
			close(fd_pipe[0]);
			if (ft_strlen(argv[2]) != 0)
			{
				path = final_path(argv[2], envp);
				if (ft_strlen(argv[3]) == 0)
					ft_chan(fd1, fd2);
				else
					ft_chan(fd1, fd_pipe[1]);
				args = ft_split(argv[2], ' ');
				if (execve(path, args, NULL) == -1);
					perror("execve");
			}
			exit(EXIT_SUCCESS);
		} else {
			close(fd_pipe[1]);
			if (ft_strlen(argv[3]) != 0)
			{
				path = final_path(argv[3], envp);
				ft_chan(fd_pipe[0], fd2);
				args = ft_split(argv[3], ' ');
				if (execve(path, args, NULL) == -1);
					perror("execve");
			}
			wait(&status);
		}
		close(fd1);
		close(fd2);
	}
	return (0);
}

// TO DO : 
	// - faire la factorisation du code à la norme
	// - verifier les leaks
