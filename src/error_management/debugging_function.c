/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debugging_function.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 22:22:11 by inazaria          #+#    #+#             */
/*   Updated: 2024/08/20 23:02:46 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* Function used to debug errors flow, will only trigger when building 
 * project with 'make debug'*/
#ifdef DEBUG

void	debug(char *str)
{
	printf_clr(RED_TXT, "%s", str);
	printf_clr(END_TXT, "");
}

#else

void	debug(char *str)
{
	(void) str;
}
#endif
