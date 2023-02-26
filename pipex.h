/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:36:16 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/26 21:50:16 by hrandria         ###   ########.fr       */
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

size_t	ft_strlen(const char *s);
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


#endif
