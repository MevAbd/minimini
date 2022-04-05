/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/04/05 12:42:34 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include "struct.h"

int		nb_cmd(t_parser *pars);
int		nb_line_env(t_cmd *env);
int		test_access(t_msh **msh, char **cmd);

void	free_tab(char **tabl);
void	init_msh(t_msh **msh);
void	search_cmd(t_msh **msh);
void	free_wait_pid(t_msh **msh);
void	redir(t_parser *pars, t_msh **msh);
void	print_parser(t_parser *pars, t_msh *msh);
void	cmd_fork(t_msh **msh, t_parser *cpy, int j);
void	manage_pipefd(t_msh **msh, int *i, int verif);

char	**get_env(t_cmd *env);
char	**get_path(t_msh **msh);
char	**ft_split(const char *s, char c);
char	*ft_add_cmd(char *cmd, char *add);

#endif
