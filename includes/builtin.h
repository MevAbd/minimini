/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

int		compare(char *s1, char *s2);
int		ft_pwd(t_parser *cmd, t_msh **msh);
int		ft_exc_cd(t_parser *cmd, t_msh **msh);
int		ft_exc_env(t_parser *cmd, t_msh **msh);
int		ft_exc_echo(t_parser *cmd, t_msh **msh);
int		ft_exc_export(t_parser *cmd, t_msh **msh);
int		ft_exc_unset(t_parser *cmd, t_msh **msh);
int		ft_exc_exit(t_parser *cmd, t_msh **msh);

#endif
