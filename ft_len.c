/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:08:13 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/19 14:13:11 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_len_lu(long unsigned n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int	ft_len_hex(long unsigned x)
{
	long unsigned	temp;
	int				len;

	len = 1;
	temp = 1;
	while (temp <= x / 16)
		temp *= 16;
	while (temp / 16 >= 1)
	{
		len++;
		x %= temp;
		temp /= 16;
	}
	return (len);
}

int	ft_len_s(char *s)
{
	int	size;

	size = 0;
	if (!s)
		s = "(null)";
	while (*s++)
		size++;
	return (size);
}

int	ft_len_e(double nbr, t_arg *arg)
{
	int	len;

	len = ft_len_lu((long)nbr) + 2;
	if (arg->e > 99)
		len += ft_len_lu(arg->e);
	else
		len += 2;
	if (arg->precision > 0 || arg->flag_ht)
		len++;
	if (arg->precision > 0)
		len += arg->precision;
	return (len);
}
