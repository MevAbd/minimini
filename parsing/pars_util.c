/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_util.c                                        :+:      :+:    :+:   */
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

void	free_parser(t_parser **parser)
{
	t_parser	*cpy;

	cpy = (*parser);
	while (cpy)
	{
		cpy = (*parser)->next;
		free_redir(&(*parser)->redir);
		free_cmd(&(*parser)->cmd);
		free(*parser);
		(*parser) = cpy;
	}
	(*parser) = NULL;
}

t_parser	*new_pars(void)
{
	t_parser	*pars;

	pars = ft_calloc(1, sizeof(t_parser));
	if (pars == NULL)
		return (NULL);
	pars->next = NULL;
	return (pars);
}

void	addback_pars(t_parser **alst, t_parser *add)
{
	t_parser	*cpy;

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

void	parsing_redir(t_parser **parser_cpy, t_lexer **cpy)
{
	addback_redir(&(*parser_cpy)->redir, new_redir(*cpy));
	(*cpy) = (*cpy)->next;
	if ((*cpy) == NULL || (*cpy)->type != WORD)
	{
		print_error(ERR_SYNT);
		return ;
	}
	addback_redir(&(*parser_cpy)->redir, newredirword(*cpy));
}

void	parsing_pipe(t_parser **parser_cpy, t_lexer **cpy)
{
	t_lexer	*test;

	addback_pars(&(*parser_cpy), new_pars());
	(*parser_cpy) = (*parser_cpy)->next;
	test = (*cpy);
	(*cpy) = (*cpy)->next;
	if ((*cpy) == NULL || (*cpy)->type == PIPE)
	{
		print_error(ERR_SYNT);
		return ;
	}
	(*cpy) = test;
}
