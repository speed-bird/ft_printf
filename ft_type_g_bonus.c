/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_g_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:23 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/03 15:48:53 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_is_type_e(double nbr, t_arg *arg)
{
	int	e;

	e = 0;
	if (nbr < 0)
		nbr = -nbr;
	if (arg->precision <= -1)
		arg->precision = 6;
	if (!arg->precision)
		arg->precision = 1;
	while (nbr && nbr < 1)
	{
		nbr *= 10;
		e--;
	}
	while (nbr >= 10)
	{
		nbr /= 10;
		e++;
	}
	if (e < -4 || e >= arg->precision)
		return (1);
	else
		return (0);
}

void	ft_type_g(double nbr, t_arg *arg, int *counter)
{	
	if ((nbr == 1.0 / 0 || nbr == -1.0 / 0 || nbr != nbr)
		|| (ft_is_type_e(nbr, arg)))
		ft_type_e(nbr, arg, counter);
	else
		ft_type_f(nbr, arg, counter);
}
