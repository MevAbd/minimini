/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 05:53:39 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/24 03:12:03 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "parsing.h"

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

static void	ft_replace(t_msh **msh, char *pwd, char *s)
{
	int	i;

	i = 0;
	while ((*msh)->tab_env[i])
	{
		if (ft_cmp((*msh)->tab_env[i], s) != 0)
			i++;
		else
		{
			free((*msh)->tab_env[i]);
			(*msh)->tab_env[i] = ft_stradd(s, pwd);
			return ;
		}
	}
}

int	ft_cd_home(t_msh **msh)
{
	int		i;
	char	*ret;

	i = 0;
	while ((*msh)->tab_env[i] && ft_strncmp("HOME=", (*msh)->tab_env[i], 3))
		i++;
	if ((*msh)->tab_env[i])
	{
		ret = ft_strdup(&(*msh)->tab_env[i][5]);
		if (chdir(ret) == -1)
		{
			write((*msh)->fd_out, "cd: no such file or directory : ", 32);
			write((*msh)->fd_out, ret, ft_strlen(ret));
			write((*msh)->fd_out, "\n", 1);
			return (1);
		}
		else
			ft_replace(msh, ret, "PWD=");
		if (ret)
			free(ret);
		return (0);
	}
	return (1);
}

int	ft_cd_old(t_msh **msh)
{
	int	i;

	i = 0;
	while ((*msh)->tab_env[i] && ft_strncmp("OLDPWD=", (*msh)->tab_env[i], 6))
		i++;
	if ((*msh)->tab_env[i])
	{
		chdir(&(*msh)->tab_env[i][7]);
		write((*msh)->fd_out, (&(*msh)->tab_env[i][7]), ft_strlen(&(*msh)->tab_env[i][7]));
		write((*msh)->fd_out, "\n", 1);
		ft_replace(msh, (&(*msh)->tab_env[i][7]), "PWD=");
		return (0);
	}
	else
		write((*msh)->fd_out, "OLDPWD not set\n", 14);
	return (1);
}

int	ft_exc_cd(t_parser *cpy, t_msh **msh)
{
	int		i;
	char	tampon[UCHAR_MAX];
	t_cmd	*cmd;

	i = 0;
	if (getcwd(tampon, UCHAR_MAX) == NULL)
		return (127);
	cmd = cpy->cmd->next;
	if (cmd == NULL || (!(ft_strncmp(cmd->s, "--\0", 2))))
		i = i + ft_cd_home(msh);
	else if (!(ft_strncmp(cmd->s, "-\0", 1)))
		i = i + ft_cd_old(msh);
	else if (chdir(cmd->s) == -1)
	{
		write((*msh)->fd_out, "cd: no such file or directory : ", 32);
		write((*msh)->fd_out, cmd->s, ft_strlen(cmd->s));
		write((*msh)->fd_out, "\n", 1);
		return (1);
	}
	ft_replace(msh, tampon, "OLDPWD=");
	free_cmd(&(*msh)->env);
	(*msh)->env = fill_env((*msh)->tab_env);
	return (i);
}
