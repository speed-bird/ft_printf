/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:13 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/17 14:37:07 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static long int	ft_len_li(long int n, t_arg *arg)
{
	int	len;

	len = 0;
	if (!n && !arg->precision)
		return (0);
	else if (!n && arg->precision)
		return (1);
	else if (n == -9223372036854775807 - 1)
		return (19);
	else
	{
		if (n < 0)
			n = -n;
		while (n > 0)
		{
			n /= 10;
			len++;
		}
		return (len);
	}
}

static void	ft_put_li(long int n, t_arg *arg)
{
	char	c;

	if (!arg->l_type && n == -2147483648)
		write(1, "2147483648", 11);
	else if (arg->l_type == 'l' && n == -9223372036854775807 - 1)
		write(1, "9223372036854775808", 19);
	else if (n < 0)
	{
		write(1, "-", 1);
		ft_put_li(-n, arg);
	}
	else
	{
		if (n > 9)
			ft_put_li(n / 10, arg);
		c = n % 10 + '0';
		write(1, &c, 1);
	}
}

void	ft_type_di(long int nbr, t_arg *arg, int *counter)
{
	write(1, arg->s, arg->s_len);
	if (!arg->l_type)
		nbr = (int)nbr;
	else if (arg->l_type == 'h' && !arg->ll_type)
		nbr = (short)nbr;
	else if (arg->l_type == 'h' && arg->ll_type == 'h')
		nbr = (char)nbr;
	if (arg->precision >= 0)
		arg->flag_zero = 0;
	arg->len = ft_len_li(nbr, arg);
	if (nbr < 0)
	{
		arg->sign = -1;
		nbr = -nbr;
	}
	ft_pad_left(arg, counter);
	if (nbr || arg->precision)
		ft_put_li(nbr, arg);
}
