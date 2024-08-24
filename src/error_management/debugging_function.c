/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:22:11 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/23 17:20:50 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function used to debug errors flow, will only trigger when building 
 * project with 'make debug'*/
#ifdef DEBUG

void	debug(char *str)
{
	write(2, RED_TXT, 7);
	write(2, str, ft_strlen(str));
	write(2, END_TXT, 4);
}

#else

void	debug(char *str)
{
	(void) str;
}
#endif
