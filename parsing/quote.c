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

static int	simple_manage(t_lexer **lexer, int i)
{
	int		j;
	int		size;
	char	*str;

	j = 1;
	str = (*lexer)->s;
	while (str[i + j] != '\0' && (!(is_simple_quote(str[i + j]))))
		j++;
	if (is_simple_quote(str[i + j]))
	{
		size = i + j;
		while ((i + 1) < size)
		{
			str[i] = str[i + 1];
			i++;
		}
		while (str[i + 2] != '\0')
		{
			str[i] = str[i + 2];
			i++;
		}
		str[i] = '\0';
		return (size - 1);
	}
	else
		print_error(ERR_SYNT);
	return (i);
}

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

static char	*remove_quote(const char *str, int *i, int j, t_cmd *env)
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
//	printf("first == %s\n", first);
//	printf("end == %s\n", end);
	second = replace_dol(second, env);
//	printf("second == %s\n", second);
	ret = add_str(first, second);
	(*i) = ft_strlen(ret);
	free(first);
	free(second);
	second = add_str(ret, end);
	free(end);
	free(ret);
	return (second);
}

static int	double_manage(t_lexer **lexer, int i, t_cmd *env)
{
	int		j;
	int		size;
	char	*str;
	char	*ret;

	j = 1;
	str = (*lexer)->s;
	while (str[i + j] != '\0' && (!(is_double_quote(str[i + j]))))
		j++;
	if (is_double_quote(str[i + j]))
	{
		ret = remove_quote(str, &i, j, env);
		free((*lexer)->s);
		(*lexer)->s = ft_strdup(ret);
		free(ret);
		return (i);
	}
	else
		print_error(ERR_SYNT);
	return (i);
}

static int	normal_manage(t_lexer **lexer, int i, t_cmd *env)
{
	int		j;
	t_lexer	*cpy;

	j = 0;
	cpy = (*lexer);
	while (cpy->s[i + j])
	{
		if (is_simple_quote(cpy->s[i + j]) || is_double_quote(cpy->s[i + j]))
			return (i + j);
		else if (cpy->s[i + j] == '$')
		{
			printf("end\n");
			cpy->s = replace(cpy->s, env, &i, j);
			j = 0;
		}
		else
			j++;
	}
	return (i);
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

void	quote_manage(t_lexer **lexer, t_cmd *env)
{
	int		i;
	int		j;
	int		verif;
	t_lexer	*cpy;

	cpy = (*lexer);
	while (cpy)
	{
		if (cpy->type == WORD)
		{
			i = 0;
			while (cpy->s[i] != '\0')
			{
				if (is_simple_quote(cpy->s[i]))
					i = simple_manage(&cpy, i);
				else if (is_double_quote(cpy->s[i]))
		
					i = double_manage(&cpy, i, env);
				else
				{
					j = i;
					verif = ft_strlen(cpy->s);
					i = normal_manage(&cpy, i, env);
					test_quote(i, j, cpy->s);
					if (verif == ft_strlen(cpy->s))
						break ;
				}
				if (i == ft_strlen(cpy->s) || i == ft_strlen(cpy->s) - 1)
					break ;
				if (get_error() != SUCCESS)
					break ;
			}	
		}
		if (get_error() != SUCCESS)
			break ;
		cpy = cpy->next;
	}
}
