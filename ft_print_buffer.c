/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_buffer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 06:22:19 by romain            #+#    #+#             */
/*   Updated: 2020/11/22 22:15:36 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_buffer	buf;

void		print_buffer(int fd)
{
		write(fd, buf.bufstr, buf.i);
		buf.totalsize += buf.i;
		buf.i = 0;
}

void		write_str_buffer(char *str, int size)
{
	int	i2;

	i2 = 0;
	while (i2 < size)
	{
		buf.bufstr[buf.i++] = str[i2++];
		if (buf.i == BUFFER_SIZE)
			print_buffer(1);
	}
}

void		write_char_buffer(char c, int nb)
{
	int	i2;

	i2 = 0;
	while (i2++ < nb)
	{
		buf.bufstr[buf.i++] = c;
		if (buf.i == BUFFER_SIZE)
			print_buffer(1);
	}
}

int		send_totalsize(void)
{
	return (buf.totalsize + buf.i);
}

void	init_buffer(void)
{
	buf.i = 0;
	buf.totalsize = 0;
}