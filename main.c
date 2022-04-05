/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/05 13:33:01 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parsing.h"

#define PROMPT "SHELL $ "

static void	ft_newline(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ctrl_d(char *str, t_msh *msh)
{
	write(1, "exit\n", 5);
	free(str);
	free(msh->pars);
	free_cmd(&msh->env);
	free(msh);
}

int	main(int ac, char **av, char **envp)
{
	t_msh		*msh;
	char		*str;

	signal(SIGINT, ft_newline);
	signal(SIGQUIT, SIG_IGN);
	msh = ft_calloc(1, sizeof(t_msh));
	if (msh == NULL)
		return (0);
	msh->env = fill_env(envp);
	while (1)
	{
		str = readline(PROMPT);
		if (!str)
		{
			ctrl_d(str, msh);
			break ;
		}
		else if (str[0])
		{
			add_history(str);
			parsing(str, &msh);
		}
		free_parser(&msh->pars);
		free(msh->pars);
		msh->pars = NULL;
		free(str);
		reset_error();
	}
	return (0);
}
