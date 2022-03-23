/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"
#include "parsing.h"

t_cmd	*new_cmd(t_lexer *lexer)
{
	t_cmd	*cmd;

	if (lexer == NULL && get_error() != SUCCESS)
		return (NULL);
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (cmd == NULL)
		return (NULL);
	cmd->s = ft_strdup(lexer->s);
	if (cmd->s == NULL)
	{
		free(cmd);
		return (NULL);
	}
	cmd->next = NULL;
	return (cmd);
}

void	addback_cmd(t_cmd **alst, t_cmd *add)
{
	t_cmd	*cpy;

	cpy = (*alst);
	if (cpy)
	{
		while (cpy->next)
			cpy = cpy->next;
		cpy->next = add;
	}
	else
		(*alst) = add;
}

void	free_cmd(t_cmd **cmd)
{
	t_cmd	*cpy;

	cpy = (*cmd);
	while (cpy)
	{
		cpy = cpy->next;
		free((*cmd)->s);
		free(*cmd);
		(*cmd) = cpy;
	}
	(*cmd) = NULL;
}
