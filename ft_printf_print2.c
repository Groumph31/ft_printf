/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_print2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 10:54:04 by romain            #+#    #+#             */
/*   Updated: 2020/11/17 19:37:58 by romain           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_signed_digit(char tab[], int size, t_pars *pars)
{
	int	i;
	int	max;

	i = 1;
	max = size < pars->precision_val ? pars->precision_val : size;
	if (!pars->boundary_left)
	{
		while (i++ + max < pars->field_width_val)
			write(1, " ", 1);
		i--;
	}
	write(1, "-", 1);
	while (i++ + size < pars->precision_val)
		write(1, "0", 1);
	write(1, tab, size);
	i--;
	while (pars->boundary_left && i++ + size < pars->field_width_val)
		write(1, " ", 1);
	return (i + size - 1);
}

int		print_unsigned_digit(char *str, int size, t_pars *pars)
{
	int	i;
	int	i2;

	i = 0;
	i2 = 0;
	if (pars->precision_bool == 0)
		pars->precision_val = 1;
	if (pars->boundary_left)
	{
		while (i++ + size < pars->precision_val)
			write(1, "0", 1);
		write(1, str, size);
		i--;
		while (i++ + size < pars->field_width_val)
			write(1, " ", 1);
		return (size + i - 1);
	}
	while (i++ < pars->field_width_val - pars->precision_val)
		write(1, " ", 1);
	i--;
	while (i2++ + size < pars->precision_val)
		write(1, "0", 1);
	write(1, str, size);
	return (size + i + i2 - 1);
}

int		print_string(char *str, t_pars *pars, char *strnull, char *strvide)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	if (!str && (pars->precision_val >= 6 || !pars->precision_bool))
		str = strnull;
	else if (!str)
		str = strvide;
	while (str[max])
		max++;
	if (pars->precision_bool)
		max = max < pars->precision_val ? max : pars->precision_val;
	if (pars->boundary_left)
	{
		write(1, str, max);
		while (max++ < pars->field_width_val)
			write(1, " ", 1);
		return (max - 1);
	}
	while (i++ + max < pars->field_width_val)
		write(1, " ", 1);
	write(1, str, max);
	return (max + i - 1);
}

int		print_addr_hexa(unsigned long pt, int ind, int i, t_pars *pars)
{
	int	max;

	if (i == 1)
	{
		pars->zero_padded ? write(1, "0x", 2) : write(1, "0x", 0);
		max = 12 < pars->precision_val && pars->precision_bool ?
			pars->precision_val : 12;
		while (max + ind++ + 2 < pars->field_width_val
				&& !pars->boundary_left)
			pars->zero_padded ? write(1, "0", 1) : write(1, " ", 1);
		ind--;
		pars->zero_padded ? write(1, "", 0) : write(1, "0x", 2);
		while (ind++ < max - 12)
			write(1, "0", 1);
		ind += pars->boundary_left ? 0 : 13;
	}
	if (i < 12)
		(print_addr_hexa(pt / 16, 0, i + 1, pars));
	write(1, &"0123456789abcdef"[pt % 16], 1);
	while (i == 1 && max + ind++ + 2 <= pars->field_width_val
			&& pars->boundary_left)
		write(1, " ", 1);
	ind += pars->boundary_left ? 12 : 0;
	return (ind);
}
