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
	return (tab);
}

int	access_execve(char **tab, char **args)
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
		{
			if (execve(path, args, NULL) == -1);
				perror("execve");
			break;
		}
	i++;
	}
	return (-1);
}

int	ft_chan(int fd_pipe, int fd)
{
	if (dup2(fd_pipe, STDIN_FILENO) < 0)
		perror("Erreur de redirection de la sortie standard");
	if (dup2(fd, STDOUT_FILENO) < 0)
		perror("Erreur de redirection de la sortie standard");
	return (-1);
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
	int			i;

	i = 0;
	if (argc == 5)
	{
		fd1 = open(argv[1], O_RDONLY);
		fd2 = open(argv[4], O_CREAT | O_WRONLY, 0644);
		if (fd1 < 0 || fd2 < 0)
			perror("Erreur d'ouverture du fichier");
		args = ft_split(argv[2], ' ');

		if (pipe(fd_pipe) == -1)
			return (perror("Erreur de création du canal de communication"), 1);

		pid = fork();
		if (pid == -1)
			return (perror("Erreur de création du processus fils"), 1);
		else if (pid == 0)
		{
			close(fd_pipe[0]);
			ft_chan(fd1, fd_pipe[1]);
			tab = get_path(envp);
			access_execve(tab, args);
			exit(EXIT_SUCCESS);
		} else {
			close(fd_pipe[1]);
			ft_chan(fd_pipe[0], fd2);
			tab = get_path(envp);
			args = ft_split(argv[3], ' ');
			access_execve(tab, args);
			wait(&status);
		}
		close(fd1);
		close(fd2);
	}
	return (0);
}

// <infile ls -l | wc -l > outfile