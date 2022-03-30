/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"
#include "fork.h"
#include "parsing.h"

static void	cut_cmd(t_lexer **lexer, t_parser **parser)
{
	t_lexer		*cpy;
	t_parser	*parser_cpy;

	parser_cpy = (*parser);
	cpy = (*lexer);
	while (cpy)
	{	
		if (cpy->type == WORD)
			addback_cmd(&parser_cpy->cmd, new_cmd(cpy));
		else if (cpy->type == REDIR)
			parsing_redir(&parser_cpy, &cpy);
		else if (cpy->type == PIPE)
			parsing_pipe(&parser_cpy, &cpy);
		if (get_error() != SUCCESS)
			break ;
		cpy = cpy->next;
	}
	free_lexer(&(*lexer));
}

void	parsing(const char *s, t_msh **msh)
{
	t_lexer		*lexer;

	lexer = cut_line(s);
	if (lexer == NULL && get_error() != SUCCESS)
		return ;
	(*msh)->pars = ft_calloc(1, sizeof(t_parser));
	if ((*msh)->pars == NULL)
		return ;
	if (get_error() == SUCCESS)
	{	
		word_checker(&lexer, (*msh)->env);
		if (get_error() == SUCCESS)
		{	
			cut_cmd(&lexer, (&(*msh)->pars));
			if (get_error() == SUCCESS)
				search_cmd(msh);
		}
	}
	free_lexer(&lexer);
}
