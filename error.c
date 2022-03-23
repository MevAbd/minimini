/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"

static const char	*g_err[]
= {
	"",
	"Malloc error !",
	"Synthax error !",
	"Command not found !"
};

static t_error	static_error(t_error err, t_error type)
{
	static t_error	error = SUCCESS;

	if (type == ERR_SET)
		error = err;
	return (error);
}

t_error	get_error(void)
{
	return (static_error(0, ERR_GET));
}

void	reset_error(void)
{
	static_error(SUCCESS, ERR_SET);
}

t_error	print_error(t_error err)
{
	if (get_error() != SUCCESS)
		return (get_error());
	static_error(err, ERR_SET);
	write(2, "minishell: ", 11);
	write(2, g_err[err], ft_strlen(g_err[err]));
	write(2, "\n", 1);
	return (err);
}
