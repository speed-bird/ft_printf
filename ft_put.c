/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:02 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/04 17:11:34 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_put_lu_b(long unsigned nbr, t_arg *arg)
{
	int				val;
	char			*base;
	long unsigned	base_length;

	base = "0123456789abcdef";
	if (arg->type == 'X')
		base = "0123456789ABCDEF";
	else if (arg->type == 'u' || arg->type == 'f'
		|| arg->type == 'e' || arg->type == 'g')
		base = "0123456789";
	base_length = ft_len_s(base);
	if (nbr >= base_length)
		ft_put_lu_b(nbr / base_length, arg);
	val = nbr % base_length;
	write(1, &base[val], 1);
}

void	ft_put_s(char *s, t_arg *arg)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	else if (arg->type == 's' && arg->precision >= 0)
		while (*s && i++ < arg->precision)
			write(1, s++, 1);
	else
		write(1, s, ft_len_s(s));
}
