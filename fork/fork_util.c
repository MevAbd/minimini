/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    fork_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parsing.h"
#include "fork.h"

int	nb_cmd(t_parser *pars)
{
	int			i;
	t_parser	*cpy;

	cpy = pars;
	i = 0;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}

char	**get_env(t_cmd *env)
{
	int		size;
	int		i;
	char	**ret;
	t_cmd	*cpy;

	cpy = env;
	size = 0;
	while (cpy)
	{
		cpy = cpy->next;
		size++;
	}
	ret = ft_calloc(size + 1, sizeof(char *));
	if (ret == NULL)
		return (NULL);
	i = 0;
	cpy = env;
	while (i < size)
	{
		ret[i] = ft_strdup(cpy->s);
		cpy = cpy->next;
		i++;
	}
	return (ret);
}

void	free_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**get_path(t_msh **msh)
{
	t_cmd	*cpy;
	char	**path;

	cpy = (*msh)->env;
	while (cpy && ft_strncmp("PATH=", cpy->s, 4) != 0)
		cpy = cpy->next;
	if (cpy->s)
	{
		if (ft_strncmp("PATH=", cpy->s, 4) == 0)
		{
			path = ft_split(&cpy->s[5], ':');
			return (path);
		}
	}
	return (NULL);
}

char	*ft_add_cmd(char *cmd, char *add)
{
	int		size;
	int		i;
	char	*ret;

	i = 0;
	size = ft_strlen(cmd) + ft_strlen(add) + 2;
	ret = (char *)malloc(sizeof(char) * size);
	if (!ret)
		return (NULL);
	while (cmd[i])
	{
		ret[i] = cmd[i];
		i++;
	}
	free(cmd);
	ret[i] = '/';
	i++;
	size = 0;
	while (add[size])
	{
		ret[i + size] = add[size];
		size++;
	}
	ret[i + size] = '\0';
	return (ret);
}
