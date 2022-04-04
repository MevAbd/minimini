/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/04 12:29:39 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "struct.h"
#include "parsing.h"
#include "fork.h"

void	init_msh(t_msh **msh)
{
	(*msh)->size = nb_cmd((*msh)->pars);
	(*msh)->fd_in = STDIN_FILENO;
	(*msh)->fd_out = STDOUT_FILENO;
	(*msh)->tab_env = get_env((*msh)->env);
	(*msh)->cmd = NULL;
}

void	free_wait_pid(t_msh **msh)
{
	int			i;
	t_parser	*cpy;

	i = 0;
	free_cmd(&(*msh)->env);
	(*msh)->env = fill_env((*msh)->tab_env);
	free_tab((*msh)->tab_env);
	cpy = (*msh)->pars;
	while (i < (*msh)->size)
	{
		waitpid(cpy->pid, 0, 0);
		cpy = cpy->next;
		i++;
	}
}

void	manage_pipefd(t_msh **msh, int *i, int verif)
{
	if (verif == 0)
	{
		if ((*i) < (*msh)->size - 1)
		{
			pipe((*msh)->pipefd);
			(*msh)->fd_out = (*msh)->pipefd[1];
		}
		else
		{
			(*msh)->pipefd[0] = 0;
			(*msh)->pipefd[1] = 1;
		}
	}
	else
	{
		if ((*msh)->fd_in != 0)
			close((*msh)->fd_in);
		(*msh)->fd_in = (*msh)->pipefd[0];
		if ((*msh)->fd_out != 1)
		{
			close((*msh)->fd_out);
			(*msh)->fd_out = 1;
		}
		(*i)++;
	}
}

void	cmd_fork(t_msh **msh, t_parser *cpy, int j)
{
	cpy->pid = fork();
	if (cpy->pid == 0)
	{
		if ((*msh)->fd_in != 0)
		{
			dup2((*msh)->fd_in, 0);
			close((*msh)->fd_in);
		}
		if ((*msh)->fd_out != 1)
		{
			dup2((*msh)->fd_out, 1);
			close((*msh)->fd_out);
		}
		if ((*msh)->pipefd[0] != 0)
			close((*msh)->pipefd[0]);
		execve((*msh)->path[j], (*msh)->cmd, ((*msh)->tab_env));
		exit(1);
	}
}

int	test_access(t_msh **msh, char **cmd)
{
	int	j;

	j = 0;
	while ((*msh)->path[j])
	{
		(*msh)->path[j] = ft_add_cmd((*msh)->path[j], cmd[0]);
		if ((!(access((*msh)->path[j], R_OK)))
			&& (!(access((*msh)->path[j], X_OK))))
			return (j);
		j++;
	}
	return (-1);
}
