/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:48:20 by inazaria          #+#    #+#             */
/*   Updated: 2024/04/08 23:17:18 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"

int	ft_printf_aux(char *str, t_conversionFuncPtr *conv_table, va_list args)
{
	int		counter;
	t_args	s_args;

	counter = 0;
	s_args = (t_args){};
	s_args.rendue = 0;
	va_copy(s_args.args, args);
	while (str && str[counter])
	{
		if (str[counter] != '%')
		{
			ft_putchar(str[counter]);
			s_args.rendue++;
			counter++;
		}
		else
		{
			s_args = conv_table[(int) parse_next_arg(str + counter)](s_args);
			counter += 2;
		}
	}
	return (s_args.rendue);
}

int	ft_printf(const char *format, ...)
{
	int					rendue;
	va_list				args;
	t_conversionFuncPtr	*conv_table;

	va_start(args, format);
	conv_table = make_conversion_table();
	rendue = ft_printf_aux((char *) format, conv_table, args);
	va_end(args);
	return (rendue);
}
