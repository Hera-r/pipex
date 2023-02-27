/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 14:02:04 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/27 14:49:22 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_path(char **envp)
{
	char	**tab;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A'\
			&& envp[i][2] == 'T' && envp[i][3] == 'H')
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
		free(tmp);
		free(path);
	i++;
	}
	return (0);
}

char	*final_path(char *argv, char **envp)
{
	char	**tab;
	char	**args;
	char	*path;

	path = NULL;
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
		if (!args)
			return (NULL);
		path = access_ok(tab, args);
		if (!path)
			return (printf("command not found\n"), exit(EXIT_FAILURE), NULL);
	}
	return (path);
}
