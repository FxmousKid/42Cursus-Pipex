/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:22:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/20 18:30:03 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int	pipex(char *argv[])
{
	(void) argv;

	return (1);
}

int	main(int argc, char *argv[])
{
	if (argc != 5)
	{
		// Add invalid_arg_handler();
		printf_clr("red", "Invalid arg count !\n");
		return (1);
	}
	if (pipex(argv))
	{
		// Add error_handler();
		debug("Failed to pipex()\n");
		return (1);
	}

}
