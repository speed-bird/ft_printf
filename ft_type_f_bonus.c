/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_f_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:20 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 12:57:59 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len_f(double nbr, t_arg *arg)
{
	int	len;

	len = ft_len_lu((long)nbr);
	if ((arg->precision > 0 && (arg->type == 'f'
				|| nbr - (long)nbr)) || arg->flag_ht)
		len += arg->precision + 1;
	return (len);
}

static void	ft_put_f(long double nbr, t_arg *arg)
{
	long double	deci;
	int			i;
	char		n;

	deci = nbr - (long)nbr;
	ft_put_lu_b(nbr, arg);
	if (arg->flag_ht || (arg->precision && (deci || arg->type == 'f')))
	{
		write(1, ".", 1);
		i = 0;
		while (i++ < arg->precision)
		{
			deci = deci * 10 - (long)deci * 10;
			n = (long unsigned)deci % 10 + 48;
			write(1, &n, 1);
		}
	}
}

static void	ft_round_f(long double *n, t_arg *arg)
{
	int	i;

	if (arg->type == 'g' && ((int)*n || !*n))
		arg->precision = arg->precision - ft_len_lu(*n);
	i = 0;
	if (*n - (long)*n)
	{
		while (i++ < arg->precision)
		{
			if (arg->type == 'g' && !arg->flag_ht && !(long)(*n * 10))
				arg->precision++;
			*n *= 10;
		}
	}
	if (*n - (long)*n > 0.5 || (*n - (long)*n == 0.5 && (long)*n % 2))
		++*n;
	while (--i > 0 && *n && arg->type == 'g'
		&& !arg->flag_ht && !((long)*n % 10))
	{
		*n /= 10;
		arg->precision--;
	}
	while (i-- > 0)
		*n /= 10;
}

void	ft_type_f(long double nbr, t_arg *arg, int *counter)
{
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
		if (arg->precision < 0)
			arg->precision = 6;
		ft_round_f(&nbr, arg);
		arg->len = ft_len_f(nbr, arg);
		ft_pad_left(arg, counter);
		ft_put_f(nbr, arg);
	}
}
