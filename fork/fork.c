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

//int	fd_heredoc

//write((*msh)->fd_out, ...);

//int	signal_heredoc(int sig)
//{
//	write(1, "\n", 1);
//	close(1);
//}
//
//int	heredoc(const char *delimiter)
//{
//	char	*s;
//	int		pipefd[2];
//	int		len;
//	int		fd_in;
//
//	fd_in = dup(STDIN_FILENO);
//	pipe(pipefd);
//	signal(SIGINT, signal_heredoc);
//	s = readline(">");
//	len = ft_strlen(s);
//	while (s != NULL && ft_strncmp(s, delimiter, len) != 0)
//	{
//		write(pipefd[1], s, len);
//		free(s);
//		s = readline(">");
//		len = ft_strlen(s);
//	}
//	dup2(fd_in, STDIN_FILENO);
//	close(fd_in);
//	close(pipefd[1]);
//	return (pipefd[0]);
//}

static void	cmd_fork(t_msh **msh, t_parser *cpy, int j, int pipefd, char **env)
{
//	int	pipefd[2];
//	char	**env;
//
//	env = get_env((*msh)->env);
//	free_cmd(&(*msh)->env);
//	if ( i < (*msh)->size -1)
//	{
//		pipe(pipefd);
//		(*msh)->fd_out = pipefd[1];
//	}
//	else
//	{
//		pipefd[0] = 0;
//		pipefd[1] = 1;
//	}
//	redir
//	if (!builtin)
//	{
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
			if (pipefd != 0)
				close(pipefd);
			execve((*msh)->path[j], (*msh)->cmd, env);
			exit(1);
		}
//	}
//	if ((*msh)->fd_in != 0)
//		close((*msh)->fd_in);
//	(*msh)->fd_in = pipefd[0];
//	if ((*msh)->fd_out != 1)
//	{
//		close((*msh)->fd_out);
//		(*msh)->fd_out = 1;
//	}
//	(*msh)->env = fill_env(env);
//	free_tab(env);
}

static int	test_access(t_msh **msh, char **cmd)
{
	int	j;

	j = 0;
	while ((*msh)->path[j])
	{
		(*msh)->path[j] = ft_add_cmd((*msh)->path[j], cmd[0]);
		if ((!(access((*msh)->path[j], R_OK))) && (!(access((*msh)->path[j], X_OK))))
			return (j);
		j++;
	}
	return (-1);
}

void	search_cmd(t_msh **msh)
{
	int	pipefd[2];
	char	**env;
	int		i;
	int		j;
	t_parser	*cpy;
	t_parser	*bis;


	i = 0;
	cpy = (*msh)->pars;
	(*msh)->size = nb_cmd(cpy);
	(*msh)->fd_in = STDIN_FILENO;
	(*msh)->fd_out = STDOUT_FILENO;
	env = get_env((*msh)->env);
	while (i < (*msh)->size)
	{
		if ( i < (*msh)->size - 1)
		{
			pipe(pipefd);
			(*msh)->fd_out = pipefd[1];
		}
		else
		{
			pipefd[0] = 0;
			pipefd[1] = 1;
		}
//		expand_var
//		expand_quote
//		if (!builtin(cpy, msh))
//		{
			(*msh)->path = get_path(msh);
			(*msh)->cmd = get_env(cpy->cmd);
			j = test_access(msh, (*msh)->cmd);
			if (j > 0)
				cmd_fork(msh, cpy, j, pipefd[0], env);
			else
			{
				print_error(ERR_CMD);
				break ;
			}
//		}
		if ((*msh)->fd_in != 0)
			close((*msh)->fd_in);
		(*msh)->fd_in = pipefd[0];
		if ((*msh)->fd_out != 1)
		{
			close((*msh)->fd_out);
			(*msh)->fd_out = 1;
		}
		i++;
		cpy = cpy->next;
		free_tab((*msh)->cmd);
		if ((*msh)->path != NULL)
			free_tab((*msh)->path);
	}
	free_cmd(&(*msh)->env);
	(*msh)->env = fill_env(env);
	free_tab(env);
	i = 0;
	cpy = (*msh)->pars;
	while (i < (*msh)->size)
	{
		waitpid(cpy->pid, 0, 0);
		cpy = cpy->next;
		i++;
	}
}
