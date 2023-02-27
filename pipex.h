/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:36:16 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/27 18:06:52 by hrandria         ###   ########.fr       */
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

size_t	ft_len(const char *s);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
int		ft_printf(const char *fmt, ...);
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
int		read_and_write(int fd1, int fd2);
int		pipex(char **argv, char **envp);

typedef struct t_fd{
	int	first;
	int	second;
}			t_fd;
t_fd	get_file_descriptor(char **argv);
int		first_execve(t_fd fd, char **argv, char **envp, int fd_pipe1);
int		second_execve(char *argv, char **envp, int fd_pipe0, int fd2);
int		test_pipe_and_fd(t_fd fd, int *fd_pipe, char **argv);

#endif
