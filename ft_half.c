/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_half.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 14:58:02 by hrandria          #+#    #+#             */
/*   Updated: 2023/03/29 11:50:02 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	msg_err(char *cmd, int i)
{
	if (i == 1)
		ft_printf("%s: Aucun fichier ou dossier de ce type\n", cmd);
	else
		ft_printf("%s: commande introuvable\n", cmd);
}

char	*half_access(char *argv, char **envp)
{
	char	**tab;
	char	**args;
	char	*path;

	tab = get_path(envp);
	if (!tab)
		return (msg_err(argv, 1), NULL);
	args = ft_split(argv, ' ');
	if (!args)
		return (NULL);
	path = access_ok(tab, args);
	if (!path)
	{
		ftab(tab);
		ftab(args);
		msg_err(argv, 2);
		return (NULL);
	}
	ftab(tab);
	ftab(args);
	return (path);
}
