/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:30 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 17:34:13 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_type_p(long unsigned nbr, t_arg *arg, int *counter)
{
	write(1, arg->s, arg->s_len);
	if (nbr || arg->precision)
		arg->len = ft_len_hex(nbr);
	arg->prefix = 1;
	ft_pad_left(arg, counter);
	if (nbr || arg->precision)
		ft_put_lu_b(nbr, arg);
}
