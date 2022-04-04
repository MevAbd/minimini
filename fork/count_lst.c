/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    count_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "parsing.h"
#include "fork.h"

int	nb_line_env(t_cmd *env)
{
	int		i;
	t_cmd	*cpy;

	cpy = env;
	i = 0;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}

int	nb_cmd(t_parser *pars)
{
	int			i;
	t_parser	*cpy;

	cpy = pars;
	i = 0;
	while (cpy)
	{
		cpy = cpy->next;
		i++;
	}
	return (i);
}
