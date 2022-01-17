/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_decode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:05:22 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 17:23:17 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_sizeval(const char **format)
{
	int	val;

	val = 0;
	while (**format >= '0' && **format <= '9')
		val = val * 10 + *(*format)++ - 48;
	--*format;
	return (val);
}

static void	ft_flags(const char **format, t_arg *arg)
{
	if (**format == '#')
		arg->flag_ht = 1;
	else if (**format == '0' && !arg->flag_min)
		arg->flag_zero = 1;
	else if (**format == '-')
	{
		arg->flag_zero = 0;
		arg->flag_min = 1;
	}
	else if (**format == ' ' && !arg->flag_plus)
		arg->flag_space = 1;
	else if (**format == '+')
	{
		arg->flag_space = 0;
		arg->flag_plus = 1;
	}	
}

static char	ft_get_type(const char **format, t_arg *arg, int *counter)
{
	if ((!arg->l_type) && (**format == 'd' || **format == 'i'
			|| **format == 'u' || **format == 'x' || **format == 'X'
			|| **format == 'n' || **format == 'e' || **format == 'f'
			|| **format == 'g' || **format == 'p' || **format == 'c'
			|| **format == 's'))
		return (*(*format)++);
	else if ((arg->l_type)
		&& (**format == 'd' || **format == 'i' || **format == 'u'
			|| **format == 'x' || **format == 'X' || **format == 'n'
			|| **format == 'c' || **format == 's'))
		return (*(*format)++);
	else
	{
		write(1, arg->s, arg->s_len);
		ft_pad_left(arg, counter);
		write(1, (*format)++, 1);
		++*counter;
		return (0);
	}
}

static void	ft_scan_format(va_list ap, const char **format, t_arg *arg)
{
	while (**format == '#' || **format == '-' || **format == ' '
		|| **format == '+' || **format == '0' || **format == '.'
		|| **format == '*' || **format == '\''
		|| (**format >= '0' && **format <= '9'))
	{
		if (**format == '.')
		{
			arg->precision = 0;
			if (*++(*format) == '*')
				arg->precision = va_arg(ap, int);
			else
				arg->precision = ft_sizeval(format);
		}	
		else if (**format >= '1' && **format <= '9')
			arg->minfield = ft_sizeval(format);
		else if (**format == '*')
			arg->minfield = va_arg(ap, int);
		else
			ft_flags(format, arg);
		++*format;
	}
	if (arg->minfield < 0)
		arg->flag_min = 1;
	if (arg->minfield < 0)
		arg->minfield = -arg->minfield;
}

void	ft_decode(va_list ap, t_arg *arg, const char **format, int *counter)
{	
	arg->precision = -1;
	ft_scan_format(ap, format, arg);
	while (**format == 'l' || **format == 'h')
	{
		arg->ll_type = 0;
		arg->l_type = *(*format)++;
		if (**format == arg->l_type)
			arg->ll_type = *(*format)++;
		else
		{
			if (**format == 'l')
				arg->l_type = 'l';
			while (**format == 'l' || **format == 'h')
				++*format;
		}
	}
	if (**format)
	{
		arg->type = ft_get_type(format, arg, counter);
		ft_dispatch(ap, arg, counter);
		if (*counter >= 0)
			(*counter) += arg->len;
		ft_pad_right(arg, counter);
	}
}
