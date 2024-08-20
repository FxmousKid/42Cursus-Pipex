/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:24:49 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/20 19:05:27 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_exited_with_code(int code)
{
	printf_clr("bold", "Exited with code : ");
	if (code == 0)
		printf_clr("green", "%d\n", code);
	else
		printf_clr("red", "%d\n", code);
	printf_clr("reset", "");
}
