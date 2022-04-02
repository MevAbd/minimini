/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"
#include "fork.h"
#include "parsing.h"

//int	fd_heredoc

//write((*msh)->fd_out, ...);

void	signal_heredoc(int sig)
{
	write(1, "\n", 1);
	close(1);
}

int	heredoc(const char *delimiter)
{
	char	*s;
	int		pipefd[2];
	int		len;
	int		fd_in;

	fd_in = dup(STDIN_FILENO);
	pipe(pipefd);
//	signal(SIGINT, signal_heredoc);
	s = readline(">");
	len = ft_strlen(s);
	while (s != NULL && ft_strncmp(s, delimiter, len) != 0)
	{
		write(pipefd[1], s, len);
		free(s);
		s = readline(">");
		len = ft_strlen(s);
	}
	dup2(fd_in, STDIN_FILENO);
	close(fd_in);
	close(pipefd[1]);
	return (pipefd[0]);
}

void	manage_herdoc(t_msh **msh)
{
	t_parser	*cpy;
	t_redir		*red;

	cpy = (*msh)->pars;
	while (cpy != NULL)
	{
		red = cpy->redir;
		while (red != NULL)
		{
			if (red->rafter == LL)
				(*msh)->fd_in = heredoc(red->next->s);
			red = red->next;
		}
		cpy = cpy->next;
	}
}
