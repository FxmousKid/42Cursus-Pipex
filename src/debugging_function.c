
/************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 18:34:32 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/20 18:55:30 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function used to debug errors flow, will only trigger when building 
 * project with 'make debug'*/
#ifdef DEBUG

void	ft_debug(char *str)
{
	printf_clr("red", "%s", str);
	printf_clr("reset", "");
}

#else

void	debug(char *str)
{
	(void) str;
}
#endif
