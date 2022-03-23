
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 00:49:04 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/24 00:49:24 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fork.h"

static int	ft_count(const char *s, char c)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	if (s[i] == '\0')
		return (n);
	if (s[0] != c)
		n++;
	while (s[i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	return (n);
}

static char	*ft_substrr(const char *s, int min, int max)
{
	int		i;
	char	*s2;

	s2 = malloc(sizeof(char *) * (max - min + 1));
	if (!s2)
		return (NULL);
	i = 0;
	while (min < max)
	{
		s2[i] = s[min];
		i++;
		min++;
	}
	s2[i] = '\0';
	return (s2);
}

static void	ft_freeb(int n, char **s)
{
	while (n >= 0)
	{
		free(s[n]);
		n--;
	}
}

static	void	ft_while(const char *s, char **s2, char c)
{
	int	i;
	int	n;
	int	min;

	i = 0;
	n = 0;
	min = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		min = i;
		while (s[i] && s[i] != c)
			i++;
		if (n < ft_count(s, c))
		{
			s2[n] = ft_substrr(s, min, i);
			if (s2[n] == NULL)
				ft_freeb(n, s2);
		}
		n++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**s2;

	if (!s)
		return (NULL);
	s2 = malloc(sizeof(char *) * (ft_count(s, c) + 1));
	if (s2 == NULL)
		return (0);
	s2[ft_count(s, c)] = 0;
	ft_while(s, s2, c);
	return (s2);
}
