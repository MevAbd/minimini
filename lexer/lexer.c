/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"

t_lexer	*new_lexer(char *s, t_type type)
{
	t_lexer	*lexer;

	if (s == NULL && get_error() != SUCCESS)
		return (NULL);
	lexer = ft_calloc(1, sizeof(t_lexer));
	if (lexer == NULL)
		return (NULL);
	lexer->s = ft_strdup(s);
	if (lexer->s == NULL)
	{
		free(lexer);
		return (NULL);
	}
	lexer->type = type;
	lexer->next = NULL;
	return (lexer);
}

void	addback_lexer(t_lexer **alst, t_lexer *add)
{
	t_lexer	*cpy;

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

void	free_lexer(t_lexer **lexer)
{
	t_lexer	*cpy;

	cpy = (*lexer);
	while (cpy)
	{
		cpy = cpy->next;
		free((*lexer)->s);
		free(*lexer);
		(*lexer) = cpy;
	}
	(*lexer) = NULL;
}

int	cutline_word(const char *str, int i)
{
	int	j;

	j = 0;
	while (str[i + j] != '\0' && (is_pipe(str[i + j]) == 0)
		&& (is_space(str[i + j]) == 0) && (is_redir(str[i + j]) == 0))
	{
		if (is_simple_quote(str[i + j]))
			j = line_simple(str, i, j);
		else if (is_double_quote(str[i + j]))
			j = line_double(str, i, j);
		else
			j++;
	}
	return (j);
}

t_lexer	*cut_line(const char *str)
{
	int		i;
	int		j;
	t_lexer	*lexer;

	i = 0;
	lexer = NULL;
	while (str[i])
	{
		if (is_space(str[i]))
		{
			while (is_space(str[i]) && str[i] != '\0')
				i++;
		}
		else if (is_redir(str[i]))
			i = line_redir(str, i, &lexer);
		else if (is_pipe(str[i]))
			i = line_pipe(str, i, &lexer);
		else
		{
			j = cutline_word(str, i);
			i = line_word(str, i, j, &lexer);
		}
	}
	return (lexer);
}
