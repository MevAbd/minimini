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

int		skip_space(char *s, int i)
{
	while(s[i] && is_space(s[i]))
		i++;
	return (i);
}

int		is_empty_quote(char const *s)
{
	return s[0] == DBLQT && s[1] == DBLQT || s[0] == SPLQT && s[1] == SPLQT;
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
	// si leaks
	// s1[ft_strlen(s1 - 1)] = SPLQT;
	return ret;
}

void	splqt_manager(char *s, t_lexer **lexer)
{
	char *tmp;

	tmp = join_without_quote(s, (*lexer)->s);
	free(s);
	free((*lexer)->s);
	(*lexer)->s = tmp;
}

char		*find_dol_content(char *s, int size, t_cmd *env)
{
	t_cmd	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(s, tmp->s, size))
			return (ft_strdup(tmp->s + size + 1));
		tmp = tmp->next;
	}

	return NULL;
}

void	replace_part_of_str(char *s, char *new, int start, int end)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strnjoin(s, new, (size_t)start);
	tmp2 = ft_strjoin(tmp1, s + end);
	free(tmp1);
	free(s);
	s = tmp2;
}

char	*replace_dol_by_content(char *s, t_cmd *env)
{
	int i;
	int dol_end_index;
	char *dol_content;

	while (s[i])
	{
		if (s[i] == DOL)
		{
			dol_end_index = find_next_space(s, i) - 1;
			dol_content = find_dol_content(s + i + 1, dol_end_index - i + 1, env);
			replace_part_of_str(s, dol_content, i, dol_end_index);
			free(dol_content);
		}
		i++;
	}

	return (s);
}

void	dblqt_manager(char *s, t_lexer **lexer, t_cmd *env)
{
	char *tmp;

	s = replace_dol_by_content(s, env);
	tmp = join_without_quote(s, (*lexer)->s);
	free(s);
	free((*lexer)->s);
	(*lexer)->s = tmp;
}

void	no_quote_manager(char *s, t_lexer **lexer, t_cmd *env)
{
	int	i;
	char *dol_content;
	char *tmp;
	t_lexer *new;
	
	if (s[0] != DOL)
		return ;
	dol_content = find_dol_content(s + 1, ft_strlen(s + 1), env);
	free(s);
	s = dol_content;

	i = find_next_space(s, 0);
	if (i != ft_strlen(s) - 1)
	{
		while (s[i])
		{
			tmp = ft_strjoinn((*lexer)->s, s + i - 1);
			free((*lexer)->s);
			(*lexer)->s = tmp;
			i = skip_space(s, i);
			new = create_lexer_elem(s + i, (*lexer)->type);
			new->next = (*lexer)->next;
			(*lexer)->next = new;
			i = find_next_space(s, i);
		}
	}
	else
	{
		tmp = ft_strjoin((*lexer)->s, s);
		free((*lexer)->s);
		(*lexer)->s = tmp;
	}
	free(s);
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
	free((*lexer)->s);
	while (ss[i] != NULL)
	{
		if (is_empty_quote(ss[i]))
			continue;
		if (ss[i][0] == SPLQT)
			splqt_manager(ss[i], lexer);
		else if (ss[i][0] == SPLQT)
			dblqt_manager(ss[i], lexer, env);
		else
			no_quote_manager(ss[i], lexer, env);
		i++;
	}
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