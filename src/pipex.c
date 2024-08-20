/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:22:35 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/20 23:32:38 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*make_t_pipex(char *argv[])
{
	t_pipex	*data;
	(void) argv;

	data = (t_pipex *) ft_calloc(sizeof(t_pipex), 1);
	if (!data)
		return (ft_error("Failed to Allocate memory !\n"), NULL);
	
	
	return (data);
}

int	pipex(char *argv[])
{
	t_pipex	*data;

	data = make_t_pipex(argv);
	if (!data)
		return (debug(DBG("Failed to make_t_pipex()")), 0);

	return (1);
}

int	main(int argc, char *argv[])
{
	if (argc != 5)
	{
		// Add invalid_arg_handler();
		printf_clr(RED_TXT, "Invalid arg count !\n");
		print_code_and_exit(1);
	}
	if (!pipex(argv))
	{
		// Add error_handler();
		debug(DBG("Failed to run pipex() call"));
		print_code_and_exit(1);
	}
	print_code_and_exit(0);

}
