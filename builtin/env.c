/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 07:18:13 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/24 00:13:39 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"

int	ft_exc_env(t_parser *cpy, t_msh **msh)
{
	t_cmd	*env;

	env = (*msh)->env;
	if (cpy->cmd->next != NULL)
	{
		write((*msh)->fd_out, "with no arg or option\n", 22);
		return (127);
	}
	while (env)
	{
		write((*msh)->fd_out, env->s, ft_strlen(env->s));
		write((*msh)->fd_out, "\n", 1);
		env = env->next;
	}
	return (0);
}
