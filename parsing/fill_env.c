/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parsing.h"

void	free_env(t_cmd **env)
{
	t_cmd	*cpy;

	cpy = (*env);
	while (cpy)
	{
		cpy = cpy->next;
		free((*env)->s);
		free(*env);
		(*env) = cpy;
	}
	(*env) = NULL;
}

static t_cmd	*new_env(char *s)
{
	t_cmd	*env;

	if (s == NULL && get_error() != SUCCESS)
		return (NULL);
	env = ft_calloc(1, sizeof(t_cmd));
	if (env == NULL)
		return (NULL);
	env->s = ft_strdup(s);
	if (env->s == NULL)
	{
		free(env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}

t_cmd	*fill_env(char **envp)
{
	int		i;
	t_cmd	*env;

	i = 0;
	env = NULL;
	while (envp[i] != NULL)
	{
		addback_cmd(&env, new_env(envp[i]));
		i++;
	}
	return (env);
}
