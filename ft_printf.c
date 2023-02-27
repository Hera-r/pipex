/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hrandria <hrandria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:45:02 by hrandria          #+#    #+#             */
/*   Updated: 2023/02/27 15:24:45 by hrandria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_printf(const char *fmt, ...)
{
	int		result;
	va_list	vl;

	va_start(vl, fmt);
	result = 0;
	while (*fmt != '\0')
	{
		if (*fmt == '%')
		{
			fmt++;
			ft_format(*fmt, vl, &result);
		}
		else
			result += ft_putchar(*fmt);
		fmt++;
	}
	va_end(vl);
	return (result);
}
