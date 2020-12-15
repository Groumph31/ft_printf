/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_zero.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: romain <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 07:22:35 by romain            #+#    #+#             */
/*   Updated: 2020/12/15 12:11:23 by rsanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_zero(void *pt, size_t n)
{
	unsigned char	*tempt;

	tempt = (unsigned char*)pt;
	while (n--)
		*tempt++ = '\0';
}
