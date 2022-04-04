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

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dest;
	size_t	i;

	if (ft_strlen(s1) < n)
		return ft_strdup(s1);
	else
	{
		dest = (char *)malloc(sizeof(char) * (n + 1));
		if (!dest)
			return (NULL);
	}
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
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
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len_concat;
	char	*concat;
	int		i;
	int		j;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	len_concat = ft_strlen(s1) + ft_strlen(s2);
	concat = (char*)malloc(sizeof(*concat) * (len_concat + 1));
	if (!concat)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		concat[i] = s1[i];
	while (s2[j])
		concat[i++] = s2[j++];
	concat[i] = '\0';
	return (concat);
}

char	*ft_strnjoin(char const *s1, char const *s2, size_t n)
{
	char	*ret;
	int		i;
	int		j;
	int		s2_len;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strndup(s1, n));
	s2_len = ft_strlen(s2);
	if (s2_len > n)
		s2_len = n;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + s2_len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i] && i < n)
		ret[i] = s1[i];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoinn(char const *s1, char const *s2, size_t n)
{
	char	*ret;
	int		i;
	int		j;
	int		s2_len;

	if (!s1)
		return (ft_strndup(s2, n));
	if (!s2)
		return (ft_strdup(s1));
	s2_len = ft_strlen(s2);
	if (s2_len > n)
		s2_len = n;
	ret = (char *)malloc(sizeof(char) * (ft_strlen(s1) + s2_len + 1));
	if (!ret)
		return (NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	j = 0;
	while (s2[j] && i < n)
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (ret);
}