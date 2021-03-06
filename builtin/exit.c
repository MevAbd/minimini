/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 05:53:39 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/05 12:19:55 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parsing.h"
#include "lexer.h"
#include "fork.h"

static void	ft_exit(t_msh **msh)
{
	write((*msh)->fd_out, "exit\n", 5);
	free_cmd(&(*msh)->env);
	free_parser(&(*msh)->pars);
	if ((*msh)->cmd)
		free_tab((*msh)->cmd);
	free_tab((*msh)->tab_env);
	free(*msh);
}

int	ft_exc_exit(t_parser *pars, t_msh **msh)
{
	t_cmd	*cpy;

	cpy = pars->cmd;
	if (cpy && cpy->next)
	{
		write((*msh)->fd_out, "exit\n", 5);
		write((*msh)->fd_out, cpy->s, ft_strlen(cpy->s));
		write((*msh)->fd_out, ": numeric argument required\n", 28);
		free_cmd(&(*msh)->env);
		free_parser(&(*msh)->pars);
		if ((*msh)->path)
			free_tab((*msh)->path);
		if ((*msh)->cmd)
			free_tab((*msh)->cmd);
		free_tab((*msh)->tab_env);
		free(*msh);
	}
	else
		ft_exit(msh);
	return (138);
}
