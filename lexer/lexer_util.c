/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"

int	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

int	line_redir(const char *s, int i, t_lexer **lexer)
{
	int		j;
	char	*ret;

	j = 0;
	while (is_redir(s[i + j]) && s[i + j] != '\0')
		j++;
	ret = strdup_len(s, i, j);
	addback_lexer(lexer, new_lexer(ret, REDIR));
	free(ret);
	return (i + j);
}

int	is_pipe(char c)
{
	if (c == '|')
		return (1);
	return (0);
}

int	line_pipe(const char *s, int i, t_lexer **lexer)
{
	int		j;
	char	*ret;

	j = 0;
	while (is_pipe(s[i + j]) && s[i + j] != '\0')
		j++;
	ret = strdup_len(s, i, j);
	addback_lexer(lexer, new_lexer(ret, PIPE));
	free(ret);
	return (i + j);
}

// int	is_space(char c)
// {
// 	if (c == ' ')
// 		return (1);
// 	return (0);
// }
