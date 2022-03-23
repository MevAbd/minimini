/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    lib.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"

int	ft_strlen(const char *s)
{
	int	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(char const *s1, char const *s2, int n)
{
	int	i;

	i = 0;
	if (n == 0 && s1[i] == s2[i])
	{
		i++;
		return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
	}
	while (s1[i] && s2[i] && s1[i] == s2[i] && i < n)
		i++;
	return (((unsigned char)s1[i]) - ((unsigned char)s2[i]));
}

void	*ft_calloc(int nb, int size)
{
	char	*to_return;
	int		i;
	int		n;

	n = size * nb;
	to_return = malloc(n);
	if (to_return == NULL)
	{
		print_error(ERR_MALLOC);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		*(to_return + i) = 0;
		i++;
	}
	return (to_return);
}

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*ret;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	ret = ft_calloc((len + 1), sizeof(char));
	if (ret == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		ret[i] = s[i];
		i++;
	}
	return (ret);
}

char	*strdup_len(const char *str, int i, int j)
{
	int		c;
	char	*ret;

	ret = ft_calloc((j + 1), sizeof(char));
	if (ret == NULL)
		return (NULL);
	c = 0;
	while (c < j)
	{
		ret[c] = str[i + c];
		c++;
	}
	return (ret);
}
