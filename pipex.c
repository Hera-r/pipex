#include "pipex.h"

int	main(int argc, char *argv[], char *envp[]) 
{
	char		**tab;
	char		*tmp;
	char		*path;
	int 		fd1;
	int 		fd2;
	int			i;
	int 		fd_pipe[2];
	pid_t		pid;
	char		**args;

	i = 0;
	fd1 = open("infile", O_RDONLY);
	fd2 = open("outfile", O_CREAT | O_WRONLY, 0644);
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
		if (dup2(fd1, STDIN_FILENO) < 0)
			perror("Erreur de redirection de la sortie standard");

		if (dup2(fd_pipe[1], STDOUT_FILENO) < 0)
			perror("Erreur de redirection de la sortie standard");

		// get_env
		while (envp[i])
		{
			if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
			{
				tab = ft_split(envp[i] + 5, ':');
				break ;
			}
			i++;
		}
		i = 0;
		// une fonction déjà
		while (tab[i])
		{
			tmp = ft_strjoin(tab[i], "/");
			path = ft_strjoin(tmp, args[0]);
			if (access(path, F_OK) != -1)
			{
				execve(path, args, NULL);
				break ;
			}
		i++;
		}
	}else{
		close(fd_pipe[1]);
		if (dup2(fd_pipe[0], STDIN_FILENO) < 0)
			perror("Erreur de redirection de la sortie standard");
		if (dup2(fd2, STDOUT_FILENO) < 0)
			perror("Erreur de redirection de la sortie standard");
		i = 0;
		while (envp[i])
		{
			if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H')
			{
				tab = ft_split(envp[i] + 5, ':');
				break ;
			}
			i++;
		}
		i = 0;
		// une fonction déjà
		args = ft_split(argv[3], ' ');
		while (tab[i])
		{
			tmp = ft_strjoin(tab[i], "/");
			path = ft_strjoin(tmp, args[0]);
			if (access(path, F_OK) != -1)
			{
				execve(path, args, NULL);
				break ;
			}
		i++;
		}
	}

	close(fd1);
    close(fd2);
	return (0);
}
