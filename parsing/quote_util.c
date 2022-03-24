/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_util.c                                       :+:      :+:    :+:   */
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

char	*add_str(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*ret;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	ret = ft_calloc(len, sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

char	*remove_quote(const char *str, int *i, int j, t_cmd *env)
{
	char	*first;
	char	*second;
	char	*end;
	char	*ret;

	first = strdup_len(str, 0, (*i));
	if (is_double_quote(str[(*i)]))
		(*i)++;
	j = 0;
	while (!(is_double_quote(str[(*i) + j])) && str[(*i) + j])
		j++;
	second = strdup_len(str, (*i), j);
	if (is_double_quote(str[(*i) + j]))
		j++;
	end = strdup_len(str, ((*i) + j), ft_strlen(&str[(*i) + j]));
	second = replace_dol(second, env);
	ret = add_str(first, second);
	(*i) = ft_strlen(ret);
	free(first);
	free(second);
	second = add_str(ret, end);
	free(end);
	free(ret);
	return (second);
}

void	test_quote(int i, int j, char *s)
{
	while (j < i)
	{
		if (s[i] == 34 || s[i] == 39)
		{
			print_error(ERR_SYNT);
			return ;
		}
		j++;
	}
}
