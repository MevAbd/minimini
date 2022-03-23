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

static int	ft_cmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s2[i] && s1[i])
	{
		if (s2[i] == s1[i])
			i++;
		else
			return (-1);
	}
	return (0);
}

static char	*ft_stradd(char *s1, char *s2)
{
	int		i;
	int		j;
	int		size;
	char	*ret;

	i = 0;
	j = 0;
	size = ft_strlen(s1) + ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * size + 1);
	if (!ret)
		return (NULL);
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		ret[i + j] = s2[j];
		j++;
	}
	ret[i + j] = '\0';
	return (ret);
}

static void	ft_replace_pwd(t_msh **msh, char *pwd)
{
	int	i;

	i = 0;
	while ((*msh)->tab_env[i])
	{
		if (ft_cmp((*msh)->tab_env[i], "OLDPWD=") != 0)
			i++;
		else
		{
			free((*msh)->tab_env[i]);
			(*msh)->tab_env[i] = ft_stradd("OLDPWD=", pwd);
			return ;
		}
	}
}

void	ft_pwd(t_parser *cmd, t_msh **msh)
{
	char	tampon[UCHAR_MAX];

	if (cmd->next != NULL)
	{
		write((*msh)->fd_out, "command not found\n", 18);
		return ;
	}
	if (getcwd(tampon, UCHAR_MAX) == NULL)
		return ;
	ft_replace_pwd(msh, tampon);
	write((*msh)->fd_out, tampon, ft_strlen(tampon));
	write((*msh)->fd_out, "\n", 1);
}
