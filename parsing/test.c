#include <stdio.h>
#include <stdlib.h>

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

char	*ft_strdup(const char *s)
{
	int		i;
	int		len;
	char	*ret;

	if (s == NULL)
		return (NULL);
	len = ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * (len + 1));
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

char	*join_without_quote(char *s1, char *s2)
{
	char *ret;
    int len;

    len = ft_strlen(s1);

    if (len > 1)
	    s1[len - 1] = 0;
    else
        return NULL;
	ret = ft_strjoin(s1 + 1, s2);
	s1[ft_strlen(s1 - 1)] = 'q';
	return ret;
}

int main()
{
    char *s1;
    char *s2;
    
    s1 = (char*)malloc(sizeof(char) * 5);
    s2 = (char*)malloc(sizeof(char) * 5);

    s1[0] = '"';
    s1[1] = 't';
    s1[2] = 'o';
    s1[3] = '"';
    s1[4] = '\0';


    s2[0] = 'a';
    s2[1] = 'a';
    s2[2] = 'a';
    s2[3] = 'a';
    s2[4] = '\0';
    printf("%s\n", join_without_quote(s1, s2));

    return (0);
}