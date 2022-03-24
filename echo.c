/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 21:08:27 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/24 00:44:10 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_exc_echo(t_parser *pars, t_msh **msh)
{
	t_cmd	*cpy;
	int		new_line;

	cpy = pars->cmd;
	new_line = 1;
	if (cpy->next == NULL)
	{
		write((*msh)->fd_out, "\n", 1);
		return (0);
	}
	cpy = cpy->next;
	if (compare(cpy->s, "-n") == 0)
	{
		new_line = 0;
		cpy = cpy->next;
	}
	while (cpy)
	{
		write((*msh)->fd_out, cpy->s, ft_strlen(cpy->s));
		if (cpy->next)
				write((*msh)->fd_out, " ", 1);
		cpy = cpy->next;
	
	}
	if (new_line)
		write((*msh)->fd_out, "\n", 1);
	return (0);
}
