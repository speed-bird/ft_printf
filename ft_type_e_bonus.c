/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_e_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:16 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 12:57:48 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_exp(t_arg *arg)
{
	write(1, "e", 1);
	if (arg->e >= 0)
		write(1, "+", 1);
	else if (arg->e < 0)
	{
		arg->e = -arg->e;
		write(1, "-", 1);
	}
	if (arg->e < 10)
		write(1, "0", 1);
	ft_put_lu_b(arg->e, arg);
}

static void	ft_put_e(long double nbr_e, t_arg *arg)
{
	long double	deci;
	int			i;
	char		n;

	deci = nbr_e - (long unsigned)nbr_e;
	ft_put_lu_b(nbr_e, arg);
	if (arg->flag_ht || (arg->precision && (deci || arg->type == 'e')))
	{	
		write(1, ".", 1);
		i = 0;
		while (i++ < arg->precision)
		{
			deci = deci * 10 - (long unsigned)deci * 10;
			n = (long unsigned)deci % 10 + 48;
			write(1, &n, 1);
		}
	}
	ft_put_exp(arg);
}

static long double	ft_round_e(long double n, t_arg *arg)
{
	int	i;

	i = 0;
	if (n - (long)n)
	{
		while (i++ < arg->precision)
			n *= 10;
	}
	if (n - (long)n > 0.5 || (n - (long)n == 0.5 && (long)n % 2 != 0))
		++n;
	while (arg->type == 'g' && !arg->flag_ht && (long)n % 10 == 0)
	{
		n /= 10;
		arg->precision--;
		i--;
	}
	while (--i > 0)
		n /= 10;
	if (n >= 10)
	{
		n /= 10;
		arg->e++;
	}
	return (n);
}

static long double	ft_convert_nbr(long double nbr, t_arg *arg)
{
	if (arg->precision < 0)
		arg->precision = 6;
	if (arg->type == 'g')
		arg->precision = arg->precision - 1;
	while (nbr && nbr < 1)
	{
		nbr *= 10;
		arg->e--;
	}
	while (nbr >= 10)
	{
		nbr = (double)nbr / 10;
		arg->e++;
	}
	nbr = ft_round_e(nbr, arg);
	return (nbr);
}

void	ft_type_e(long double nbr, t_arg *arg, int *counter)
{
	long double	nbr_e;

	write(1, arg->s, arg->s_len);
	if (nbr < 0)
	{
		arg->sign = -1;
		nbr = -nbr;
	}
	if (nbr == 1.0 / 0 || nbr == -1.0 / 0 || nbr != nbr)
	{
		arg->len = 3;
		arg->flag_zero = 0;
		ft_pad_left(arg, counter);
	}
	if (nbr == 1.0 / 0 || nbr == -1.0 / 0)
		ft_put_s("inf", arg);
	else if (nbr != nbr)
		ft_put_s("nan", arg);
	else
	{
		nbr_e = ft_convert_nbr(nbr, arg);
		arg->len = ft_len_e(nbr_e, arg);
		ft_pad_left(arg, counter);
		ft_put_e(nbr_e, arg);
	}
}
