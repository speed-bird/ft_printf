/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_ws_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:40 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 17:41:06 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_len_wc(wchar_t wc)
{
	int	width;

	width = 0;
	if (wc <= 127)
		width = 1;
	else if (wc <= 2047)
		width = 2;
	else if (wc <= 65535)
		width = 3;
	else if (wc <= 1114111)
		width = 4;
	return (width);
}

static int	ft_len_ws(wchar_t *ws, t_arg *arg)
{
	int	len;

	len = 0;
	while (*ws && (arg->precision == -1
			|| len + ft_len_wc(*ws) <= arg->precision))
	{
		if (*ws <= 127)
			len++;
		else if (*ws <= 2047)
			len += 2;
		else if (*ws <= 65535)
			len += 3;
		else if (*ws <= 1114111)
			len += 4;
		ws++;
	}
	return (len);
}

void	ft_type_ws(wchar_t *ws, t_arg *arg, int *counter)
{
	char	*str;
	int		b_written;
	int		wc_width;

	arg->len = ft_len_ws(ws, arg);
	ft_pad_left(arg, counter);
	b_written = 0;
	while (*ws && (arg->precision == -1
			|| b_written + ft_len_wc(*ws) <= arg->precision))
	{
		wc_width = ft_len_wc(*ws);
		if (*ws <= 127)
			str = (char []){*ws};
		else if (*ws <= 2047)
			str = (char []){*ws >> 6 | 192, (*ws & 63) | 128};
		else if (*ws <= 65535)
			str = (char []){*ws >> 12 | 224, (*ws >> 6 & 63)
				| 128, (*ws & 63) | 128};
		else if (*ws <= 1114111)
			str = (char []){*ws >> 18 | 240, (*ws >> 12 & 63)
				| 128, (*ws >> 6 & 63) | 128, (*ws & 63) | 128};
		write(1, str, wc_width);
		b_written += wc_width;
		ws++;
	}
}
