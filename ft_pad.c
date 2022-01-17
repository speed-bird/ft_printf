/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:04:11 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/04 17:04:13 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putxdigits(t_arg *arg, int *counter)
{
	int	i;

	i = arg->precision;
	if (arg->type == 'd' || arg->type == 'i' || arg->type == 'p'
		|| arg->type == 'u' || arg->type == 'x' || arg->type == 'X')
	{
		while (i-- > arg->len)
		{
			write(1, "0", 1);
			++*counter;
		}
	}
}

static void	ft_printsize(t_arg *arg)
{
	if (arg->type)
		arg->printsize = arg->len;
	else
		arg->printsize = 1;
	if (arg->type == 's' && arg->precision > -1 && arg->len > arg->precision)
		arg->printsize = arg->precision;
	else if ((arg->type == 'd' || arg->type == 'i' || arg->type == 'u'
			|| arg->type == 'x' || arg->type == 'X')
		&& arg->len < arg->precision)
		arg->printsize = arg->precision;
	if (arg->sign || ((arg->flag_plus || arg->flag_space) && (arg->type == 'd'
				|| arg->type == 'i' || arg->type == 'g' || arg->type == 'e'
				|| arg->type == 'f')))
		arg->printsize++;
	if (arg->prefix)
		arg->printsize += 2;
}

static void	ft_put_sign_prefix(t_arg *arg, int *counter)
{
	if (arg->sign == -1)
	{
		write(1, "-", 1);
		++*counter;
	}
	else if (!arg->sign && arg->flag_plus && (arg->type == 'd'
			|| arg->type == 'i' || arg->type == 'g' || arg->type == 'e'
			|| arg->type == 'f'))
	{
		write(1, "+", 1);
		++*counter;
	}
	if (arg->prefix)
	{
		*counter += 2;
		if (arg->type == 'X')
			write(1, "0X", 2);
		else
			write(1, "0x", 2);
	}
}

void	ft_pad_left(t_arg *arg, int *counter)
{
	ft_printsize(arg);
	if (arg->flag_zero)
		ft_put_sign_prefix(arg, counter);
	if (!arg->sign && arg->flag_space && (arg->type == 'd' || arg->type == 'i'
			|| arg->type == 'g' || arg->type == 'e' || arg->type == 'f'))
	{
		write(1, " ", 1);
		++*counter;
	}
	while (!arg->flag_min && arg->minfield-- > arg->printsize)
	{
		if (arg->flag_zero)
			write(1, "0", 1);
		else
			write(1, " ", 1);
		++*counter;
	}
	if (!arg->flag_zero)
		ft_put_sign_prefix(arg, counter);
	ft_putxdigits(arg, counter);
}

void	ft_pad_right(t_arg *arg, int *counter)
{
	if (arg->flag_min)
	{
		while (arg->minfield-- > arg->printsize)
		{
			write(1, " ", 1);
			++*counter;
		}
	}
}
