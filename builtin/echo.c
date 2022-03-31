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

static void	check_new_line(t_cmd **cmd, int *new_line)
{
	int	i;
	int	verif;

	verif = 0;
	while (*cmd)
	{
		i = 0;
		if ((*cmd)->s[i] == '-')
			i++;
		if (verif == 0 && i == 0)
			return ;
		verif++;
		while ((*cmd)->s[i])
		{
			if ((*cmd)->s[i] != 'n')
				return ;
			i++;
		}
		*new_line = 0;
		(*cmd) = (*cmd)->next;
	}
}

int	ft_exc_echo(t_parser *pars, t_msh **msh, int new_line)
{
	t_cmd	*cpy;

	cpy = pars->cmd;
	if (cpy->next == NULL)
	{
		write((*msh)->fd_out, "\n", 1);
		return (0);
	}
	cpy = cpy->next;
	check_new_line(&cpy, &new_line);
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
