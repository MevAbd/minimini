/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"

int	is_simple_quote(char c)
{
	if (c == 39)
		return (1);
	return (0);
}

int	is_double_quote(char c)
{
	if (c == 34)
		return (1);
	return (0);
}

int	line_simple(const char *s, int i, int j)
{
	if (is_simple_quote(s[i + j]))
		j++;
	while (s[i + j] && s[i + j] != 39)
		j++;
	if (is_simple_quote(s[i + j]))
		j++;
	return (j);
}

int	line_double(const char *s, int i, int j)
{
	if (is_double_quote(s[i + j]))
		j++;
	while (s[i + j] && s[i + j] != 34)
		j++;
	if (is_double_quote(s[i + j]))
		j++;
	return (j);
}

int	line_word(const char *s, int i, int j, t_lexer **lexer)
{
	int		c;
	char	*ret;

	ret = ft_calloc((j + 1), sizeof(char));
	if (ret == NULL)
		return (0);
	c = 0;
	while (c < j)
	{
		ret[c] = s[i + c];
		c++;
	}
	addback_lexer(lexer, new_lexer(ret, WORD));
	free(ret);
	return (i + j);
}
