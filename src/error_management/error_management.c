/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:24:49 by inazaria          #+#    #+#             */
/*   Updated: 2024/09/17 02:12:45 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_correct_pipex_usage(void)
{
	ft_printf("Invalid use of pipex\n");
	ft_printf("Usage: ");
	printf_clr(YELLOW_TXT, "./pipex infile cmd1 cmd2 [...] outfile\n");
}

void	ft_error(char *text)
{
	write(2, text, ft_strlen(text));
}

void	custom_name_error(char *file, char *text)
{
	ft_error(file);
	ft_error(": ");
	ft_error(RED_TXT);
	ft_error(text);
	ft_error(END_TXT);
}

void	custom_name_perror(char *file)
{
	ft_error(file);
	ft_error(": ");
	ft_error(RED_TXT);
	perror("");
	ft_error(END_TXT);
}
