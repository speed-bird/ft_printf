/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_ux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/04 17:13:21 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 16:24:42 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_len_lu_hex(long unsigned nbr, t_arg *arg)
{
	if (arg->type == 'u')
		arg->len = ft_len_lu(nbr);
	else
		arg->len = ft_len_hex(nbr);
	if (!nbr && !arg->minfield && !arg->precision)
		arg->len--;
}

void	ft_type_ux(long unsigned nbr, t_arg *arg, int *counter)
{
	write(1, arg->s, arg->s_len);
	if (!arg->l_type)
		nbr = (unsigned int)nbr;
	else if (arg->l_type == 'h' && !arg->ll_type)
		nbr = (unsigned short)nbr;
	else if (arg->l_type == 'h' && arg->ll_type == 'h')
		nbr = (unsigned char)nbr;
	if (arg->precision >= 0)
		arg->flag_zero = 0;
	if (arg->precision < 0)
		arg->precision = 1;
	ft_len_lu_hex(nbr, arg);
	if (nbr || arg->precision || arg->minfield)
	{
		if (nbr && arg->flag_ht)
			arg->prefix = 1;
		ft_pad_left(arg, counter);
		if (!nbr && !arg->precision)
			write(1, " ", 1);
		else
			ft_put_lu_b(nbr, arg);
	}
}
