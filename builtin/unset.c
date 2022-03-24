/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                           :+:      :+:    :+:   */
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

static int	search_var(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '=')
			return (-1);
		i++;
	}
	return (0);
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

static void	ft_unset(char *s, t_msh **msh)
{
	int	i;

	i = 0;
	while ((*msh)->tab_env[i])
	{
		if (ft_cmp(s, (*msh)->tab_env[i]) == 0)
		{
			while ((*msh)->tab_env[i + 1])
			{
				free((*msh)->tab_env[i]);
				(*msh)->tab_env[i] = ft_strdup((*msh)->tab_env[i + 1]);
				i++;
			}
			free((*msh)->tab_env[i]);
			(*msh)->tab_env[i] = NULL;
		}
		else i++;
	}
	free_cmd(&(*msh)->env);
	(*msh)->env = fill_env((*msh)->tab_env);
}

int	ft_exc_unset(t_parser *pars, t_msh **msh)
{
	t_cmd	*cpy;
	t_cmd	*add;
	char	*var;

	cpy = pars->cmd;
	cpy = cpy->next;
	if (cpy == NULL)
		return (0);
	while (cpy)
	{
		if (search_var(cpy->s) == 0)
		{
			ft_unset(cpy->s, msh);
			cpy = cpy->next;
		}
		else
			return (1);
	}
	return (0);
}
