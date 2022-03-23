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

static int	builtin(t_parser *cmd, t_msh **msh)
{
	if (ft_strncmp(cmd->cmd->s, "pwd\0", ft_strlen("pwd\0")) == 0)
	{
		ft_pwd(cmd, msh);
		return (1);
	}
	return (0);
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
		if (builtin(cpy, msh) == 0)
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
		}
		manage_pipefd(msh, &i, 1);
		cpy = cpy->next;
		free_tab((*msh)->cmd);
		if ((*msh)->path != NULL)
			free_tab((*msh)->path);
	}
	free_wait_pid(msh);
}
