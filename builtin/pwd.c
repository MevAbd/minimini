/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 01:03:12 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 23:32:11 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	ft_pwd(t_parser *cmd, t_msh **msh)
{
	char	tampon[UCHAR_MAX];

	if (getcwd(tampon, UCHAR_MAX) == NULL)
		return (127);
	write((*msh)->fd_out, tampon, ft_strlen(tampon));
	write((*msh)->fd_out, "\n", 1);
	return (0);
}
