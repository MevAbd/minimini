/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      redir_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "struct.h"
#include "parsing.h"
#include "fork.h"
#include "builtin.h"

static int	redir_out(t_redir *cpy, t_msh **msh)
{
	if (cpy->rafter == R)
	{
		cpy = cpy->next;
		if ((*msh)->fd_out != 1)
			close((*msh)->fd_out);
		(*msh)->fd_out = open(cpy->s, O_CREAT | O_TRUNC | O_WRONLY, 0664);
		cpy = cpy->next;
		return (1);
	}
	else if (cpy->rafter == RR)
	{
		cpy = cpy->next;
		if ((*msh)->fd_out != 1)
			close((*msh)->fd_out);
		(*msh)->fd_out = open(cpy->s, O_CREAT | O_APPEND | O_WRONLY, 0664);
		cpy = cpy->next;
		return (1);
	}
	return (0);
}

void	redir(t_parser *pars, t_msh **msh)
{
	t_redir	*cpy;

	cpy = pars->redir;
	if (!cpy)
		return ;
	while (cpy)
	{
		if (redir_out(cpy, msh) == 1)
		{
			cpy = cpy->next;
			cpy = cpy->next;
		}
		else if (cpy->rafter == L)
		{
			cpy = cpy->next;
			if ((*msh)->fd_in != 0)
				close((*msh)->fd_in);
			(*msh)->fd_in = open(cpy->s, O_RDONLY);
			cpy = cpy->next;
		}
	}
}
