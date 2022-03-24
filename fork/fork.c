/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "struct.h"
#include "parsing.h"
#include "fork.h"
#include "builtin.h"

int	compare(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	return (1);
}

static int	builtin(t_parser *cmd, t_msh **msh)
{
	int	ret;

	ret = -1;
	if (compare(cmd->cmd->s, "pwd\0") == 0)
		ret = ft_pwd(cmd, msh);
	else if (compare(cmd->cmd->s, "env\0") == 0)
		ret = ft_exc_env(cmd, msh);
	else if (compare(cmd->cmd->s, "cd\0") == 0)
		ret = ft_exc_cd(cmd, msh);
	else if (compare(cmd->cmd->s, "echo\0") == 0)
		ret = ft_exc_echo(cmd, msh);
	return (ret);
}

void	search_cmd(t_msh **msh)
{
	int			i;
	int			j;
	t_parser	*cpy;

	i = 0;
	init_msh(msh);
	cpy = (*msh)->pars;
	while (i < (*msh)->size)
	{
		manage_pipefd(msh, &i, 0);
		if (builtin(cpy, msh) == -1)
		{
			(*msh)->path = get_path(msh);
			(*msh)->cmd = get_env(cpy->cmd);
			j = test_access(msh, (*msh)->cmd);
			if (j > 0)
				cmd_fork(msh, cpy, j);
			else
			{
				print_error(ERR_CMD);
				break ;
			}
			free_tab((*msh)->cmd);
			free_tab((*msh)->path);
		}
		manage_pipefd(msh, &i, 1);
		cpy = cpy->next;
	}
	free_wait_pid(msh);
}
