/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/04 15:01:16 by malbrand         ###   ########.fr       */
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

void	heredoc(const char *delimiter)
{
	char	*s;
	char	*name;
	int		len;
	int		fd_in;

	fd_in = open(delimiter, O_CREAT | O_TRUNC | O_WRONLY, 0664);
	signal(SIGINT, signal_heredoc);
	s = readline(">");
	len = ft_strlen(s);
	while (s != NULL && ft_strncmp(s, delimiter, len) != 0)
	{
		write(fd_in, s, len);
		write(fd_in, "\n", 1);
		free(s);
		s = readline(">");
		len = ft_strlen(s);
	}
	close(fd_in);
}

void	manage_herdoc(t_msh **msh)
{
	t_parser	*cpy;
	t_redir		*red;
	int			fd;
	char		*name;

	cpy = (*msh)->pars;
	while (cpy != NULL)
	{
		red = cpy->redir;
		while (red != NULL)
		{
			if (red->rafter == LL)
			{
				red = red->next;
				heredoc(red->s);
			}
			red = red->next;
		}
		cpy = cpy->next;
	}
}
