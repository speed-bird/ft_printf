/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dispatch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:06:08 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 13:09:34 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_dispatch(va_list ap, t_arg *arg, int *counter)
{
	if (arg->type == 'd' || arg->type == 'i')
		ft_type_di(va_arg(ap, long int), arg, counter);
	else if (arg->type == 'n')
		ft_type_n(va_arg(ap, int *), arg, counter);
	else if (arg->type == 'c')
		ft_type_c(va_arg(ap, wint_t), arg, counter);
	else if (arg->type == 'e')
		ft_type_e(va_arg(ap, double), arg, counter);
	else if (arg->type == 'f')
		ft_type_f(va_arg(ap, double), arg, counter);
	else if (arg->type == 'g')
		ft_type_g(va_arg(ap, double), arg, counter);
	else if (arg->type == 'p')
		ft_type_p(va_arg(ap, long unsigned), arg, counter);
	else if (arg->type == 's')
		ft_type_s(va_arg(ap, wchar_t *), arg, counter);
	else if (arg->type == 'u' || arg->type == 'x' || arg->type == 'X')
		ft_type_ux(va_arg(ap, long unsigned), arg, counter);
}
