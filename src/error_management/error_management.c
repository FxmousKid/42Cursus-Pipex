/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:24:49 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/22 23:32:36 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_code_and_exit(int code)
{
	ft_printf("\n");
	printf_clr(BOLD_TXT, "Exited with code : ");
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

void	stderr_file_error(char *file, char *text)
{
	write(2, file, ft_strlen(file));
	write(2, ": ", 2);
	write(2, RED_TXT, 7);
	write(2, text, ft_strlen(text));
	write(2, END_TXT, 4);	
}
