/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakada <stakada@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 14:19:18 by stakada           #+#    #+#             */
/*   Updated: 2024/12/17 14:36:20 by stakada          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_dprintf(int fd, const char *fmt, ...)
{
	int		len;
	va_list	ap;

	va_start(ap, fmt);
	len = ft_vdprintf(fd, fmt, ap);
	va_end(ap);
	return (len);
}
