#include <stdio.h>
#include <stdlib.h>
#include "../includes/parsing.h"


int         is_quote(char c)
{
    return c == SPLQT || c == DBLQT;
}

int         find_next_given_char_index(char const *s, int i, char c)
{
    i++;
    while(s[i] && s[i] != c)
        i++;
    if (s[i] == '\0')
        return (-1);
    
    return (i);
}

int         find_next_quote_index(char const *s, int i)
{
    i++;
    while (s[i])
    {
        if (is_quote(s[i]))
            break;
        i++;
    }

    return (i);
}

int         word_counter(char *s)
{
    char    mem;
    int     i;
    int     ret;

    i = 0;
    ret = 0;
    mem = 0;
    while (s[i])
    {
        if (is_quote(s[i]))
        {
            ret ++;
            mem = 0;
            i = find_next_given_char_index(s, i, s[i]);
            if (i == -1)
                return (-1);
        }
        else if (mem == 0)
        {
            ret++;
            mem = 1;
        }
        i++;
    }

    return (ret);
}

int        fill_str(char const *src, char *str, int j, int next_quote_index)
{
    int     i;

    i = 0;
    if (!is_quote(src[j]))
        next_quote_index--;
    while (j <= next_quote_index)
    {
        str[i] = src[j];
        i++;
        j++;
    }

    return (j);
}

char        **fill_tab(char **tab, char const *s, int tab_size)
{
    int     i;
    int     j;
    int     next_quote_index;

    i = 0;
    j = 0;
	while (i < tab_size)
	{
        next_quote_index = find_next_quote_index(s, j);
        if (is_quote(s[j]))
            next_quote_index = find_next_given_char_index(s, j, s[j]);
		tab[i] = ft_calloc((next_quote_index - j + 1), sizeof(char));
		if (!tab[i])
            return (NULL);
        j = fill_str(s, tab[i], j, next_quote_index);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

char	    **quote_spliter(char *s)
{
	int     word_count;
    char    **ret;

    if (!s)
        return (NULL);

    word_count = word_counter(s);
    if (word_count == -1)
        return (NULL);

    ret = (char **)malloc(sizeof(char *) * (word_count + 1));
    if (!ret)
        return (NULL);

    ret = fill_tab(ret, s, word_count);
    
    return (ret);
}

// int main(int ac, char **av)
// {
//     char **ss;
    
//     ss = quote_spliter("\"nimportequoi     $mev         qulequechose\"");


//     while(*ss != NULL)
//     {
//         printf("%s\n", *ss);
//         ss++;
//     }

//     return (0);
// }
