/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/23 15:17:51 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void		write_addr_null(t_flags *flags)
{
	int	maxprint;
	int	space_toprint;
	int	zero_toprint;

	maxprint = 3;
	if (flags->bw_flags & PRECIS)
		maxprint = flags->precision_val + 2;
	space_toprint = flags->field_width_val - maxprint;
	zero_toprint = maxprint - 2;
	if (!(flags->bw_flags & MINUS))
		write_char_buffer(' ', space_toprint);
	write_str_buffer("0x", 2);
	write_char_buffer('0', zero_toprint);
	if (flags->bw_flags & MINUS)
		write_char_buffer(' ', space_toprint);
}

static void		write_addr_boundary(t_flags *flags, unsigned long pt,
								int size)
{
	int	maxprint;
	int	space_toprint;
	int	zero_toprint;

	maxprint = size;
	if (flags->bw_flags & PRECIS && size < flags->precision_val)
		maxprint = flags->precision_val;
	space_toprint = flags->field_width_val - maxprint - 2;
	zero_toprint = maxprint - size - 2;
	write_str_buffer("0x", 2);
	write_char_buffer('0', zero_toprint);
	write_base_recurs(pt, "0123456789abcdef", 16, 50);
	write_char_buffer(' ', space_toprint);
}

static void		write_addr_zeropadded(t_flags *flags, unsigned long pt,
								int size)
{
	int	zero_toprint;

	write_str_buffer("0x", 2);
	zero_toprint = flags->field_width_val - size;
	write_char_buffer('0', zero_toprint);
	write_base_recurs(pt, "0123456789abcdef", 16, 50);
}

static void		write_addr(t_flags *flags, unsigned long pt, int size)
{
	int maxprint;
	int space_toprint;
	int zero_toprint;

	maxprint = size;
	if (flags->bw_flags & PRECIS && size < flags->precision_val)
		maxprint = flags->precision_val;
	space_toprint = flags->field_width_val - maxprint - 2;
	zero_toprint = maxprint - size;
	write_char_buffer(' ', space_toprint);
	write_str_buffer("0x", 2);
	write_char_buffer('0', zero_toprint);
	write_base_recurs(pt, "0123456789abcdef", 16, 50);
}

void			write_p(va_list *param, t_flags *flags)
{
	unsigned long	pt;
	int				size;

	pt = va_arg(*param, unsigned long);
	if (!pt)
		return (write_addr_null(flags));
	size = my_utoa_len(pt, 16, NULL);
	if (flags->bw_flags & MINUS)
		write_addr_boundary(flags, pt, size);
	else if (flags->bw_flags & ZERO)
		write_addr_zeropadded(flags, pt, size);
	else
		write_addr(flags, pt, size);
}