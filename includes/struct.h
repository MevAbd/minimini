/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "lib.h"

typedef enum e_error
{
	ERR_SET=-2,
	ERR_GET,
	SUCCESS,
	ERR_MALLOC,
	ERR_SYNT,
	ERR_CMD,
}	t_error;

typedef enum e_type
{
	REDIR,
	PIPE,
	WORD,
}	t_type;

typedef enum e_rafter
{
	W,
	L,
	LL,
	R,
	RR,
}	t_rafter;

typedef struct s_lexer
{
	char			*s;
	t_type			type;
	struct s_lexer	*next;
}			t_lexer;

typedef struct s_cmd
{
	char			*s;
	struct s_cmd	*next;
}			t_cmd;

typedef struct s_redir
{
	char			*s;
	t_rafter		rafter;
	struct s_redir	*next;
}			t_redir;

typedef struct s_parser
{
	int				pid;
	t_cmd			*cmd;
	t_redir			*redir;
	struct s_parser	*next;
}			t_parser;

typedef struct s_msh
{
	t_cmd		*env;
	t_parser	*pars;
	char		**path;
	char		**cmd;
	char		**tab_env;
	int			pipefd[2];
	int			fd_in;
	int			fd_out;
	int			size;
}			t_msh;

void	reset_error(void);

t_error	get_error(void);
t_error	print_error(t_error err);

#endif
