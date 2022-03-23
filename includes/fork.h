/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*      fork.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORK_H
# define FORK_H

# include "struct.h"

int	nb_cmd(t_parser *pars);

void	free_tab(char **tab);
void	search_cmd(t_msh **msh);
void	print_parser(t_parser *pars, t_msh *msh);

char	**get_env(t_cmd *env);
char	**get_path(t_msh **msh);
char	**ft_split(const char *s, char c);
char	*ft_add_cmd(char *cmd, char *add);

#endif
