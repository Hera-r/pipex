/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:36:16 by hrandria          #+#    #+#             */
/*   Updated: 2023/03/24 15:35:45 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

void	ftab(char **tab);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_printf(const char *fmt, ...);
int		argv_error(int argc);
int		ft_putchar(char c);
int		ft_putstr(char *s);
void	ft_putnbr(int nb, int *result);
void	ft_hexadecimal(unsigned int nb, int *result, char c);
void	ft_nbunsigned(unsigned int nb, int *result);
void	ft_pointer(void *n, int *result);
void	ft_hexpointer(unsigned long long nb, int *result);
void	ft_format(char fmt, va_list vl, int *result);
char	**get_path(char **envp);
char	*access_ok(char **tab, char **args);
int		ft_chan(int fd_pipe, int fd);
int		find_slash(char	*argv);
char	*final_path(char *argv, char **envp);

typedef struct t_fd{
	int	first;
	int	second;
}			t_fd;
t_fd	get_file_descriptor(char **argv);
size_t	ft_len(const char *s);
void	first_cmd(int fd_pipe[], t_fd fd, char **argv, char **envp);
void	second_cmd(int fd_pipe[], t_fd fd, char **argv, char **envp);
void	ft_close_fd(t_fd fd);
char	*half_access(char *argv, char **envp);
int		pipex(char **argv, char **envp, t_fd fd);
int		first_execve(t_fd fd, char **argv, char **envp, int fd_pipe1);
int		second_execve(char **argv, char **envp, int fd_pipe0, t_fd fd);
int		test_pipe_and_fd(int *fd_pipe);

#endif
