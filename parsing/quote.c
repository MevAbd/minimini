/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
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

int		is_space(char c )
{
	return (c == ' ' || c == '\f' || c == '\t' || c == '\n' || c == '\r' || c == '\v');
}

char	**quote_spliter(char *s)
{
	
}

void	quote_manager(t_lexer *lexer, t_cmd *env)
{
	char **ss;

	ss = quote_spliter(lexer->s);
}

void	word_checker(t_lexer **lexer, t_cmd *env)
{
	t_lexer	*cpy;

	cpy = (*lexer);
	while (cpy)
	{
		if (cpy->type == WORD)
			quote_manager(cpy, env);
		if (get_error() != SUCCESS)
			break ;
		cpy = cpy->next;
	}
}


/*
check + decoupage string

sans cote :
- check erreur if `'` | `"`                            '
- $ 
	-> env empty delete maillon
	-> replace by content 
	-> si espace (tout type)transformer en autant de maillon de type WORD

double cote:
- retirer les double cote
- si $ voir sans cote

simple cote :
- retirer les cote
*/