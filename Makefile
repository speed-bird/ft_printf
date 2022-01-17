# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jrobert <jrobert@student.s19.be>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/29 12:53:53 by jrobert           #+#    #+#              #
#    Updated: 2021/05/05 16:50:23 by jrobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= 	ft_decode.c \
				ft_dispatch.c \
				ft_len.c \
				ft_pad.c \
				ft_printf.c \
				ft_put.c \
				ft_type_c.c \
				ft_type_di.c \
				ft_type_p.c \
				ft_type_s.c \
				ft_type_ux.c \
				ft_type_e_bonus.c \
				ft_type_f_bonus.c \
				ft_type_g_bonus.c \
				ft_type_n_bonus.c \
				ft_type_ws_bonus.c

OBJS		= 	$(SRCS:%.c=%.o)

HDR			=	ft_printf.h

CFLAGS		= 	-Wall -Wextra -Werror -I $(HDR)

NAME		= 	libftprintf.a
				
$(NAME)			:	$(OBJS)
					ar rcs $(NAME) $(OBJS)

bonus			:	$(NAME) 

all    			:	bonus

clean 			:	
					rm -f $(OBJS)

fclean 			:	clean
					rm -f $(NAME) a.out
					
re				:	fclean all

.PHONY			: 	all clean fclean re
