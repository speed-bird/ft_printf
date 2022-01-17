/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 21:08:50 by jrobert           #+#    #+#             */
/*   Updated: 2021/05/06 17:24:33 by jrobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <wchar.h>

typedef struct s_arg
{
	const char	*s;
	int			s_len;
	int			len;
	int			minfield;
	int			precision;
	int			sign;
	int			e;
	int			prefix;
	char		type;
	char		l_type;
	char		ll_type;
	int			flag_ht;
	int			flag_zero;
	int			flag_min;
	int			flag_space;
	int			flag_plus;
	int			printsize;
}				t_arg;

void	ft_decode(va_list ap, t_arg *arg, const char **format, int *counter);
void	ft_dispatch(va_list ap, t_arg *arg, int *counter);
int		ft_len_e(double nbr, t_arg *arg);
int		ft_len_lu(long unsigned n);
int		ft_len_hex(long unsigned x);
int		ft_len_s(char *s);
void	ft_pad_left(t_arg *arg, int *counter);
void	ft_pad_right(t_arg *arg, int *counter);
int		ft_printf(const char *format, ...);
void	ft_put_lu_b(long unsigned nbr, t_arg *arg);
void	ft_put_s(char *s, t_arg *arg);
void	ft_type_c(wint_t c, t_arg *arg, int *counter);
void	ft_type_di(long int nbr, t_arg *arg, int *counter);
void	ft_type_e(long double nbr, t_arg *arg, int *counter);
void	ft_type_f(long double nbr, t_arg *arg, int *counter);
void	ft_type_g(double nbr, t_arg *arg, int *counter);
void	ft_type_n(int *nbr, t_arg *arg, int *counter);
void	ft_type_p(long unsigned nbr, t_arg *arg, int *counter);
void	ft_type_s(wchar_t *ws, t_arg *arg, int *counter);
void	ft_type_ux(long unsigned nbr, t_arg *arg, int *counter);
void	ft_type_ws(wchar_t *ws, t_arg *arg, int *counter);

#endif