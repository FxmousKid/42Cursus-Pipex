/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:24:49 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/20 23:14:24 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_code_and_exit(int code)
{
	printf_clr(BOLD_TXT, "\nExited with code : ");
	if (code == 0)
		printf_clr(GREEN_TXT, "%d\n", code);
	else
		printf_clr(RED_TXT, "%d\n", code);
	printf_clr(END_TXT, "");
	exit(code);
}

void	ft_error(char *str)
{
	printf_clr(RED_TXT, "");
	ft_putstr_fd(str, 2);
	printf_clr(END_TXT, "");
}
