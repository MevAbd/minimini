/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parsing.h"

#define PROMPT "SHELL $ "

static const char	*g_type[]
= {
	"REDIR",
	"PIPE",
	"WORD"
};

static const char	*g_redir[]
= {
	"WORD",
	"LEFT",
	"DOUBLE LEFT",
	"RIGHT",
	"DOUBLE RIGHT"
};

static void	newline(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	print_parser(t_parser *parser, t_msh *msh)
{
	int			i;
	t_cmd		*c_cp;
	t_redir		*r_cp;
	t_parser	*cpy;

	i = 0;
	cpy = parser;
	while (cpy)
	{
		c_cp = cpy->cmd;
		r_cp = cpy->redir;
		while (c_cp)
		{
			printf("maillon[%d] cmd = %s\n", i, c_cp->s);
			c_cp = c_cp->next;
		}
		while (r_cp)
		{
			printf("redir = %s\n", r_cp->s);
			printf("type %s\n", g_redir[r_cp->rafter]);
			r_cp = r_cp->next;
		}
		printf("\n\n");
		i++;
		cpy = cpy->next;
	}
	printf("nb cmd == %d\n", msh->size);
}

int	main(int ac, char **av, char **envp)
{
	t_msh		*msh;
	char		*str;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, newline);
	msh = ft_calloc(1, sizeof(t_msh));
	if (msh == NULL)
		return (0);
	msh->env = fill_env(envp);
	while (1)
	{
		str = readline(PROMPT);
		if (!str)
		{
			free(str);
			free(msh->pars);
			free_cmd(&msh->env);
			free(msh);
			break ;
		}
		if (str[0])
		{
			add_history(str);
			parsing(str, &msh);
//			if (get_error() == SUCCESS)
//				print_parser(msh->pars, msh);
		}
		free_parser(&msh->pars);
		free(msh->pars);
		msh->pars = NULL;
		free(str);
		reset_error();
	}
}
