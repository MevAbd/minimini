/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 02:31:26 by malbrand          #+#    #+#             */
/*   Updated: 2022/02/23 22:42:20 by malbrand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "lexer.h"
#include "parsing.h"
#include "lib.h"

int		is_space(char c )
{
	return (c == ' ' || c == '\f' || c == '\t' || c == '\n' || c == '\r' || c == '\v');
}

int		find_next_space(char *s, int i)
{
	while(s[i])
	{
		if (is_space(s[i]))
			break;
		i++;
	}

	return i;
}

int		find_end_dol(char *s, int i)
{
	while(s[i])
	{
		write(1, &s[i], 1);
		if (is_space(s[i]) || s[i] == DOL || is_double_quote(s[i]))
			break;

		i++;
	}

	return i - 1;
}

int		skip_space(char *s, int i)
{
	while(s[i] && is_space(s[i]))
		i++;
	return (i);
}

int		is_empty_quote(char const *s)
{
	return ((s[0] == DBLQT && s[1] == DBLQT) || (s[0] == SPLQT && s[1] == SPLQT));
}

char	*join_without_quote(char *s1, char *s2)
{
	char *ret;
    int len;

    len = ft_strlen(s2);

    if (len > 1)
	    s2[len - 1] = 0;
    else
        return NULL;

	ret = ft_strjoin(s1, s2 + 1);
	// si leaks
	// s1[ft_strlen(s1 - 1)] = SPLQT;
	return ret;
}

void	splqt_manager(char *s, t_lexer **lexer)
{
	char *tmp;

	tmp = join_without_quote((*lexer)->s, s);
	ft_memdel((void**)&s);
	ft_memdel((void**)&(*lexer)->s);
	(*lexer)->s = tmp;
}

char		*find_dol_content(char *s, int size, t_cmd *env)
{
	t_cmd	*tmp;
	char	*to_cmp;

	tmp = env;
	to_cmp = ft_strnjoin(s, "=", size);
	while (tmp)
	{
		if (ft_strncmp(to_cmp, tmp->s, size) == 0)
			return (ft_strdup(tmp->s + size + 1));
		tmp = tmp->next;
	}
	ft_memdel((void**)to_cmp);
	return NULL;
}

void	replace_part_of_str(char **s, char *new, int start, int end)
{
	char	*tmp1;
	char	*tmp2;
	tmp1 = ft_strnjoin(*s, new, (size_t)start);
	tmp2 = ft_strjoin(tmp1, *s + end + 1);
	ft_memdel((void**)&tmp1);
	ft_memdel((void**)s);
	*s = tmp2;
}

char	*replace_dol_by_content(char *s, t_cmd *env)
{
	int i;
	int dol_end_index;
	char *dol_content;

	i = 0;
	while (s[i])
	{
		if (s[i] == DOL)
		{
			dol_end_index = find_end_dol(s, i + 1);
			dol_content = find_dol_content(s + i + 1, dol_end_index - i, env);
			replace_part_of_str(&s, dol_content, i, dol_end_index);
			ft_memdel((void**)&dol_content);
		}
		i++;
	}

	return (s);
}

void	dblqt_manager(char *s, t_lexer **lexer, t_cmd *env)
{
	char *tmp;

	s = replace_dol_by_content(s, env);
	printf("s   : %s\n", s);
	tmp = join_without_quote((*lexer)->s, s);
	printf("tmp : %s\n", tmp);
	ft_memdel((void**)&s);
	ft_memdel((void**)&(*lexer)->s);
	(*lexer)->s = tmp;
}

t_lexer *create_lexer_elem(char *s, t_type type)
{
	t_lexer *new;

	new = ft_calloc(1, sizeof(t_lexer));
	if (new == NULL)
		return (NULL);
	new->type = type;
	new->next = NULL;
	return (new);
}

void 	add_elem_as_next(t_lexer **lexer)
{
	t_lexer *new;

	new = create_lexer_elem(NULL, (*lexer)->type);
	new->next = (*lexer)->next;
	(*lexer)->next = new;
	*lexer = (*lexer)->next;
}

void	no_quote_manager(char *s, t_lexer **lexer, t_cmd *env)
{
	int	i;
	char *tmp1;
	char *tmp2;
	
	i = 0;
	s = replace_dol_by_content(s, env);
	while(s[++i])
	{
		if (is_space(s[i]))
		{
			tmp1 = ft_strjoinn((*lexer)->s, s, i);
			ft_memdel((void**)&(*lexer)->s);
			(*lexer)->s = ft_strdup(tmp1);
			ft_memdel((void**)&tmp1);
			add_elem_as_next(lexer);
			i = skip_space(s, i);
			tmp2 = ft_strdup(s + i);
			ft_memdel((void**)&s);
			s = tmp2;
			i = 0;
		}
	}
	tmp1 = ft_strjoin((*lexer)->s, s);
	ft_memdel((void**)&s);
	ft_memdel((void**)&(*lexer)->s);
	(*lexer)->s = tmp1;
}

void	word_manager(t_lexer **lexer, t_cmd *env)
{
	int		i;
	char 	**ss;

	i = 0;
	ss = quote_spliter((*lexer)->s);
	if (ss == NULL)
	{
		print_error(ERR_SYNT);
		return;
	}
	ft_memdel((void**)&(*lexer)->s);
	while (ss[i] != NULL)
	{
		if (!is_empty_quote(ss[i]))
		{
			if (ss[i][0] == SPLQT)
				splqt_manager(ss[i], lexer);
			else if (ss[i][0] == DBLQT)
				dblqt_manager(ss[i], lexer, env);
			else
				no_quote_manager(ss[i], lexer, env);
		}
		i++;
	}
	// ft_memdel((void**)ss);
}

void	word_checker(t_lexer **lexer, t_cmd *env)
{
	t_lexer	*cpy;

	cpy = (*lexer);
	while (cpy)
	{
		if (cpy->type == WORD)
			word_manager(&cpy, env);
		if (get_error() != SUCCESS)
			break ;
		cpy = cpy->next;
	}

	printf("\n  LEXER :   \no----------o\n");
	t_lexer *test = (*lexer);
	while(test) {
		printf("| %s\n", test->s);
		test = test->next;
		printf("o----------o\n");
	}
	printf("\n");
}

/*
check + decoupage string DONE

sans cote :
- check erreur if `'` | `"` DONE                           '
- $ 
	-> env empty delete maillon DONE
	-> replace by content DONE
	-> si espace (tout type)transformer en autant de maillon de type WORD

double cote:
- retirer les double cote DONE
- si $ voir sans cote DONE

simple cote :
- retirer les cote DONE
*/
