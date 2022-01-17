/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:09 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 17:46:19 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_put_c(char *str, t_arg *arg, int *counter)
{
	if (!str)
		return ;
	write(1, arg->s, arg->s_len);
	if (arg->type == 'c')
		ft_pad_left(arg, counter);
	write(1, str, arg->len);
}

static void	ft_convert_c(wint_t c, t_arg *arg, int *counter)
{
	char	*str;

	str = NULL;
	if (!arg->l_type)
		c = (char)c;
	arg->len = 1;
	if (c <= 127)
		str = (char []){c};
	else if (c <= 2047)
	{
		str = (char []){c >> 6 | 192, (c & 63) | 128};
		arg->len = 2;
	}
	else if (c <= 65535)
	{
		str = (char []){c >> 12 | 224, (c >> 6 & 63) | 128, (c & 63) | 128};
		arg->len = 3;
	}
	else if (c <= 1114111)
	{
		str = (char []){c >> 18 | 240, (c >> 12 & 63)
			| 128, (c >> 6 & 63) | 128, (c & 63) | 128};
		arg->len = 4;
	}
	ft_put_c(str, arg, counter);
}

void	ft_type_c(wint_t c, t_arg *arg, int *counter)
{
	if (!arg->ll_type && arg->l_type == 'l' && c < 0)
		*counter = -1;
	else
		ft_convert_c(c, arg, counter);
}
