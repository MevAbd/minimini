/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
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

static void	type_redir(t_redir **redir)
{
	if (ft_strlen((*redir)->s) == 1)
	{
		if ((*redir)->s[0] == '>')
			(*redir)->rafter = R;
		else if ((*redir)->s[0] == '<')
			(*redir)->rafter = L;
	}
	else if (ft_strlen((*redir)->s) == 2)
	{
		if ((*redir)->s[0] == '>' && (*redir)->s[1] == '>')
			(*redir)->rafter = RR;
		else if ((*redir)->s[0] == '<' && (*redir)->s[1] == '<')
			(*redir)->rafter = L;
	}
}

t_redir	*new_redir(t_lexer *lexer)
{
	t_redir	*redir;

	if (lexer == NULL && get_error() != SUCCESS)
		return (NULL);
	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->s = ft_strdup(lexer->s);
	if (redir->s == NULL)
	{
		free(redir);
		return (NULL);
	}
	type_redir(&redir);
	if (ft_strlen(redir->s) > 2)
	{
		print_error(ERR_SYNT);
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

t_redir	*newredirword(t_lexer *lexer)
{
	t_redir	*redir;

	if (lexer == NULL && get_error() != SUCCESS)
		return (NULL);
	redir = ft_calloc(1, sizeof(t_redir));
	if (redir == NULL)
		return (NULL);
	redir->s = ft_strdup(lexer->s);
	redir->rafter = W;
	if (redir->s == NULL)
	{
		free(redir);
		return (NULL);
	}
	redir->next = NULL;
	return (redir);
}

void	addback_redir(t_redir **alst, t_redir *add)
{
	t_redir	*cpy;

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

void	free_redir(t_redir **redir)
{
	t_redir	*cpy;

	cpy = (*redir);
	while (cpy)
	{
		cpy = cpy->next;
		free((*redir)->s);
		free(*redir);
		(*redir) = cpy;
	}
	(*redir) = NULL;
}
