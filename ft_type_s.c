/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:33 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/17 15:11:28 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_type_s(wchar_t *ws, t_arg *arg, int *counter)
{
	char	*s;

	write(1, arg->s, arg->s_len);
	if (!arg->l_type || !ws)
	{
		if (!ws)
			s = "(null)";
		else
			s = (char *)ws;
		arg->len = ft_len_s(s);
		if (arg->precision >= 0 && arg->precision < arg->len)
			arg->len = arg->precision;
		ft_pad_left(arg, counter);
		ft_put_s(s, arg);
	}
	else
		ft_type_ws(ws, arg, counter);
}
