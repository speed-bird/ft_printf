/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type_n_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:09:26 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 13:18:45 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_type_n(int *nbr, t_arg *arg, int *counter)
{
	write(1, arg->s, arg->s_len);
	if (!nbr)
		return ;
	else if (arg->l_type == 'l' && !arg->ll_type)
		*(long int *)nbr = *counter;
	else if (arg->l_type == 'l' && arg->ll_type == 'l')
		*(long long int *)nbr = *counter;
	else if (arg->l_type == 'h' && !arg->ll_type)
		*(short *)nbr = *counter;
	else if (arg->l_type == 'h' && arg->ll_type == 'h')
		*(char *)nbr = *counter;
	else
		*nbr = *counter;
}
