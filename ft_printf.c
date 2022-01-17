/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:08:41 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 17:46:05 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_fill_s(t_arg *arg, const char **format, int *counter)
{
	--*format;
	if (!arg->s)
		arg->s = *format;
	arg->s_len++;
	++*counter;
	++*format;
}

int	ft_printf(const char *format, ...)
{
	t_arg	arg;
	va_list	ap;
	int		counter;

	arg = (t_arg){};
	counter = 0;
	va_start(ap, format);
	while (*format && counter >= 0)
	{
		if (*format++ == '%')
		{
			if (*format)
				ft_decode(ap, &arg, &format, &counter);
			if (counter >= 0)
				arg = (t_arg){};
		}			
		else
			ft_fill_s(&arg, &format, &counter);
	}
	va_end(ap);
	if (arg.s && counter >= 0)
		write(1, arg.s, arg.s_len);
	return (counter);
}
