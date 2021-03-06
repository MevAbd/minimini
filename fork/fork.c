/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/04 15:37:44 by malbrand         ###   ########.fr       */
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
	else if (compare(cmd->cmd->s, "cd\0") == 0 && cmd->next == NULL)
		ret = ft_exc_cd(cmd, msh);
	else if (compare(cmd->cmd->s, "echo\0") == 0)
		ret = ft_exc_echo(cmd, msh, 1);
	else if (compare(cmd->cmd->s, "export\0") == 0)
		ret = ft_exc_export(cmd, msh);
	else if (compare(cmd->cmd->s, "unset\0") == 0)
		ret = ft_exc_unset(cmd, msh);
	else if (compare(cmd->cmd->s, "exit\0") == 0)
		ret = ft_exc_exit(cmd, msh);
	return (ret);
}

static void	free_tabtab(t_msh **msh, int verif)
{
	if (verif == 0)
		print_error(ERR_CMD);
	free_tab((*msh)->cmd);
	free_tab((*msh)->path);
}

static int	manage_exe(t_msh **msh, int *i, t_parser **cpy)
{
	int	built;
	int	j;

	manage_pipefd(msh, i, 0);
	redir((*cpy), msh);
	built = builtin((*cpy), msh);
	if (built == 138)
		exit (EXIT_SUCCESS);
	else if (built == -1)
	{
		(*msh)->path = get_path(msh);
		if ((*msh)->path == NULL)
			return (-1);
		(*msh)->cmd = get_env((*cpy)->cmd);
		j = test_access(msh, (*msh)->cmd);
		if (j > 0)
			cmd_fork(msh, (*cpy), j);
		else
		{
			free_tabtab(msh, 0);
			return (-1);
		}
		free_tabtab(msh, 1);
	}	
	return (0);
}

void	search_cmd(t_msh **msh)
{
	int			i;
	t_parser	*cpy;

	i = 0;
	init_msh(msh);
	cpy = (*msh)->pars;
	while (i < (*msh)->size)
	{
		if (manage_exe(msh, &i, &cpy) == -1)
			break ;
		manage_pipefd(msh, &i, 1);
		cpy = cpy->next;
	}
	remove_herdoc(msh);
	free_wait_pid(msh);
}
