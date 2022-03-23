/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dol.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parsing.h"
#include "lexer.h"

static char	*search_env(char *s, t_cmd *env)
{
	int		size;
	t_cmd	*cpy;

	cpy = env;
	while (cpy)
	{
		if (ft_strncmp(s, cpy->s, ft_strlen(s) - 1))
			cpy = cpy->next;
		else
		{
			size = ft_strlen(s) + 1;
			free(s);
			s = ft_strdup(&(cpy->s[size]));
			return (s);
		}
	}
	free(s);
	s = malloc(sizeof(char));
	s[0] = '\0';
	return (s);
}

char	*replace_end(char *first, char *second, char *ret, char *end)
{
	free(first);
	free(second);
	first = add_str(ret, end);
	free(ret);
	free(end);
	return (first);
}

char	*replace(const char *s, t_cmd *env, int *i, int j)
{
	char	*first;
	char	*second;
	char	*end;
	char	*ret;
	int	size;

	j++;
	if (s[(*i) + j] == '\0')
	{
		((char *)s)[(*i) + j - 1] = '\0';
		return ((char *)s);
	}
	first = strdup_len(s, 0, ((*i) + j - 1));
	size = (*i) + j;
	j = 0;
	while (s[size + j] && s[size + j] != ' ' && s[size + j] != '$' && s[size + j] != 39 && s[size + j] != 34)
		j++;
	second = strdup_len(s, size, j);
	second = search_env(second, env);
	end = ft_strdup(&s[size + j]);
	printf("t1\n");
	ret = add_str(first, second);
	(*i) = ft_strlen(ret);
	free((char *)s);
	return (replace_end(first, second, ret, end));
}

char	*replace_dol(const char *s, t_cmd *env)
{
	int		i;
	int		j;
	char	*first;
	char	*second;
	char	*end;
	char	*ret;

	i = 0;
	while (s[i] != '\0' && s[i] != '$')
		i++;
	if (s[i] == '\0')
		return ((char *)s);
	first = strdup_len(s, 0, i);
	i++;
	j = 0;
	while (s[i + j] && s[i + j] != ' ' && s[i + j] != '\'' && s[i + j] != '"')
		j++;
	second = strdup_len(s, i, j);
	second = search_env(second, env);
	end = ft_strdup(&s[i + j]);
	ret = add_str(first, second);
	free(first);
	free(second);
	first = add_str(ret, end);
	free(ret);
	free(end);
	free((char *)s);
	return (first);
}
