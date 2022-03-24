/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 16:29:56 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/24 00:22:55 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parsing.h"
#include "lexer.h"
#include "fork.h"

static char	*ft_search_name(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '=')
	{
		ret = (char *)malloc(sizeof(char) * (i + 2));
		if (!ret)
			return (NULL);
		while (j <= i)
		{
			ret[j] = str[j];
			j++;
		}
		ret[j] = '\0';
		return (ret);
	}
	return (NULL);
}

static int	ft_cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i] && s1[i])
	{
		if (s2[i] == s1[i])
			i++;
		else
			return (-1);
	}
	return (0);
}

static void	ft_export(t_parser *parser, t_msh **msh)
{
	char	*name;
	t_cmd	*cpy;
	t_cmd	*cpy_env;

	cpy = parser->cmd;
	cpy_env = (*msh)->env;
	while (cpy)
	{
		name = ft_search_name(cpy->s);
		if (name)
		{
			while (cpy_env && ft_cmp(name, cpy_env->s))
				cpy_env = cpy_env->next;
			if (cpy_env && cpy_env->s)
			{
				free(cpy_env->s);
				cpy_env->s = ft_strdup(cpy->s);
			}
			else
				addback_cmd((&(*msh)->env), new_cmd(new_lexer(name, WORD)));
			free(name);
		}
		cpy = cpy->next;
		cpy_env = (*msh)->env;
	}
}

int	ft_exc_export(t_parser *pars, t_msh **msh)
{
	t_cmd	*cpy;
	t_cmd	*cpy_env;

	cpy = pars->cmd;
	cpy_env = (*msh)->env;
	if (cpy->next == NULL)
	{
		while (cpy_env)
		{
			write((*msh)->fd_out, cpy_env->s, ft_strlen(cpy_env->s));
			write((*msh)->fd_out, "\n", 1);
			cpy_env = cpy_env->next;
		}
		return (0);
	}
	else
		ft_export(pars, msh);
	free_tab((*msh)->tab_env);
	(*msh)->tab_env = get_env((*msh)->env);
	return (0);
}
